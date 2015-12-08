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

Node::Node(){	//constructor
	ID = getID();
	nodeType = root; //base class will be only really our root node, so lets do that
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;
	//printf("node init done\n");
}

//==================================================================
//function which does all the heavy lifting
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

//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN 
//DERIVED CLASSES

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}