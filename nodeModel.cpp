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

	currentMat = mat1;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	switch (modelType){
	case Sphere:
		glutSolidSphere(1, 12, 10);
		break;
	case Cube:
		glutSolidCube(1);
		break;
	case Teapot:
		glutSolidTeapot(1);
		break;
	case Cone:
		glutSolidCone(1,1,12,10);
		break;
	case Cylinder:
		//TRANSFORM THIS INTO A CYLINDER
		//TODO*****************************************************
		glutSolidCone(1,1,12,10);
		break;
	case Torus:
		glutSolidTorus(0.5,1,12,12);
		break;
	case Tetrahedron:
		glutSolidTetrahedron();
		break;
	case Dodecahedron:
		glutSolidDodecahedron();
		break;
	case Icosahedron:
		glutSolidIcosahedron();
		break;
	case Custom:
		//own mesh thing
		break;
	}
}