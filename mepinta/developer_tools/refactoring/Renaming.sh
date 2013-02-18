#!/bin/bash

function replace_in_text(){
  for f in $FILES ; do 
    #echo "On file $f"
    echo "$RENAMING_DICT" | while read LINE ; do
      FROMTX=$( echo "$LINE" | cut -d" " -f1)
      TOTX=$( echo "$LINE" | cut -d" " -f2)
      
      if [ "$1" = "-y" ] ; then
        cmd="sed 's/$FROMTX/$TOTX/g' -i $f"
      else
        cmd="sed 's/$FROMTX/$TOTX/g' $f | sed '/$TOTX/ p' -n"
      fi
      eval $cmd
    done 
  done
}

function rename_files(){
  echo "$FILES_RENAMING_DICT" | while read LINE ; do
    FROMTX=$( echo "$LINE" | cut -d" " -f1)
    TOTX=$( echo "$LINE" | cut -d" " -f2)

    PLUGIN_FILES=$(find ./ -name "*$FROMTX*")
    for f in $PLUGIN_FILES ; do
      new_f=$(echo "$f" | sed "s/$FROMTX/$TOTX/g")
      cmd="mv $f $new_f"
      echo "$cmd"
      if [ "$1" = "-y" ] ; then
        eval $cmd
      fi
    done 
  done 
}

OLD="pipeline.lower_level.data_model pipeline.lo.pipeline.data_model
pipeline_abslayer pipeline_backend
pipeline.lower_level.PropertyValueManager pipeline.lo.value_manager.PropertyValueManager
pipeline.lower_level.constants pipeline.lo.constants
pipeline.lower_level.PipelineManager pipeline.lo.topology_manager.PipelineManager
pipeline.higher_level.PipelineManager pipeline.hi.topology_manager.PipelineManager
pipeline.lower_level.PropertyValueSetterGetter pipeline.lo.value_manager.PropertyValueSetterGetter
pipeline.lower_level.PipelineEvaluator pipeline.lo.pipeline_evaluator.PipelineEvaluator
pipeline.lower_level.ProcessorArgsManager pipeline.lo.pipeline_evaluator.ProcessorArgsManager
pipeline.higher_level.SharedObjectLibraryLoader pipeline.hi.plugins_manager.SharedObjectLibraryLoader
pipeline.lower_level.SharedObjectLibraryLoader pipeline.lo.plugins_manager.SharedObjectLibraryLoader
pipeline.higher_level.PluginsManager pipeline.hi.plugins_manager.PluginsManager
pipeline.higher_level.NodeProxyManager pipeline.hi.plugins_manager.NodeProxyManager
pipeline.higher_level.data_model pipeline.hi.plugins_manager.data_model
pipeline.higher_level.base pipeline.hi.base
pipeline.higher_level.proxy pipeline.hi.plugins_manager.proxy
pipeline.lower_level.propagation pipeline.lo.pipeline_evaluator.propagation
pipeline.lower_level pipeline.lo
pipeline.higher_level pipeline.hi
pipeline.lo.pipeline pipeline.lo.pipeline_data
pipeline.hi.pipeline pipeline.hi.pipeline_data
pipeline.lo.storage pipeline.lo.pipeline_data.storage
pipeline.hi.plugins_manager_detail pipeline.hi.plugins_manager.plugins_manager_detail
pipeline.lo.pipeline_data_evaluator pipeline.lo.pipeline_evaluator
PipelineManager TopologyManager
pipeline.hi.EnvironmentGetter configuration.EnvironmentGetter
pipeline.hi.pipelines_manager.PipelinesManager pipelineview.pipelines_manager.PipelinesManager
"

NEW_REFACTORING="pipeline.lo.plugins_manager.SharedObjectLibraryLoader pipeline.lo.plugin_loader.PluginLoader
pipeline.hi.plugins_manager.SharedObjectLibraryLoader pipeline.hi.plugin_loader.PluginLoader
SharedObjectLibraryLoader PluginLoader
PipelineValuePointer PropertyValuePointer
IdIndexedTable DirectedGraph
PropertyValueSetterGetter ValueManager
NodeProxyManager NodeManager
pipeline.hi.plugins_manager.proxy.NodeProxy pipelineview.graph.data_model
NodeProxy Node
NodeTopologyManager GraphTopologyManager
ImplementationSwitcher BackendSwitcher
HiClass HiBase
get_switched_class get_wrapped_class
common_data context_lo
CommonData ContextLo
pipeline.lo.pipeline_context.PipelineContext pipeline.lo.context_lo.ContextLo
env context
context.config context
enviroment_name context_name
lower_level_language backend_name
pipeline.hi.plugins_manager.proxy.ProcessorProxy pipeline.proxy.data_model
pipeline.proxy.data_model proxy.data_model
DefinitionBase PluginManifestBase
plugins.base plugins_manifest
"

RENAMING_DICT="plugins.creation mepinta.plugins_creation
plugins.manager mepinta.plugins_manager
plugins.manifest mepinta.plugins_manifest"

# FILES=$(find ./ -iname "*.cpp"); replace_in_text $1
# FILES=$(find ./ -iname "*.hpp"); replace_in_text $1
# FILES=$(find ./ -iname "*.c"); replace_in_text $1
# FILES=$(find ./ -iname "*.h") ; replace_in_text $1

FILES=$(find ./ -iname "*.py") ; replace_in_text $1

FILES_RENAMING_DICT=""
# rename_files $1

if [ "$1" = "-y" ] ; then
  echo "Running the commands!"
else
  echo "Not running commands!"
fi
