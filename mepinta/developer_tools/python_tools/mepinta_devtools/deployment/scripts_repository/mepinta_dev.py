#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
from deployment_config import configurePythonPaths, deployment_config

if __name__ == "__main__":
  context = configurePythonPaths()
  from mepinta_devtools.dev_manager_cli.DevelopmentManagerCli import DevelopmentManagerCli
  DevelopmentManagerCli(context).run(deployment_config.mepinta_source_path, os.path.dirname(__file__))
