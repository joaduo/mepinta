# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

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

from mepinta.pipeline.lo.FunctionCaller import FunctionCaller
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, \
  INPUT_PROPS, OUTPUT_PROPS, PROCESSOR_EXIT_NORMAL, has_flags,\
  FUNCTUM_PROPERTY_FLAG
from mepinta.pipeline.lo.pipeline_data.data_model import PropertyValuePointer
from pipeline_backend.logging.logging import log_debug, log_warning
from pipeline_backend.void_pointer_casting.void_pointer_casting import voidp_to_FunctionPropertyValue
from mepinta.pipeline.lo.pipeline_evaluator.ProcessorArgsManager import ProcessorArgsManager
from mepinta.pipeline.lo.generic_data.DirectedGraph import DirectedGraph
 
class PipelineEvaluatorBase(object):
  def __init__(self, context_lo):
    self.context_lo = context_lo
    self.p_value_mngr = PropertyValueManager(context_lo)
    self.func_caller = FunctionCaller()
  def evaluateProp(self, pline, prop_id):
    prop = pline.all_properties[prop_id]
    return prop_id, prop

#  def animate(self, pline, prop_id):
#    '''When making changes do not persist them for next change'''
#    prop_id, prop = self.eval(pline, prop_id, add_propagation=True)
#    #pline.get_topology().changed_secondary.clear()
#    return prop_id, prop
#
#  def eval(self,pline,prop_id, add_propagation):
#    #if prop_id not in pline.properties: RuntimeError("You should never evaluate a non existent property") #DEBUG
#    #TODO: take propagation out of here. Propagation triggers should be fired from higher levels
#    #if add_propagation:
#    #  pline.changed_track.update(pline.get_topology().changed_secondary)
#    prop = pline.all_properties[prop_id]
#    return self.eval_property(pline, prop_id, prop)
#
#  def gather_input_value(self, pline, input_id, args_mngr):
#    input_prop = pline.all_properties[input_id]
#    
#    if has_flags(input_prop.type,FUNCTION_PROPERTY_FLAG):
#      self.eval_function(pline, input_id, input_prop)
#      return input_id
#    else:
#      changed = False
#      #TODO: (performance) review if it can avoid adding the prop to the args. Cached args!
#      if input_id in pline.changed_track:
#        changed = True
#      input_dency_id,input_dency_prop = self.eval_property(pline, input_id, input_prop)
#      #TODO: review it we really need to initialize properties
#      self.p_value_mngr.init_set_prop_value(input_prop, input_dency_prop.get_value_ptr())
#      args_mngr.append(input_id, input_prop, input_prop)
#      if changed: #TODO: review if this is OK here
#        args_mngr.changed_value()
#      else:
#        args_mngr.unchanged_value()      
#      args_mngr.next_prop() #TODO: this method is useful if we avoid adding a prop not changed
#      return input_dency_id
#
#  def gather_output_value(self, pline, out_id, in_dency_ids, args_mngr):
#    if out_id in pline.changed_track: 
#      pline.changed_track.remove(out_id)
#    out_prop = pline.all_properties[out_id]
#     
#    if out_id in pline.cached_link:
#      #TODO: remove the inputs values, 
#      #since we won't be use them (we work on outputs)?
#      input_id = pline.cached_link.get_first(out_id)
#      input_prop = pline.all_properties[input_id]
#      value_ptr = input_prop.get_value_ptr()
#      if out_id in pline.get_topology().cached: 
#        #We are caching on this node, then we must copy values
#        log_debug('Copying value for property:%r id=%r'%(out_prop.name,out_id))
#        self.p_value_mngr.copy_prop_value(out_prop, value_ptr)
#      else: #We can directly pass the value_pointer
#        self.steal_input_value(pline, out_id, out_prop, input_id, input_prop, 
#                               value_ptr, in_dency_ids)
#
#    if not has_flags(out_prop.type, FUNCTION_PROPERTY_FLAG):
#      self.p_value_mngr.init_prop_value(out_prop)
#      args_mngr.append(out_id, out_prop, out_prop)
#      args_mngr.unchanged_value() #Reset its status
#      args_mngr.next_prop() #Check if this is necessary or (append should increment the pointer?)
#
#  def steal_input_value(self,pline, out_id, out_prop, input_id, input_prop, 
#                        value_ptr, in_dency_ids):
#    #TODO: create a ValuePointerStealer? What for?
#    #If we steal a value of an unchanged property, we will run into problems
#    #We must fix that situation
#    #Also we can only steal a value when its pointed only by one prop (the non_cached input)
#    #if not, we need to copy it as many time as the stealing needs
#    log_debug('Non cached properties should be used in a restricted context.')
#    log_debug('Stealing value for property:%r id=%r from property:%r id=%r'%(out_prop.name,out_id,input_prop.name,input_id))
#    self.p_value_mngr.set_prop_value(out_prop, value_ptr) #Need to do this first, if not the value will be freed
#    log_debug('Detaching from previous property:%r id=%r'%(input_prop.name,input_id))
#    vpointer_none = PropertyValuePointer() #Create a value pointer with None as value
#    self.p_value_mngr.set_prop_value(input_prop,vpointer_none) #Ok, you not own the previous value anymore.
#    pline.get_topology().changed_primary.add(input_id) #input changed (we stole it's value)
#    if input_id in in_dency_ids:
#      in_dency_id = in_dency_ids.get_first(input_id)
#      in_dency_prop = pline.all_properties[in_dency_id]
#      log_debug('Detaching from previous property dependency:%r id=%r'%(in_dency_prop.name,in_dency_id))
#      self.p_value_mngr.set_prop_value(in_dency_prop,vpointer_none)
#      pline.get_topology().changed_primary.add(in_dency_id) #inputs depedency's changed (we stole it's value)
#
#  def eval_function(self, pline, prop_id, prop):
#    log_debug('Evaluating function prop_id=%r'%prop_id)
#    #TODO: review if this code is necessary. 
#    if not prop_id in pline.changed_track: #Already visited on this evaluation round?
#      return None
#    pline.changed_track.remove(prop_id) #Mark as visited for this round
#
#    func_prop_value = voidp_to_FunctionPropertyValue(prop.get_value())
#    inputs_ids = pline.get_topology().connections.dpdencies[prop_id]
#    outputs_ids = pline.get_topology().connections.dpdents[prop_id]
#    args_mngr = ProcessorArgsManager(self.context_lo, func_prop_value, 
#                                     len(inputs_ids), len(outputs_ids)
#                                     ,thread_id=0)
#    args_mngr.set_in_out(INPUT_PROPS)    
#    in_dency_ids = DirectedGraph()#{} #Inputs dependencies Ids. Used when we want to mark changed_primary node on non-cached pipeline
#    #Iterate over the processor's Inputs
#    for input_id in inputs_ids:
#      in_dency_id = self.gather_input_value(pline, input_id, args_mngr)
#      if input_id != in_dency_id:
#        in_dency_ids.add(input_id, in_dency_id)      
#
#    args_mngr.set_in_out(OUTPUT_PROPS)
#    #Iterate over the processor's Outputs
#    for dent_id in outputs_ids:
#      self.gather_output_value(pline, dent_id, in_dency_ids, args_mngr)
#
#    return self.call_processor(pline, prop_id, prop, func_prop_value, args_mngr)
#
#  def eval_property(self, pline, prop_id, prop):
#    if prop_id in pline.changed_track:#Has changed?
#      if has_flags(prop.type,FUNCTION_PROPERTY_FLAG): #is a function, then evaluate it 
#        self.eval_function(pline, prop_id, prop)
#      else:
#        #We are going to evaluate it, remove from changed
#        pline.changed_track.remove(prop_id)
#        dencies = pline.get_topology().connections.dpdencies[prop_id]
#        #It has one dependency? It should be a Function or an InOutProperty 
#        if len(dencies) == 1:
#          dency_id = dencies[0] 
#          dency_prop = pline.all_properties[dency_id]
#          if has_flags(dency_prop.type, FUNCTION_PROPERTY_FLAG):
#            self.eval_function(pline, dency_id, dency_prop)
#          else: #Connected to another property
#            return self.eval_property(pline, dency_id, dency_prop)      
#        elif len(dencies) > 1:
#          for dency_id in dencies:
#            dency_prop = pline.all_properties[dency_id]
#            if has_flags(dency_prop.type, FUNCTION_PROPERTY_FLAG):
#              self.eval_function(pline, dency_id, dency_prop)
#            else: #TODO: review this
#            #elif not has_flags(dency_prop.type, FUNCTUM_PROPERTY_FLAG):
#              log_warning("For prop_id: %r "%prop_id)
#              log_warning("A common (in/out/internal) property shouldn't be connected to functions and other properties")
#    return prop_id,prop
    
def shedskin_PipelineEvaluatorBase(context_lo, pline, prop):
  pe = PipelineEvaluatorBase(context_lo)
#  prop_id = 100
#  pline.all_properties[prop_id] = prop
#  pe.eval_function(pline, prop_id, prop)
#  pe.eval(pline, prop_id, True)
#  pe.animate(pline, prop_id)  
#  pe.eval_property(pline, prop_id, prop)
  return pe
        
if __name__ == "__main__":
  pass
