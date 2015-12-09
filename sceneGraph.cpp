//Main Scene Graph code, some of it was already written by Dr. Gwosdz and put on avenue

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <fstream>

#include "sceneGraph.h"
#include "node.h"
#include "Math/math3D.h"
#include "Math/Hitbox.h"
#include <stdio.h>
#include <math.h>

//Constructor, creates the first root node
SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;

	currentNode->current = true;
	// R0
	vec3D near = vec3D();
	// R1
	vec3D far = vec3D(1,1,1);
	vec3D distance = (far - near).normalize();
}

//Goes to the root node of the Graph
void SceneGraph::goToRoot()
{
	currentNode = rootNode;
}

//Go to an ID in the scene Graph
void SceneGraph::goToChild(int i)
{
	if (i < currentNode->children->size() && i >= 0)
	{
		currentNode = currentNode->children->at(i);
	}
	else
	{
		printf("Invalid node ID");
	}
}

//Go to the current nodes parent
void SceneGraph::goToParent()
{
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

void SceneGraph::transformNode(Node *node)
{

	if(node->nodeType == transformation)
	{
	}
}

//Add a child node underneath the Current node
//If it is a model node, then usually a tranformation node is inserted above it as the initial translation at the origin 0,0,0
void SceneGraph::insertChildNodeHere(Node *node)
{
	//add our parent to our child node
	node->parent = currentNode;
	//Add the new child to the parents children vector
	currentNode->children->push_back(node);
	//Switch to the new current node
	//Add a new hitbox to the hitbox nodes
	if(node->nodeType == model)
	{	
		hitBoxNodes.push_back(node);
		for(int i = 0; i < hitBoxNodes.size(); i++)
		{
			hitBoxNodes.at(i)->current = false;
		}
		hitBoxNodes.at(hitBoxNodes.size()-1)->current = true;
	}
	//Switch to the newly created node
	//This will almost always at the end be a model node, unless theres nothing on the screen
	currentNode = node;
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode()
{
	//Remove the current node, check if it has subnodes, and relink to the node above this one
	//Delete Any dangling nodes

	SceneGraph::goToParent();
	currentNode->children->clear();
	//Also delete the hitbox

	//Go to a different hitbox

}

//draw the scenegraph
void SceneGraph::draw()
{
	//This will recursively start drawing within the Node class
	rootNode->draw();
}

//This will search for a node by it's ID
void SceneGraph::searchByID(int ID)
{
	//Search for the ID that the program gives, and set the currentNode to be the node from that ID
	Node *tmpnode = currentNode;

	//recursively call our children
	if(currentNode->ID != ID)
	{
		//Go to the top Node, and search all nodes
		currentNode = rootNode;

		const int numberOfChildren = currentNode->children->size();
		if (numberOfChildren > 0)
		{
			for (int i = 0; i < numberOfChildren; i++)
			{
				if(currentNode->children->at(i)->ID == ID)
				{
					currentNode = currentNode->children->at(i);
					break;
				}
			}
		}
	}
}


//Intersection Test, and selection of a hitbox using a mouse click
bool SceneGraph::Intersect(int x, int y)
{

	Node *currentNodeIntersect = rootNode;

	//grab the matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport); 

	start = near.returnDoubleArray();
	finish = far.returnDoubleArray();

	//unproject the values
	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
		 viewport, &start[0], &start[1], &start[2]); 

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
		 viewport, &finish[0], &finish[1], &finish[2]); 

	near.update(start);
	far.update(finish);
	distance = (far - near).normalize();

	double A,B,C;
	A = distance.dot(distance);
	B = near.dot(distance);
	B = B*2.0;
	C = near.dot(near);

	//Get the hitbox by ID
	int ID_tmp;
	for(int i = 0; i < hitBoxNodes.size(); i++)
	{
		ID_tmp = hitBoxNodes.at(i)->hit.Intersect(near,distance);
		if(ID_tmp != -1)
		{
			for(int j = 0; j < hitBoxNodes.size(); j++)
			{
				hitBoxNodes.at(j)->current = false;
			}
			hitBoxNodes.at(i)->current = true;
			currentNode = hitBoxNodes.at(i);
			hitBoxNodes.at(i)->hit.draw();
		}
	}
	return false;

}

//Clear the entire scene revusively
void SceneGraph::clearScene(Node *n)
{
	for (int i = 0; i < n->children->size(); i++){
		clearScene(n->children->at(i));
	}
	//Delete children for the current only once at the bottom of the tree and then working our way up
	n->children->clear();
	return;
}

//Go to root and call the clear scene function
void SceneGraph::deleteScene(){
	goToRoot();
	clearScene(currentNode);
}