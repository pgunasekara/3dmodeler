#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "sceneGraph.h"
#include "node.h"
#include "Math/math3D.h"
#include <stdio.h>
#include <math.h>

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
	printf("scene graph init done\n");
	// R0
	vec3D near = vec3D();
	// R1
	vec3D far = vec3D(1,1,1);
	vec3D distance = (far - near).normalize();
	start = near.returnDoubleArray();
	finish = far.returnDoubleArray();

	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport); 
	printf("window calculations done\n");
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
	currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i){
	if (i < currentNode->children->size() && i >= 0)
		currentNode = currentNode->children->at(i);
	else
		printf("child out of range");
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
	currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
	//TODO
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}

bool SceneGraph::Intersect(int x, int y){
	//unproject the values
	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	printf("%f %f %f %f %f %f\n",start[0],start[1],start[2],finish[0],finish[1],finish[2]);
	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
         viewport, &start[0], &start[1], &start[2]); 

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
         viewport, &finish[0], &finish[1], &finish[2]); 

	printf("%f %f %f %f %f %f\n",start[0],start[1],start[2],finish[0],finish[1],finish[2]);

	//vec3D Ray = vec3D(distance.dot(distance),near.dot(distance) * 2.0,near.dot(near) - 1);
	
	double a,b,c;
	a = distance.dot(distance);
	b = near.dot(distance) * 2.0;
	c = near.dot(near) - 1;

	printf("%f %f %f\n",a,b,c);

	double sq = b*b  - 4*a*c;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * b + sqrt(sq))/(2*a);
		t1 = ((-1) * b - sqrt(sq))/(2*a);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
		return true;
	}

	return false; //else returns false

}
