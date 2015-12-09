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
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentMat.current->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentMat.current->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentMat.current->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentMat.current->shine);

	switch (modelType){
	case Sphere:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidSphere(0.7, 12, 10);
		break;
	case Cube:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidCube(1);
		/*if (current){	
			hit.draw();
		}*/
		break;
	case Cone:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidCone(1,1,12,10);
		break;
	case Cylinder:
		//TRANSFORM THIS INTO A CYLINDER
		//TODO*****************************************************
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidCone(1,1,12,10);
		break;
	case Torus:
		hit = Hitbox(vertex3D(-0.8,-0.8,-0.5), vertex3D(0.8,0.8,0.5), ID);
		glutSolidTorus(0.25,0.5,12,12);
		break;
	case Tetrahedron:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidTetrahedron();
		break;
	case Dodecahedron:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidDodecahedron();
		break;
	case Icosahedron:
		hit = Hitbox(vertex3D(-0.5,-0.5,-0.5), vertex3D(0.5,0.5,0.5), ID);
		glutSolidIcosahedron();
		break;
	case Custom:
		//own mesh thing
		break;
	}
}
/*
void NodeModel::applyChangesAxes(vec3D transform){
	xaxis = (xaxis + transform).normalize();
	yaxis = (yaxis + transform).normalize();
	zaxis = (zaxis + transform).normalize();
};
*/