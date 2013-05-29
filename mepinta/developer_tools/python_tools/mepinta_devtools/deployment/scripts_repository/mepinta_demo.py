#!/usr/bin/python
# -*- coding: utf-8 -*-

from deployment_config import configurePythonPaths

if __name__ == "__main__":
  configurePythonPaths()
  from default_context import getDefaultContext
  from plugins_tests.demo.MepintaDemo import MepintaDemo
  MepintaDemo(getDefaultContext()).run()
