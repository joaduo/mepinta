This project aims to create a suite of graphics tools based on plugins.

Right now the core of the project is functional. This core supports some cool features like:
  1. On the fly plugin loading and reloading. Means you can change the plugin version.(plugins in C, C++ and Python)
  1. Separate data types from core library (the core is data type's agnostic).
  1. Fault tolerant plugin system (WIP, although some features are implemented).
  1. Smooth plugin testing system (automatic reloading and testing of .so libraries).
  1. Easy to write plugin manifest and implementation. (minium sdk needed)
  1. Python, C and C++ plugins are treated in the same way.
  1. Fast pipeline evaluation through translation of Python to C++ code. (with shedskin)
  1. Easy backward compatibility of plugins. (the system will load any plugin, no matter the sdk used)

With these features supported the next step of the project aims making easier to deploy and create new plugins.

Below you can see a test of the core.

![http://mepinta.googlecode.com/files/Mepinta_2D_Geometry.png](http://mepinta.googlecode.com/files/Mepinta_2D_Geometry.png)

2D vectorial geometry with a deformation expression applied.