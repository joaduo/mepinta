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
        #cmd="sed 's/$FROMTX/$TOTX/g' $f | sed '/$TOTX/ p' -n"
        cmd="sed 's/$FROMTX/$TOTX/g' $f | grep '$TOTX' --color"
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
      echo "$cmd" | grep "$TOTX" --color
      if [ "$1" = "-y" ] ; then
        eval $cmd
      fi
    done 
  done 
}

RENAMING_DICT="EclipseCoreProjectTemplates EclipsePydevProjectTemplates
EclipseCoreProjectCreator EclipsePydevProjectCreator"

# FILES=$(find ./ -iname "*.cpp"); replace_in_text $1
# FILES=$(find ./ -iname "*.hpp"); replace_in_text $1
# FILES=$(find ./ -iname "*.c"); replace_in_text $1
# FILES=$(find ./ -iname "*.h") ; replace_in_text $1

FILES=$(find ./ -iname "*.py") ; replace_in_text $1

FILES_RENAMING_DICT=$RENAMING_DICT
rename_files $1

if [ "$1" = "-y" ] ; then
  echo "Running the commands!"
else
  echo "Not running commands!"
fi