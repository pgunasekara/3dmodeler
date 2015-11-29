#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include "node.h"
#include "Math/math3D.h"

class SceneGraph{
public:
	SceneGraph();	//constructor

	//Scene Graph Navigation
	void goToRoot();
	void goToChild(int i);
	void goToParent();
	void insertChildNodeHere(Node *node);
	void deleteThisNode();
	bool Intersect(int x, int y);

	//Scene Graph Draw
	void draw();

	// Variables for Intersect
	vec3D near,far,distance;
	double matModelView[16], matProjection[16]; 
	int viewport[4]; 
	double* start;
	double* finish;

private:
	Node *currentNode;
	Node *rootNode;
};

#endif