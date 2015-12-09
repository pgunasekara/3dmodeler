#include "nodeModel.h"
#include <stdio.h> //needed for printf command

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Math/math3D.h"



NodeModel::NodeModel(ModelType whatType){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;

	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	xaxis = vec3D(1,0,0);
	yaxis = vec3D(0,1,0);
	zaxis = vec3D(0,0,1);
	//current = true;

	currentMat.toEmerald();
	method2 = false;
}

NodeModel::NodeModel(ModelType whatType,vertex3D min,vertex3D max){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;

	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	xaxis = vec3D(1,0,0);
	yaxis = vec3D(0,1,0);
	zaxis = vec3D(0,0,1);
	//current = true;

	currentMat.toEmerald();
	this->min = vertex3D(min.x,min.y,min.z);
	this->max = vertex3D(max.x,max.y,max.z);
	method2 = true;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentMat.current->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentMat.current->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentMat.current->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentMat.current->shine);

	if (method2){
		switch (modelType){
			case Sphere:
				hit = Hitbox(min, max, ID);
				glutSolidSphere(0.7, 12, 10);
				break;
			case Cube:
				hit = Hitbox(min, max, ID);
				glutSolidCube(1);
				break;
			case Cone:
				hit = Hitbox(min, max, ID);
				glutSolidCone(1,1,12,10);
				break;
			case Cylinder:
				//TRANSFORM THIS INTO A CYLINDER
				//TODO*****************************************************
				hit = Hitbox(min, max, ID);
				glutSolidCone(1,1,12,10);
				break;
			case Torus:
				hit = Hitbox(min, max, ID);
				glutSolidTorus(0.25,0.5,12,12);
				break;
			case Tetrahedron:
				hit = Hitbox(min, max, ID);
				glutSolidTetrahedron();
				break;
			case Dodecahedron:
				hit = Hitbox(min, max, ID);
				glutSolidDodecahedron();
				break;
			case Icosahedron:
				hit = Hitbox(min, max, ID);
				glutSolidIcosahedron();
				break;
			case Custom:
				//own mesh thing
				break;
			}
	}else {
		switch (modelType){
		case Sphere:
			hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
			glutSolidSphere(0.7, 12, 10);
			break;
		case Cube:
			hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
			glutSolidCube(0.8);
			break;
		case Cone:
			hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
			glutSolidCone(0.6,0.6,12,10);
			break;
		case Torus:
			hit = Hitbox(vertex3D(-0.8,-0.8,-0.5), vertex3D(0.8,0.8,0.5), ID);
			glutSolidTorus(0.20,0.4,12,12);
			break;
		case Tetrahedron:
			hit = Hitbox(vertex3D(-1.0,-1.0,-1.0), vertex3D(1.0,1.0,1.0), ID);
			glutSolidTetrahedron();
			break;
		}
	}
}