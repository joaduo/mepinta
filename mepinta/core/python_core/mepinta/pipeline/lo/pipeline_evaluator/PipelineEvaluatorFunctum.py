# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
'''

from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, INPUT_PROPS,\
  OUTPUT_PROPS, FUNCTUM_PROPERTY_FLAG, has_flags, PROCESSOR_EXIT_NORMAL,\
  CUSTOM_INPUT_PROPS, CUSTOM_PROPERTY_FLAG, CUSTOM_OUTPUT_PROPS
from pipeline_backend.logging.logging import log_debug, log_warning
from pipeline_backend.void_pointer_casting.void_pointer_casting import voidp_to_FunctumPropertyValue,\
  voidp_to_FunctionPropertyValue
from mepinta.pipeline.lo.pipeline_evaluator.ProcessorArgsManager import ProcessorArgsManager
from pipeline_backend.args_management.args_management import get_functum_struct_voidp
from mepinta.pipeline.lo.pipeline_evaluator.base import PipelineEvaluatorBase
from mepinta.pipeline.lo.pipeline_data.data_model import PropertyValuePointer
#from mepinta.pipeline.lo.reentrant.data_model import ProcessorContext

#TODO: inherit from PipelineEvaluatorBase
class PipelineEvaluatorFunctum(PipelineEvaluatorBase):
  def __callProcessor(self,pline,prop_id,prop,func_prop_value,args_mngr):
    func_ptr = self.context_lo.functions[func_prop_value.func_id].get_func_pointer()
    #TODO: if using long on shedkin, then casting should be applied
    log_debug("Entering processor function '%s'."%prop.name)
    exit_status = self.func_caller.call_processor_func(func_ptr, args_mngr.get_args())
    log_debug("Leaving processor function '%s'."%prop.name)
    if exit_status != PROCESSOR_EXIT_NORMAL:
      #TODO: fix this on python should log as error when fixed
      log_debug("Processor function '%s' with unnormal exit status: %r."%(prop.name,exit_status))
    
    if prop_id in pline.marked_outputs:
      #We have a propagation filter. Then it must create its changed set
      return args_mngr.build_changed_set()
    return None

  #TODO: remove add_propagation
  def evaluateProp(self, pline, prop_id):
    #if prop_id not in pline.properties: RuntimeError("You should never evaluate a non existent property") #DEBUG
    prop = pline.all_properties[prop_id]
    return self.__evalProperty(pline, prop_id, prop)

  def __evalFunction(self, pline, prop_id, prop):
    log_debug('Evaluating function with prop_id=%r'%prop_id)
    #TODO: review if this code is necessary. 
    if not prop_id in pline.changed_track: #Already visited on this evaluation round?
      return None
    pline.changed_track.remove(prop_id) #Mark as visited for this round

    func_prop_value = voidp_to_FunctionPropertyValue(prop.get_value())
    inputs_ids = pline.get_topology().connections.dpdencies[prop_id]
    outputs_ids = pline.get_topology().connections.dpdents[prop_id]
    args_mngr = ProcessorArgsManager(self.context_lo, func_prop_value,thread_id=0)
    
    #processor_context = ProcessorContext(self.context_lo, pline, self)
    #args_mngr.setProcessorContext(processor_context)
    
    #Iterate over the processor's Inputs
    for input_id in inputs_ids:
      self.__inputValue(pline, input_id, args_mngr)

    #Iterate over the processor's Outputs
    for dent_id in outputs_ids:
      self.__outputValue(pline, dent_id, args_mngr)

    return self.__callProcessor(pline, prop_id, prop, func_prop_value, args_mngr)

  def __inputValue(self, pline, input_id, args_mngr):
    input_prop = pline.all_properties[input_id]
    if has_flags(input_prop.type, CUSTOM_PROPERTY_FLAG):
      args_mngr.set_in_out(CUSTOM_INPUT_PROPS)
    else:
      args_mngr.set_in_out(INPUT_PROPS)

    if has_flags(input_prop.type,FUNCTION_PROPERTY_FLAG):
      self.__evalFunction(pline, input_id, input_prop)
      return input_id
    else:
      changed = input_id in pline.changed_track
      #TODO: (performance) review if it can avoid adding the prop to the args. Cached args!
      _, dency_prop = self.__evalProperty(pline, input_id, input_prop)
      #TODO: review it we really need to initialize properties
      #self.p_value_mngr.init_set_prop_value(input_prop, input_dency_prop.get_value_ptr())
      args_mngr.append(input_id, input_prop, dency_prop)
      if changed: #TODO: review if this is OK here
        args_mngr.changed_value()
      else:
        args_mngr.unchanged_value()      
      args_mngr.next_prop() #TODO: this method is useful if we avoid adding a prop not changed
      return input_id

  def __outputValue(self, pline, out_id, args_mngr):
    out_prop = pline.all_properties[out_id]
    if has_flags(out_prop.type, CUSTOM_PROPERTY_FLAG):
      args_mngr.set_in_out(CUSTOM_OUTPUT_PROPS)
    else:
      args_mngr.set_in_out(OUTPUT_PROPS)
          
    if out_id in pline.changed_track: 
      pline.changed_track.remove(out_id)

    if not has_flags(out_prop.type, FUNCTION_PROPERTY_FLAG):
      self.p_value_mngr.init_prop_value(out_prop)
      args_mngr.append(out_id, out_prop, out_prop)
      args_mngr.unchanged_value() #Reset its output status
      args_mngr.next_prop() #Check if this is necessary or (append should increment the pointer?)

  def __solveNonCached(self, pline, out_id, out_prop):
    input_id = pline.cached_link.get_first(out_id)
    input_prop = pline.all_properties[input_id]
    input_id, input_prop = self.__evalProperty(pline, input_id, input_prop)
    if out_id in pline.get_topology().cached: #We are caching on this node, then we must copy values
      log_debug('Copying value for property:%r id=%r'%(out_prop.name,out_id))
      self.p_value_mngr.copy_prop_value(out_prop, input_prop.get_value_ptr())
    else: #We can directly pass the value_pointer
      self.__stealInput(pline,  out_id, out_prop, input_id, input_prop)

  def __stealInput(self,pline, out_id, out_prop, input_id, input_prop):
    #TODO: create a ValuePointerStealer? What for?
    #If we steal a value of an unchanged property, we will run into problems
    #We must fix that situation
    #Also we can only steal a value when its pointed only by one prop (the non_cached input)
    #if not, we need to copy it as many time as the stealing needs
    log_debug('Non cached properties should be used in a restricted context.')
    log_debug('Stealing value for property:%r id=%r from property:%r id=%r'%(out_prop.name,out_id,input_prop.name,input_id))
    self.p_value_mngr.set_prop_value(out_prop, input_prop.get_value_ptr()) #Need to do this first, if not the value will be freed
    log_debug('Detaching from previous property:%r id=%r'%(input_prop.name,input_id))
    vpointer_none = PropertyValuePointer() #Create a value pointer with None as value #TODO: relies on garbage collector
    self.p_value_mngr.set_prop_value(input_prop,vpointer_none) #Ok, you do not own the previous value anymore.
    pline.get_topology().changed_primary.add(input_id) #input changed (we stole it's value and needs to propagate the change)

  def __evalFunctum(self, pline, prop_id, prop):
    log_debug("Evaluating functum with prop_id=%r"%prop_id)
    #TODO: review if this code is necessary.
    functum_prop_value = voidp_to_FunctumPropertyValue(prop.get_value())
    inputs_ids = pline.get_topology().connections.dpdencies[prop_id]
    outputs_ids = pline.get_topology().connections.dpdents[prop_id]
    args_mngr = ProcessorArgsManager(self.context_lo, functum_prop_value, thread_id=0)    
    if prop_id in pline.changed_track: #Already visited on this evaluation round?
      pline.changed_track.remove(prop_id) #Mark as visited for this round
      
    #args_mngr.set_in_out(INPUT_PROPS)    
    #Iterate over the processor's Inputs
    for input_id in inputs_ids:
      self.__inputValue(pline, input_id, args_mngr)      

    #args_mngr.set_in_out(OUTPUT_PROPS)
    #Iterate over the processor's Outputs
    for dent_id in outputs_ids:
      self.__outputValue(pline, dent_id, args_mngr)

    functum_prop = functum_prop_value.get_functum_prop()
    if functum_prop.get_value() == None:
      func_ptr = self.context_lo.functions[functum_prop_value.func_id].get_func_pointer()
      functum_struct = get_functum_struct_voidp(func_ptr, args_mngr.get_args())    
      self.p_value_mngr.new_prop_value(functum_prop, functum_struct)
    #else:pass
    #TODO:IMPORTANT it's caching here beware! args should be ok, but func_ptr may change
    return prop_id, functum_prop

  def __evalProperty(self, pline, prop_id, prop):         
    if has_flags(prop.type,FUNCTION_PROPERTY_FLAG): #is a function, then evaluate it 
      self.__evalFunction(pline, prop_id, prop)
    else:      
      dencies = pline.get_topology().connections.dpdencies[prop_id]
      if has_flags(prop.type,FUNCTUM_PROPERTY_FLAG): #Its a functum
        if len(dencies) == 1:
          dency_id = dencies[0] 
          dency_prop = pline.all_properties[dency_id]
          if has_flags(dency_prop.type, FUNCTUM_PROPERTY_FLAG):
            return self.__evalProperty(pline, dency_id, dency_prop)
        return self.__evalFunctum(pline, prop_id, prop)
      else: #Its a common property
        log_debug("Evaluating property with prop_id=%r"%prop_id)
        changed = False
        if prop_id in pline.changed_track:#Has changed?
          changed = True
          log_debug("Removing changed Property with prop_id=%r"%prop_id)
          pline.changed_track.remove(prop_id)#Mark as visited for this round           
          if prop_id in pline.cached_link: #Steal input value
            self.__solveNonCached(pline, prop_id, prop)
        for dency_id in dencies:
          dency_prop = pline.all_properties[dency_id]
          if has_flags(dency_prop.type, FUNCTION_PROPERTY_FLAG):
            if changed: #Only evaluateProp function if property was notified of a change
              self.__evalFunction(pline, dency_id, dency_prop)
          else: #Connected to several InOutProperties
            if len(dencies) == 1:
              return self.__evalProperty(pline, dency_id, dency_prop)
            else:
              log_warning("A common (in/out/internal) property shouldn't be connected to functions and other properties.For prop_id: %r "%prop_id)
        if changed: #It's a leaf property, the value may be uninitialized
          self.p_value_mngr.init_prop_value(prop)
    return prop_id,prop

def shedskin_PipelineEvaluatorFunctum(context_lo, pline, prop, args_mngr):
  pe = PipelineEvaluatorFunctum(context_lo)
  prop_id = 100
  pline.all_properties[prop_id] = prop
  #pe.__evalFunction(pline, prop_id, prop)
  pe.evaluateProp(pline, prop_id)
  #pe.animate(pline, prop_id)
  #pe.__evalProperty(pline, prop_id, prop)

