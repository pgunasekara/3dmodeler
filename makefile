LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -std=c++11 -w
CC=g++
EXEEXT=
RM=rm

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
	# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

PROGRAM_NAME=assignment_3_gunasepi_temelkr

#run target to compile and build, and then launch the executable
run: object $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

object: main.cpp node.cpp nodeGroup.cpp nodeModel.cpp nodeTransform.cpp sceneGraph.cpp Math/math3D.cpp Math/camera.cpp Math/Hitbox.cpp materials.cpp
	$(CC) -std=c++11 -c -o main.o main.cpp
	$(CC) -std=c++11 -c -o node.o node.cpp 
	$(CC) -std=c++11 -c -o nodeGroup.o nodeGroup.cpp 
	$(CC) -std=c++11 -c -o nodeModel.o nodeModel.cpp 
	$(CC) -std=c++11 -c -o nodeTransform.o nodeTransform.cpp 
	$(CC) -std=c++11 -c -o sceneGraph.o sceneGraph.cpp 
	$(CC) -std=c++11 -c -o Math/math3D.o Math/math3D.cpp 
	$(CC) -std=c++11 -c -o Math/camera.o Math/camera.cpp 
	$(CC) -std=c++11 -c -o Math/Hitbox.o Math/Hitbox.cpp 
	$(CC) -std=c++11 -c -o materials.o materials.cpp


$(PROGRAM_NAME): main.o node.o nodeGroup.o nodeModel.o nodeTransform.o sceneGraph.o Math/math3D.o Math/camera.o Math/Hitbox.o materials.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o Math/*.o save.txt $(PROGRAM_NAME)$(EXEEXT)
