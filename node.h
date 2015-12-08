#ifndef __NODE_H__	//guard against cyclic dependancy
#define __NODE_H__

//Node Class.
//should act as a template class for other sub-types of
//Nodes

#include <vector>
#include "structs.h"
#include "Math/Hitbox.h"
#include "Math/math3D.h"
using namespace std;

extern int getID();

typedef struct customMaterial
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shine;

}customMaterial;


customMaterial emerald = {
	{0.0215, 0.1745, 0.0215, 1.0},
	{0.07568, 0.61424, 0.07568, 1.0},
	{0.633, 0.727811, 0.633, 1.0},
	{0.0,0.0,0.0,0.0},
	0.6
}

customMaterial blackRubber = {
	{0.0,0.0,0.0},
	{0.01,0.01,0.01},
	{0.50,0.50,0.50},
	{0.0,0.0,0.0,0.0},
	0.6
}

customMaterial jade = {
	{0.135,0.2225,0.1575,1.0},
	{0.54,0.89,0.63,1.0},
	{0.316228,0.316228,0.316228},
	{0.0,0.0,0.0,0.0},
	0.1
}

customMaterial ruby = {
	{0.1745,0.01175,0.01175,1.0},
	{0.61424,0.04136,0.04136,1.0},
	{0.727811,0.626959,0.626959,1.0},
	{0.0,0.0,0.0,0.0},
	0.6
}

customMaterial copper = {
	{0.19125,0.0735,0.0225,1.0},
	{0.7038,0.27048,0.0828,1.0},
	{0.256777,0.137622,0.086014,1.0},
	{0.0,0.0,0.0,0.0},
	0.1
}

//if you add more derived classes
//add the types here
enum NodeType{
	root,
	group,
	transformation,
	model
};

enum transformType{
	Translate,
	Rotate,
	Scale
};

class Node{
public:
	Node();	//constructor

	NodeType nodeType;
	bool isDrawable;
	int ID;
	vector<Node*> *children;
	Node* parent;
	int currentChild;
	bool current;
	Hitbox hit;

	transformType type;

	vec3D tr;
	vec3D sc;
	quaternion rot;
	vec3D xaxis,yaxis,zaxis;

	Vector3D amount3;
	Vector4D amount4;

	customMaterial currentMat;

	void draw();
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
	//virtual void applyChangesAxes(vec3D transform);
};

#endif