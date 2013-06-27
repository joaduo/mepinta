#!/usr/bin/python
# -*- coding: utf-8 -*-

from deployment_config import configurePythonPaths

if __name__ == "__main__":
  context = configurePythonPaths()
  from mepinta_devtools.demo.MepintaDemo import MepintaDemo
  MepintaDemo(context).run()
