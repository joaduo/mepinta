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

RENAMING_DICT="pipeline\\\/lo mepinta\\\/pipeline\\\/lo
__pipeline__::__lo__ __mepinta__::__pipeline__::__lo__"

FILES=$(find ./ -iname "*.cpp"); replace_in_text $1
FILES=$(find ./ -iname "*.c"); replace_in_text $1
FILES=$(find ./ -iname "*.h") ; replace_in_text $1

# FILES=$(find ./ -iname "*.py") ; replace_in_text $1

FILES_RENAMING_DICT=""
# rename_files $1

if [ "$1" = "-y" ] ; then
  echo "Changes applied!"
else
  echo "Smoke mode!"
fi
