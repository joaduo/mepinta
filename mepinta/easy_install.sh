#!/bin/bash

if [ -a "deploy.py" ] ; then
  echo "You should run easy_install.sh only the first time you download mepinta."
  echo "Use the deploy command for a new deployment."
  exit 0
fi

$DEPLOY_DIR="../../mepinta_deployment"

#download nodebox gl (optional
wget http://mepinta.googlecode.com/files/nodebox-gl-1.6-mepinta.tar.gz
tar -xzf nodebox-gl-1.6-mepinta.tar.gz

#download mepinta
git clone https://code.google.com/p/mepinta/
cd mepinta/mepinta

#deploy it
deploy.py $DEPLOY_DIR
cd $DEPLOY_DIR

#Lists the demos
export PYTHONPATH="$PYTHONPATH:../nodebox-gl-1.6-mepinta.tar"
./mepinta_demo.py     
