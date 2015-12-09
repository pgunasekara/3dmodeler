#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>	
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "Math/Hitbox.h"
#include "Math/math3D.h"

//Header for Model nodes

class NodeModel:public Node{
public:
	NodeModel(ModelType whatType);	//constructor
	NodeModel(ModelType whatType,vertex3D min, vertex3D max);
	

	Vector3D position, rotation, scale;

	bool current;
	Hitbox hit;

	vec3D tr;
	vec3D sc;
	quaternion rot;
	vertex3D min,max;
	bool method2;

	//Bounding box information is already specified in the math library

	virtual void nodeSpecificCodeDown();
};

#endif