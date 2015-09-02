
#!/bin/bash

DEPLOY_DIR="mepinta_deployment"

if [ -e "deploy.py" ] ; then
  echo "You should run easy_mepinta_install.sh only the first time you download mepinta."
  echo "Use the deploy command for a new deployment."
  exit 0
elif [ -e "mepinta" ] ; then
  echo "You probably already installed mepinta"
  exit 0
fi

#download nodebox gl (optional
wget http://mepinta.googlecode.com/files/nodebox-gl-1.6-mepinta.tar.gz
tar -xzf nodebox-gl-1.6-mepinta.tar.gz

#download mepinta
git clone https://code.google.com/p/mepinta/

#deploy it
python ./mepinta/mepinta/deploy.py $DEPLOY_DIR

#Final Message
echo "

Finished installing.

For Running demos do:
  cd $DEPLOY_DIR
  export PYTHONPATH=\"\$PYTHONPATH:../nodebox-gl-1.6-mepinta\"
  #Finally
  ./mepinta_demo.py

"
