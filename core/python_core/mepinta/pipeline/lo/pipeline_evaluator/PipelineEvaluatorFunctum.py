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

from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, INPUT_PROPS, \
    OUTPUT_PROPS, FUNCTUM_PROPERTY_FLAG, hasFlags, PROCESSOR_EXIT_NORMAL, \
    CUSTOM_INPUT_PROPS, CUSTOM_PROPERTY_FLAG, CUSTOM_OUTPUT_PROPS
from pipeline_backend.logging.logging import logDebug, logWarning
from pipeline_backend.void_pointer_casting.void_pointer_casting import voidp_to_FunctumPropertyValue, \
    voidp_to_FunctionPropertyValue
from mepinta.pipeline.lo.pipeline_evaluator.ProcessorArgsManager import ProcessorArgsManager
from pipeline_backend.args_management.args_management import getFunctumStructVoidp
from mepinta.pipeline.lo.pipeline_evaluator.base import PipelineEvaluatorBase
from mepinta.pipeline.lo.pipeline_data.data_model import PropertyValuePointer
#from mepinta.pipeline.lo.reentrant.data_model import ProcessorContext

# TODO: rename to PipelineEvaluator


class PipelineEvaluatorFunctum(PipelineEvaluatorBase):

    '''
    Evaluates a Pipeline(lo) given a property.
    This means it visits all dependencies in the graph recursively until it
      evaluates the desired property.
    It stops evaluating a recursion branch when there are no more changed
      dependencies or it founds a cyclic connection.
    If the Property is not marked as changed, it won't be evaluated.
    '''

    def __callProcessor(self, pline, prop_id, prop, func_prop_value, args_mngr):
        '''
        Calls the processor function (solving its function pointer) passign the
          mepinta_args structure as the only argument.
        Functions return a int with a code associated.
        :param pline:
        :param prop_id:
        :param prop:
        :param func_prop_value:
        :param args_mngr:
        '''
        func_ptr = self.context_lo.functions[
            func_prop_value.func_id].getFuncPointer()
        # TODO: if using long on shedkin, then casting should be applied
        logDebug("Entering processor function '%s'." % prop.name)
        exit_status = self.func_caller.callProcessorFunc(
            func_ptr, args_mngr.getArgs())
        logDebug("Leaving processor function '%s'." % prop.name)
        if exit_status != PROCESSOR_EXIT_NORMAL:
            # TODO: fix this on python should log as error when fixed
            logDebug("Processor function '%s' with unnormal exit status: %r." %
                     (prop.name, exit_status))

        if prop_id in pline.marked_outputs:
            # We have a propagation filter. (conditional evaluation)
            # Then it must create its changed set
            return args_mngr.buildChangedSet()
        return None

    def evaluateProp(self, pline, prop_id):
        '''
        Evaluates the pipeline to determine the value of the property that
          matched the prop_id given.
        Navigates properties backwards recursively (from dependents to dependencies)
          to generate a forward propagation (from dependencies to dependents) of
          evaluation of each property. (thus satisfying each property depedendecies
          on evaluation)
        :param pline: a Pipeline (lo) instance
        :param prop_id: the id of the property to be evaluated
        :return: tuple of (prop_id, prop) where prop_id and prop is the really
          evaluated prop
        '''
        prop = pline.all_properties[prop_id]
        return self.__evalProperty(pline, prop_id, prop)

    def __evalFunction(self, pline, prop_id, prop):
        '''
        When a function node is found, means it has to be evaluated. But before
          evaluating a function all its changed dependencies must be evaluated.
        So it will call recursively __evalProperty and __evalFunction.
        Once all are evaluated it will call the processor's functions passing the
          args structure as only argument. build with :class:`ProcessorArgsManager`
        '''
        logDebug('Evaluating function with prop_id=%r' % prop_id)
        # TODO: review if this code is necessary.
        # Already visited on this evaluation round?
        if not prop_id in pline.changed_track:
            return None
        pline.changed_track.remove(prop_id)  # Mark as visited for this round

        func_prop_value = voidp_to_FunctionPropertyValue(prop.getValue())
        inputs_ids = pline.getTopology().connections.dpdencies[prop_id]
        outputs_ids = pline.getTopology().connections.dpdents[prop_id]
        args_mngr = ProcessorArgsManager(
            self.context_lo, func_prop_value, thread_id=0)

        #processor_context = ProcessorContext(self.context_lo, pline, self)
        # args_mngr.setProcessorContext(processor_context)

        # Iterate over the processor's Inputs
        for input_id in inputs_ids:
            self.__inputValue(pline, input_id, args_mngr)

        # Iterate over the processor's Outputs
        for dent_id in outputs_ids:
            self.__outputValue(pline, dent_id, args_mngr)

        return self.__callProcessor(pline, prop_id, prop, func_prop_value, args_mngr)

    def __inputValue(self, pline, input_id, args_mngr):
        '''
        Will evaluate an input value wether it's a function or a data property.
        Once a property is evaluated it can be added o the args to be passed to the
          function we are gathering dependencies for. (via args_mngr)
        :param pline: :class:`Pipeline` instance object
        :param input_id: property id of the input property to be evaluated
        :param args_mngr: instance of :class:`ProcessorArgsManager` to gather args
          into
        '''
        input_prop = pline.all_properties[input_id]
        if hasFlags(input_prop.type, CUSTOM_PROPERTY_FLAG):
            args_mngr.setInOut(CUSTOM_INPUT_PROPS)
        else:
            args_mngr.setInOut(INPUT_PROPS)

        if hasFlags(input_prop.type, FUNCTION_PROPERTY_FLAG):
            # Its a function, then evaluate it
            self.__evalFunction(pline, input_id, input_prop)
            return input_id
        else:
            changed = input_id in pline.changed_track
            # TODO: (performance) review if it can avoid adding the prop to the
            # args. Cached args!
            _, dency_prop = self.__evalProperty(pline, input_id, input_prop)
            # TODO: review it we really need to initialize properties
            #self.p_value_mngr.init_set_prop_value(input_prop, input_dency_prop.getValuePtr())
            args_mngr.append(input_id, input_prop, dency_prop)
            if changed:
                # Optimization: Used for conditional processing.
                args_mngr.changedValue()
            else:
                # Optimization: Used for conditional processing.
                args_mngr.unchangedValue()
            # this method is useful if we avoid adding a prop not changed
            #(used for args caching, WIP)
            args_mngr.nextProp()
            return input_id

    def __outputValue(self, pline, out_id, args_mngr):
        '''
        Will gather all output "args" for a processor's functions into the args
          structure managed by args_mngr instance.
        :param pline: :class:`Pipeline` instance object
        :param input_id: property id of the output property to be later evaluated
        :param args_mngr: instance of :class:`ProcessorArgsManager` to gather output
          args into
        '''
        out_prop = pline.all_properties[out_id]
        if hasFlags(out_prop.type, CUSTOM_PROPERTY_FLAG):
            args_mngr.setInOut(CUSTOM_OUTPUT_PROPS)
        else:
            args_mngr.setInOut(OUTPUT_PROPS)

        if out_id in pline.changed_track:
            pline.changed_track.remove(out_id)

        # Its a data property, so we will output on them
        if not hasFlags(out_prop.type, FUNCTION_PROPERTY_FLAG):
            # we need to make sure output data is initialized
            self.p_value_mngr.initPropValue(out_prop)
            args_mngr.append(out_id, out_prop, out_prop)
            # Resets its status for optimization techniques (conditional
            # evaluation)
            args_mngr.unchangedValue()
            # Properties are in certain order (used for args caching, WIP)
            args_mngr.nextProp()

    def __solveNonCached(self, pline, out_id, out_prop):
        '''
        out_prop its in cached_link, means its possible to have (non-)cached links.
          out_prop <- input_prop
        First it evaluates the input_prop.
        Checks if non-caching is enabled for this (non-cached capable) link:
          - If stealing is possible calls __stealInput method
          - If not, copies the data from input_prop into out_prop
        :param pline:
        :param out_id:
        :param out_prop:
        '''
        input_id = pline.cached_link.getFirst(out_id)
        input_prop = pline.all_properties[input_id]
        input_id, input_prop = self.__evalProperty(pline, input_id, input_prop)
        if out_id in pline.getTopology().cached:
            # We are caching on this node, then we must copy values
            logDebug('Copying value for property:%r id=%r' %
                     (out_prop.name, out_id))
            self.p_value_mngr.copyPropValue(out_prop, input_prop.getValuePtr())
        else:
            # We can directly pass the value_pointer
            self.__stealInput(pline, out_id, out_prop, input_id, input_prop)

    def __stealInput(self, pline, out_id, out_prop, input_id, input_prop):
        '''
        Steals data from an input_prop into out_prop. Thus working as a big memory
          optimization on linear pipelines. (always working on the same data)
        Using non-cached links requires a higher analysis, since it requires
          linear "sub-pipelines" and this class does not check so.
        In fact, in the case of K-3d, data uses copy-on-write policy, so this
          optimization is unnecessary in such case.
        :param pline: Pipeline (lo) instance
        :param out_id: property id of the out_prop parameter
        :param out_prop: "output" property of the cached link context
        :param input_id: property id of the input_prop parameter
        :param input_prop: "input" property of the cached link context
        '''
        # TODO: create a ValuePointerStealer? What for?
        # If we steal a value of an unchanged property, we will run into problems
        # We must fix that situation
        # Also we can only steal a value when its pointed only by one prop (the non_cached input)
        # if not, we need to copy it as many time as the stealing needs
        logDebug(
            'Non cached properties should be used in a restricted context.')
        logDebug('Stealing value for property:%r id=%r from property:%r id=%r' %
                 (out_prop.name, out_id, input_prop.name, input_id))
        # Need to do this first, if not the value will be freed
        self.p_value_mngr.setPropValuePointer(
            out_prop, input_prop.getValuePtr())
        logDebug('Detaching from previous property:%r id=%r' %
                 (input_prop.name, input_id))
        # Create a value pointer with None as value #TODO: relies on garbage
        # collector
        vpointer_none = PropertyValuePointer()
        # Ok, you do not own the previous value anymore.
        self.p_value_mngr.setPropValuePointer(input_prop, vpointer_none)
        # input changed (we stole it's value and needs to propagate the change)
        pline.getTopology().changed_primary.add(input_id)

    def __evalFunctum(self, pline, prop_id, prop):
        '''
        Evaluates all the dependencies of a functum, and packs function and
        dependencies together for later evaluation.
        '''
        logDebug("Evaluating functum with prop_id=%r" % prop_id)
        # TODO: review if this code is necessary.
        functum_prop_value = voidp_to_FunctumPropertyValue(prop.getValue())
        inputs_ids = pline.getTopology().connections.dpdencies[prop_id]
        outputs_ids = pline.getTopology().connections.dpdents[prop_id]
        args_mngr = ProcessorArgsManager(
            self.context_lo, functum_prop_value, thread_id=0)
        # Already visited on this evaluation round?
        if prop_id in pline.changed_track:
            # Mark as visited for this round
            pline.changed_track.remove(prop_id)

        # args_mngr.setInOut(INPUT_PROPS)
        # Iterate over the processor's Inputs
        for input_id in inputs_ids:
            self.__inputValue(pline, input_id, args_mngr)

        # args_mngr.setInOut(OUTPUT_PROPS)
        # Iterate over the processor's Outputs
        for dent_id in outputs_ids:
            self.__outputValue(pline, dent_id, args_mngr)

        functum_prop = functum_prop_value.getFunctumProp()
        if functum_prop.getValue() == None:
            func_ptr = self.context_lo.functions[
                functum_prop_value.func_id].getFuncPointer()
            functum_struct = getFunctumStructVoidp(
                func_ptr, args_mngr.getArgs())
            self.p_value_mngr.replacePropValue(functum_prop, functum_struct)
        # else:pass
        # TODO:IMPORTANT it's caching here beware! args should be ok, but
        # func_ptr may change
        return prop_id, functum_prop

    def __evalFunctumOrDependency(self, pline, prop_id, prop):
        dencies = pline.getTopology().connections.dpdencies[prop_id]
        if len(dencies) == 1:  # Check if connected to other functum
            dency_id = dencies[0]
            dency_prop = pline.all_properties[dency_id]
            if hasFlags(dency_prop.type, FUNCTUM_PROPERTY_FLAG):
                # Its a functum connected to other functum
                return self.__evalFunctumOrDependency(pline, dency_id, dency_prop)
        return self.__evalFunctum(pline, prop_id, prop)

    def __evaleDataProperty(self, pline, prop_id, prop):
        '''
        Evaluates an Data property. Will iterate over and evaluate all its
        dependencies. Dependencies could be:
          - One or more functions (will evaluate all of them and return the prop)
          - One data property (solve its value and return it)

        :param pline: Pipeline (lo) instance
        :param prop_id: property id of the prop parameter
        :param prop: pipeline's Property
        :return: tuple of (prop_id, prop) where prop_id and prop is the really
          evaluated prop
        '''
        # Get all connected dependencies of a prop_id in the topology
        dencies = pline.getTopology().connections.dpdencies[prop_id]
        logDebug("Evaluating property with prop_id=%r" % prop_id)
        # We assume the property hasn't changed
        changed = False
        if prop_id in pline.changed_track:  # Has changed?
            changed = True
            logDebug("Removing changed Property with prop_id=%r" % prop_id)
            # Mark as visited for this round
            pline.changed_track.remove(prop_id)
            if prop_id in pline.cached_link:
                # its in cached_link => its possible to have (non-)cached links
                self.__solveNonCached(pline, prop_id, prop)
        # Iterate over
        for dency_id in dencies:
            dency_prop = pline.all_properties[dency_id]
            if hasFlags(dency_prop.type, FUNCTION_PROPERTY_FLAG):
                if changed:
                    # Only evaluateProp function if property was notified of a
                    # change
                    self.__evalFunction(pline, dency_id, dency_prop)
            else:
                if len(dencies) == 1:
                    return self.__evalProperty(pline, dency_id, dency_prop)
                else:
                    # Connected to several InOutProperties
                    msg = ('A common (in/out/internal) property shouldn\'t be connected '
                           'to functions and other properties.For prop_id: %r' % prop_id)
                    logWarning(msg)
        if changed:  # It's a leaf property, the value may be uninitialized
            self.p_value_mngr.initPropValue(prop)
        return prop_id, prop

    def __evalProperty(self, pline, prop_id, prop):
        '''
        Distinguish between functions, functums and data properties.
        Calls each evaluation function depending on its type.
        :param pline: Pipeline (lo) instance
        :param prop_id: property id of the prop parameter
        :param prop: pipeline's Property
        :return: tuple of (prop_id, prop) where prop_id and prop is the really
          evaluated prop
        '''
        # Distinguish between property's types and call the corresponding
        # function
        if hasFlags(prop.type, FUNCTION_PROPERTY_FLAG):
            # is a function, then evaluate it
            self.__evalFunction(pline, prop_id, prop)
            return prop_id, prop
        else:
            if hasFlags(prop.type, FUNCTUM_PROPERTY_FLAG):
                # Its a functum (datum + function)
                return self.__evalFunctumOrDependency(pline, prop_id, prop)
            else:  # Its a data property
                return self.__evaleDataProperty(pline, prop_id, prop)


def shedskin_PipelineEvaluatorFunctum(context_lo, pline, prop, args_mngr):
    pe = PipelineEvaluatorFunctum(context_lo)
    prop_id = 100
    pline.all_properties[prop_id] = prop
    #pe.__evalFunction(pline, prop_id, prop)
    pe.evaluateProp(pline, prop_id)
    #pe.animate(pline, prop_id)
    #pe.__evalProperty(pline, prop_id, prop)
