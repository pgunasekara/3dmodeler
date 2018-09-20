## OpenGL 3D Modeling Software
#####COMP SCI 3GC3 - COMPUTER GRAPHICS : Assignment 3

Group: Pasindu Gunasekara, Roberto Temelkovski

Implements a scene graph data structure to add various 3D objects and transformations.

### Compilation Instructions
OpenGL, FreeGLUT 3, g++, and the make utility are required to be installed for the makefile to properly compile.
````
make
```
Make will automatically execute the compiled binary.

To clean up the directory, run
```
make clean
```

### Known Issues:
* Sometimes deleting an object may not automatically select a deselected node.
* When Changing materials, you cannot change the material of the first node without first changing the material of the second node added. I'm not entirely sure why this happens. Changing materials works perfectly fine after you change any other node before the first one.

### Extra Notes:
* Sometimes on Linux or OSX the main file object generation may not work. For Linux, it's because the c++11 flag is not included for some reason. If so, run the following commands instead:
```
g++ -std=c++11 -c -o main.o main.cpp
make
```

* If you recieve an error about incorrect architecture on OSX, run the following commands instead:
```
g++ -std=c++11 -arch x86_64  -c -o main.o main.cpp
make
```
