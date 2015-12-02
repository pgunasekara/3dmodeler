#ifndef HITBOX_H
#define HITBOX_H
#include <vector>
#include "math3D.h"
using namespace std;


class Plane {
public:
	Plane();
	Plane(vertex3D a, vertex3D b, vertex3D c, vertex3D d,bool xPlane, bool yPlane, bool zPlane);
	void draw();
	bool Intersect(vec3D v0,vec3D vD, float* tNear, float* tFar,vertex3D minP, vertex3D maxP);
	void scale(vec3D transform);
	void Translate(vec3D transform);
	void Rotate(quaternion quat);

	vertex3D a,b,c,d;
	vec3D norm;
	bool xPlane,yPlane,zPlane;
};

class Hitbox{
public:
	Hitbox();
	Hitbox(vertex3D low, vertex3D high);
	void draw();
	bool Intersect(vec3D v0,vec3D vD);
	bool IntersectSphere(vec3D Ray);
	
	void scale(vec3D transform);
	void Translate(vec3D transform);
	void Rotate(quaternion quat);

	vertex3D minP,maxP;
	vector<Plane*> Planes;
};



#endif