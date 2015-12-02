#include "math3D.h"
#include "Hitbox.h"
#include <cmath>
#include <stdio.h>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


Plane::Plane(){
	a = vertex3D(-0.5,-0.5,0.5);
	b = vertex3D(0.5,-0.5,0.5);
	c = vertex3D(0.5,0.5,0.5);
	d = vertex3D(-0.5,0.5,0.5);
	xPlane = true;
	yPlane = false;
	zPlane = false;
}

Plane::Plane(vertex3D a, vertex3D b, vertex3D c, vertex3D d,bool xPlane, bool yPlane, bool zPlane){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	vec3D v1 = vec3D(a,d);
	vec3D v2 = vec3D(a,b);
	this->xPlane = xPlane;
	this->yPlane = yPlane;
	this->zPlane = zPlane;
	norm = v1.cross(v2);
}


void Plane::draw(){
	glBegin(GL_LINE_LOOP);
			glColor3f(1.0f,0.0f,0.0f);
		    glVertex3dv(a.returnDoubleArray());
		    glVertex3dv(b.returnDoubleArray());
		    glVertex3dv(c.returnDoubleArray());
		    glVertex3dv(d.returnDoubleArray());
	glEnd();
}
//FIX THIS FJSDOAIJFDSIOAJFISDO
bool Plane::Intersect(vec3D v0,vec3D vD, float* tNear, float* tFar, vertex3D minP, vertex3D maxP){
	float t1,t2;
	if (yPlane && zPlane){
		if (vD.isOrthogonal(norm)) { //ray is parallel to the planes 
			if (v0.x < minP.x || v0.x > maxP.x) {    
				return false; // outside slab
			}
		}else{
			t1 = (minP.x-v0.x)/vD.x;
			t2 = (maxP.x-v0.x)/vD.x;
		}
		if (t1 > t2) {
			float temp = t1;
			t1 = t2;
			t2 = temp;

		}
		if (t1 > *tNear){
			*tNear = t1; // want largest tNear
		}
		if (t2 < *tFar){
			*tFar = t2; // want smallest tFar
		}
		if (*tNear > *tFar){
			return false; //box is missed
		}
		if (*tFar < 0){
			return false; //Slab behind origion of ray
		}
	}else if (xPlane && yPlane){
		if (vD.isOrthogonal(norm)) { //ray is parallel to the planeS
			if (v0.z < minP.z || v0.z > maxP.z) {    
				return false; // outside slab
			}
		}else{
			t1 = (minP.z-v0.z)/vD.z;
			t2 = (maxP.z-v0.z)/vD.z;
		}
		if (t1 > t2) {
			float temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > *tNear){
			*tNear = t1; // want largest tNear
		}
		if (t2 < *tFar){
			*tFar = t2; // want smallest tFar
		}
		if (*tNear > *tFar){
			return false; //box is missed
		}
		if (*tFar < 0){
			return false; //Slab behind origion of ray
		}
	}else if (xPlane && zPlane){
		if (vD.isOrthogonal(norm)) { //ray is parallel to the planes 
			if (v0.y < minP.y || v0.y > maxP.y) {    
				return false; // outside slab
			}
		}else{
			t1 = (minP.y-v0.y)/vD.y;
			t2 = (maxP.y-v0.y)/vD.y;
		}
		if (t1 > t2) {
			float temp = t1;
			t1 = t2;
			t2 = temp;

		}
		if (t1 > *tNear){
			*tNear = t1; // want largest tNear
		}
		if (t2 < *tFar){
			*tFar = t2; // want smallest tFar
		}
		if (*tNear > *tFar){
			return false; //box is missed
		}
		if (*tFar < 0){
			return false; //Slab behind origion of ray
		}
	}
	return true;
}


void Plane::scale(vec3D transform){
	

}
void Plane::Translate(vec3D transform){
	a.movePoint(transform);
	b.movePoint(transform);
	c.movePoint(transform);
	d.movePoint(transform);
	norm = norm + transform;
	
}

void Plane::Rotate(quaternion quat){

}


Hitbox::Hitbox(){
	vertex3D v1 = vertex3D(-0.5,-0.5,0.5);
	vertex3D v2 = vertex3D(0.5,-0.5,0.5);
	vertex3D v3 = vertex3D(0.5,0.5,0.5);
	vertex3D v4 = vertex3D(-0.5,0.5,0.5);
	vertex3D v5 = vertex3D(-0.5,-0.5,-0.5);
	vertex3D v6 = vertex3D(0.5,-0.5,-0.5);
	vertex3D v7 = vertex3D(0.5,0.5,-0.5);
	vertex3D v8 = vertex3D(-0.5,0.5,-0.5);

	Planes.push_back(new Plane(v1,v2,v3,v4,true,true,false)); // front face
	Planes.push_back(new Plane(v5,v6,v7,v8,true,true,false)); // back face
	Planes.push_back(new Plane(v4,v3,v7,v8,true,false,true)); // top face
	Planes.push_back(new Plane(v1,v2,v6,v5,true,false,true)); // bottom face
	Planes.push_back(new Plane(v2,v6,v7,v3,false,true,true)); // right face
	Planes.push_back(new Plane(v1,v5,v8,v4,false,true,true)); // left face
	minP = vertex3D(-0.5,-0.5,-0.5);
	maxP = vertex3D(0.5,0.5,0.5);

}

Hitbox::Hitbox(vertex3D low, vertex3D high){
	vertex3D v1 = vertex3D(low.x,low.y,high.z);
	vertex3D v2 = vertex3D(high.x,low.y,high.z);
	vertex3D v3 = vertex3D(high.x,high.y,high.z);
	vertex3D v4 = vertex3D(low.x,high.y,high.z);
	vertex3D v5 = vertex3D(low.x,low.y,low.z);
	vertex3D v6 = vertex3D(high.x,low.y,low.z);
	vertex3D v7 = vertex3D(high.x,high.y,low.z);
	vertex3D v8 = vertex3D(low.x,high.y,low.z);

	Planes.push_back(new Plane(v1,v2,v3,v4,true,true,false)); // front face
	Planes.push_back(new Plane(v5,v6,v7,v8,true,true,false)); // back face
	Planes.push_back(new Plane(v4,v3,v7,v8,true,false,true)); // top face
	Planes.push_back(new Plane(v1,v2,v6,v5,true,false,true)); // bottom face
	Planes.push_back(new Plane(v2,v6,v7,v3,false,true,true)); // right face
	Planes.push_back(new Plane(v1,v5,v8,v4,false,true,true)); // left face
	minP = vertex3D(low.x,low.y,low.z);
	maxP = vertex3D(high.x,high.y,high.z);

}

void Hitbox::draw(){
	for (int i = 0; i <Planes.size(); i++){
		Planes[i]->draw();
	}
}

bool Hitbox::Intersect(vec3D v0,vec3D vD){
	float *tNear;
	float *tFar;
	float nearVal,farVal;
	nearVal = -1000.0f;
	farVal = 1000.0f;
	tFar = &farVal;
	tNear = &nearVal;
	for (int i =0 ; i <Planes.size(); i++){
		if (!Planes[i]->Intersect(v0,vD,tNear,tFar,minP,maxP)){
			return false;
		}
	}
	return true;
}

bool Hitbox::IntersectSphere(vec3D Ray){
	double sq = Ray.y*Ray.y  - 4*Ray.x*Ray.z;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * Ray.y + sqrt(sq))/(2*Ray.x);
		t1 = ((-1) * Ray.y - sqrt(sq))/(2*Ray.x);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
		return true;
	}
	return false;
}

void Hitbox::scale(vec3D transform){
	for (int i = 0; i < Planes.size(); i++){
		Planes[i]->scale(transform);
	}
}

void Hitbox::Translate(vec3D transform){
	for (int i = 0; i < Planes.size(); i++){
		Planes[i]->Translate(transform);
	}
	minP.movePoint(transform);
	maxP.movePoint(transform);
}

void Hitbox::Rotate(quaternion quat){
	for (int i = 0; i < Planes.size(); i++){
		Planes[i]->Rotate(quat);
	}
}


