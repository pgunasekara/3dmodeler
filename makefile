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
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

$(PROGRAM_NAME): main.o node.o nodeGroup.o nodeModel.o nodeTransform.o sceneGraph.o Math/math3D.o Math/camera.o Math/Hitbox.o materials.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o Math/*.o save.txt $(PROGRAM_NAME)$(EXEEXT)
