#!/usr/bin/python
# -*- coding: utf-8 -*-

from deployment_config import configurePythonPaths

if __name__ == "__main__":
    configurePythonPaths(create_context=False)
    from mepinta.testing.plugins_testing.TestDiscoveryManager import TestDiscoveryManager
    TestDiscoveryManager().runAllTests()
