# -*- coding: utf-8 -*-

find ./ -iname "*.py" | while read line ; do if [[ "" != "$(cat $line)" ]]; then cp $line $temp; cat $header $temp > $line ; fi done