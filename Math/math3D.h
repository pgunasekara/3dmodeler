#ifndef MATH3D_H
#define MATH3D_H
#include <vector>
using namespace std;

class vertex3D; // declare vertex3D class for use later
class quaternion; // declare quaternion class for use later

class vec3D{ // vector3d class
public:
	// constructors
	vec3D();
	vec3D(float x, float y,float z); // make a vector from 3 componenets
	vec3D(vertex3D p1, vertex3D p2); // make a vector from 2 points
	// destructor
	~vec3D();

	//methods
	// multiply by scalar and return new vector
	vec3D vectorMultiplyr(float s);
	// returns normal
	vec3D normalize();
	// cross product with other vector
	vec3D cross(vec3D other);
	// dot product with other vector
	float dot(vec3D other);
	// flips direction of vector
	void flipVector();
	// reset vector to 0,0,0
	void reset();
	// returns the vector components as a pointer to a float array of size 3
	float* returnArray();
	// retusn vector components as pointer to double array
	double* returnDoubleArray();
	// multiply the vector by a transformation matrix
	void applyMatrix(float* matrix);
	// updates vector through passed in array
	void update(double v[]);
	// check if orthogonal to other vector
	bool isOrthogonal(vec3D v);

	//member variables
	float x,y,z;
};

// class for verticies
class vertex3D{
public:
	// constructors
	vertex3D();
	vertex3D(float x, float y,float z);
	
	// destructor
	~vertex3D();

	// methods
	// finds distance from other point
	float distanceFrom(vertex3D p);
	// just finds distance without sqrt (used for comparisons only)
	float fastDistanceFrom(vertex3D p);
	// moves point along vector
	void movePoint(vec3D v);
	// scale point by vector
	void scalePoint(vec3D v);
	// rotate point by quaternion
	void rotatePoint(float* matrix);
	// returns the vertex components as a pointer to a float array of size 3
	float* returnArray();
	// return vertex components as pointer to double array
	double* returnDoubleArray();

	//member variables
	float x,y,z;
	// vertex Normal
	vec3D totalN;
};

// quaternion = w + xi + yj + zk. where i,j and k are imaginary numbers
class quaternion{
public:
	// constructors
	quaternion();
	quaternion(float w, float x, float y, float z);
	// destructor
	~quaternion();

	// update the rotation matrix that is made by the quaternion (used if you normalize) or change quaternion
	void updateRotationMatrix();
	// cross the quaternion with another, return a new quaternion
	quaternion cross(quaternion other);
	// normalize quaternion, return a new one
	quaternion normalize();

	// w is angle you are rotating, x,y,z are components defining axis
	// rotationMatrix holds on to the rotation matrix that corresponds to the quaternion
	float w,x,y,z;
	float* rotationMatrix;
};

struct face3D{
	// which verticies to use for face
	int a,b,c;
	// face normal
	vec3D averageN;
};

class Mesh3D{
public:
	Mesh3D();
	void drawMesh(); // draws Mesh (not used in A2) 
	void drawTerrain(vector<vector<float> > heightMap, float maxHeight,bool drawFlat); // draws terrain using a heightmap, maxheight for color scheme and a boolean for type of shading
	void draw2DTerrain(vector<vector<float> > heightMap,float maxHeight); // draws 2d terrain using height map and maxheight for color scheme

	// loads Obj file (not used in A3)
	void loadObj(char* filename);
	
	// calculate normals
	void calculateFaceNormals();
	void calculateVertexNormals(float tSize);
	// calculates one vertex normal when given vertex and size of terrain
	vector<vec3D> calculateVertexNormal(vertex3D v,float tSize);

	// holds all your verticies and faces
	vector<vertex3D> verts;
	vector<face3D> faces;
};

// creates a quaternion after being given an angle and an axis
quaternion angleAxis(float angle, vec3D vec);

// overloads + and - operators to work for vectors (these return vectors unlike the .add and subtract methods)
vec3D operator+ (vec3D v1, vec3D v2);
vec3D operator- (vec3D v1, vec3D v2);
vec3D operator* (vec3D v1, vec3D v2);

bool Intersect(int x, int y);


#endif