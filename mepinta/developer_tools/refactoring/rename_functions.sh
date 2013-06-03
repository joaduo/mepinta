grep -e "def\s" -Rhi ./ | egrep -e "[a-z]+_([a-z_]+)\(" | egrep  "__[a-z_]+__" -v | sed -r 's/.*def\s+([a-z_]+)\(.*/\1/g'

find ./ -iname "*.py" -exec grep "def\s" -Rhi {} \; | egrep  "[a-z0-9]+_([a-z0-9_]+)\(" | egrep  "__[a-z0-9_]+__" -v | sed -r 's/.*def\s+([a-z0-9_]+)\(.*/\1/g'

