#ifndef HITBOX_H
#define HITBOX_H
#include <vector>
#include "math3D.h"
using namespace std;


class Plane {
public:
	// constructors
	Plane();
	Plane(vertex3D a, vertex3D b, vertex3D c, vertex3D d,bool xPlane, bool yPlane, bool zPlane);
	// methods
	void draw();
	bool Intersect(vec3D v0,vec3D vD, float* tNear, float* tFar,vertex3D minP, vertex3D maxP);
	void Scale(vec3D transform);
	void Translate(vec3D transform);
	void Rotate(quaternion transform);
	// variables
	vertex3D a,b,c,d,dA,dB,dC,dD;
	vec3D norm;
	bool xPlane,yPlane,zPlane;
};

class Hitbox{
public:
	// constructors
	Hitbox();
	Hitbox(vertex3D low, vertex3D high, int ID);
	// methods
	void draw();
	int Intersect(vec3D v0,vec3D vD);
	void applyAxesChanges(vec3D transform);
	
	void Scale(vec3D transform);
	void Translate(vec3D transform);
	void Rotate(quaternion transform);
	void updateHitbox(vertex3D minP, vertex3D maxP);
	// variables
	vertex3D minP,maxP;
	vec3D xaxis,yaxis,zaxis;
	vector<Plane*> Planes;
	int ID;
};

#endif