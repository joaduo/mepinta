#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
from deployment_config import configurePythonPaths

if __name__ == "__main__":
  context = configurePythonPaths()
  from mepinta_devtools.dev_manager_cli.DevelopmentManagerCli import DevelopmentManagerCli
  DevelopmentManagerCli(context).run(os.path.dirname(__file__))
