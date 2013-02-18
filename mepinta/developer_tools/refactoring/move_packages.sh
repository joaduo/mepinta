# exit 0
# egrep -r "def\s[a-z_]+\(" alldefs.txt  | egrep -r "__[a-z_]+__" -v
# grep "def\s" -Rh  ./ > ../alldefs.txt

packages='abstract
context
pipeline
pipelineview
plugins_creation
plugins_manager
plugins_manifest'

#packages='plugins_manager'

# packages='plugins_manifest'

for pkg in $packages; do
  for f in $(find ./ -iname "*.py"); do
    if [ "$1" = "-y" ] ; then
      sed -r 's/from\s'$pkg'(\s|\.)/from mepinta\.'$pkg'\1/' -i $f
    else
      sed -r 's/from\s'$pkg'(\s|\.)/from mepinta\.'$pkg'\1/' $f | grep -r "from\s.*$pkg.*import\s" --color
    fi
  done
done

if [ "$1" != "-y" ] ; then
  echo "Smoke mode. run '$0 -y' to apply changes"
fi
