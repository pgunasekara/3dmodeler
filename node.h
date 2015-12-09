#ifndef __NODE_H__	//guard against cyclic dependancy
#define __NODE_H__

#include <vector>
#include "structs.h"
#include "Math/Hitbox.h"
#include "Math/math3D.h"
#include "materials.h"

using namespace std;

extern int getID();

//Main Node class

//Various node types
enum NodeType{
	root,
	group,
	transformation,
	model
};

//Various transformation types possible for a nodes
enum transformType{
	Translate,
	Rotate,
	Scale
};

//various model types
enum ModelType{
	Sphere,
	Cube,
	Cone,
	Cylinder,
	Torus,
	Teapot,
	Tetrahedron,
	Octahedron,
	Dodecahedron,
	Icosahedron,
	Custom
};


class Node{
public:
	Node();

	NodeType nodeType;
	bool isDrawable;
	int ID;
	vector<Node*> *children;
	Node* parent;
	int currentChild;
	bool current;
	Hitbox hit;
	ModelType modelType;
	Vector3D amount3;
	Vector4D amount4;

	transformType transformationType;

	transformType type;

	vec3D tr;
	vec3D sc;
	quaternion rot;
	vec3D xaxis,yaxis,zaxis;
	vertex3D min,max;
	bool method2;

	cMaterial currentMat;

	void draw();
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
	//virtual void applyChangesAxes(vec3D transform);
};

#endif