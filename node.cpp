#include "node.h"
#include <stdio.h>
#include "structs.h"
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//Constructor for a node
//Initially the node will be a root node, until changed
Node::Node(){
	ID = getID();
	nodeType = root;
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;

	currentMat = cMaterial();

	//printf("node init done\n");
}


//This function will reursively draw the Nodes
void Node::draw(){
	//printf("nodeType: %i\n", nodeType);
	//we entered node, so execute the commands
	//ie. push matrix, apply material, draw geometry, etc.
	nodeSpecificCodeDown();

	//recursively call our children
	const int numberOfChildren = children->size();
	if (numberOfChildren > 0){
		for (int i = 0; i < numberOfChildren; i++){
			glColor3f(0,0,1);
			children->at(i)->draw();
			if (children->at(i)->current && children->at(i)->nodeType == model){	
				children->at(i)->hit.draw();
			}
		}
	}

	//we are exiting the node, so execute the commands
	//ie. pop matrix, etc.
	nodeSpecificCodeUp();
}

//These functions are used by the inherting classes
void Node::nodeSpecificCodeDown(){}
void Node::nodeSpecificCodeUp(){}