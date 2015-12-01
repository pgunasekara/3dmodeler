#include <cmath>
#include <sstream>
#include <fstream>
#include "math3D.h"
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

/* VECTORS */

// general case
vec3D::vec3D(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

// specify components
vec3D::vec3D(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3D::vec3D(vertex3D p1, vertex3D p2){
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

vec3D::~vec3D(){

}

vec3D vec3D::vectorMultiplyr(float s){
	return vec3D(x*s,y*s,z*s);
}

vec3D vec3D::normalize() {
	float magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));

	return vec3D(x/magnitude,y/magnitude,z/magnitude);
};

vec3D vec3D::cross(vec3D other) {
	// cross product of vectors
	float cx = y*other.z - z*other.y;
	float cy = z*other.x - x*other.z;
	float cz = x*other.y - y*other.x;

	return vec3D(cx,cy,cz);
};

double vec3D::dot(vec3D other) {
	// dot product of vectors
	return x*other.x + y*other.y + z*other.z;
};

void vec3D::flipVector(){
	x *= -1;
	y *- -1;
	z *= -1;
}

void vec3D::reset(){
	x=0;
	y=0;
	z=0;
}

float* vec3D::returnArray(){
	float *vert = new float[3];

	vert[0] = static_cast<float>(x);
	vert[1] = static_cast<float>(y);
	vert[2] = static_cast<float>(z);

	return vert;
}

double* vec3D::returnDoubleArray(){
	double *vert = new double[3];

	vert[0] = static_cast<double>(x);
	vert[1] = static_cast<double>(y);
	vert[2] = static_cast<double>(z);

	return vert;
}

void vec3D::applyMatrix(float* matrix){
	x = matrix[0]*x + matrix[1]*y + matrix[2]*z + matrix[3];
	y = matrix[4]*x + matrix[5]*y + matrix[6]*z + matrix[7];
	z = matrix[8]*x + matrix[9]*y + matrix[10]*z + matrix[11];
}

bool vec3D::IntersectSphere(){
	double sq = y*y  - 4*x*z;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * y + sqrt(sq))/(2*x);
		t1 = ((-1) * y - sqrt(sq))/(2*x);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
		return true;
	}
	return false;
}

bool vec3D::IntersectCube(){

	return true;
}

void vec3D::update(double v[]){
	x = v[0];
	y = v[1];
	z = v[2];
}

/* POINTS */

vertex3D::vertex3D(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

vertex3D::vertex3D(float x, float y,float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

vertex3D::~vertex3D(){

}

// if difficulties switch to pointer
float vertex3D::distanceFrom(vertex3D p){
	return sqrt(pow(p.x - x,2) + pow(p.y - y,2) + pow(p.z - z,2));
}

// used for comparisons
float vertex3D::fastDistanceFrom(vertex3D p){
	return pow(p.x - x,2) + pow(p.y - y,2) + pow(p.z - z,2);
}

// moves point along vector
void vertex3D::movePoint(vec3D v){
	x += v.x;
	y += v.y;
	z += v.z;
}

// returns pointer to array with components of vertex
float* vertex3D::returnArray(){
	float *vert = new float[3];

	vert[0] = static_cast<float>(x);
	vert[1] = static_cast<float>(y);
	vert[2] = static_cast<float>(z);
	return vert;
}

double* vertex3D::returnDoubleArray(){
	double *vert = new double[3];

	vert[0] = static_cast<double>(x);
	vert[1] = static_cast<double>(y);
	vert[2] = static_cast<double>(z);

	return vert;
}



/* QUATERNIONS */
// general case
quaternion::quaternion(){
	w = 1.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;

	updateRotationMatrix();
}

// specify components
quaternion::quaternion(float w,float x, float y, float z){
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
	updateRotationMatrix();
}

quaternion::~quaternion(){

}

// updates rotation matrix that quaternion associates with
void quaternion::updateRotationMatrix(){
	rotationMatrix = new float[16];

	rotationMatrix[0] = pow(w,2)+pow(x,2)-pow(y,2)-pow(z,2);
	rotationMatrix[1] = 2*x*y - 2*w*z;
	rotationMatrix[2] = 2*x*z + 2*w*y;
	rotationMatrix[3] = 0.0;
	rotationMatrix[4] = 2*x*y + 2*w*z;
	rotationMatrix[5] = pow(w,2)-pow(x,2)+pow(y,2)-pow(z,2);
	rotationMatrix[6] = 2*y*z + 2*w*x;
	rotationMatrix[7] = 0.0;
	rotationMatrix[8] = 2*x*z - 2*w*y;
	rotationMatrix[9] = 2*y*z - 2*w*x;
	rotationMatrix[10] = pow(w,2)-pow(x,2)-pow(y,2)+pow(z,2);
	rotationMatrix[11] = 0.0;
	rotationMatrix[12] = 0.0;
	rotationMatrix[13] = 0.0;
	rotationMatrix[14] = 0.0;
	rotationMatrix[15] = 1.0;
}

// normalizes quaternion
quaternion quaternion::normalize() {
	float magnitude = sqrt(pow(w,2) + pow(x,2) + pow(y,2) + pow(z,2));

	return quaternion(w/magnitude,x/magnitude,y/magnitude,z/magnitude);
};


// cross two quaternions
quaternion quaternion::cross(quaternion other) {

	float cw = w*other.w - x*other.x - y*other.y - z*other.z;
	float cx = w*other.x + x*other.w + y*other.z - z*other.y;
	float cy = w*other.y + x*other.z - y*other.w + z*other.x;
	float cz = w*other.z + x*other.y + y*other.x - z*other.w;

	return quaternion(cw,cx,cy,cz);
};

/* MESHES */

Mesh3D::Mesh3D(){
	verts = vector<vertex3D>(0);
	faces = vector<face3D>(0);
}

// draws a mesh
void Mesh3D::drawMesh(){
	for (int i = 0; i < faces.size();i++){
		glBegin(GL_QUADS);
		glVertex3fv(verts[faces[i].a].returnArray());
		glVertex3fv(verts[faces[i].b].returnArray());
		glVertex3fv(verts[faces[i].c].returnArray());
		glEnd();
		}
	}

// draws Terrain
void Mesh3D::drawTerrain(vector<vector<float> > heightMap,float maxHeight,bool drawFlat){
	// draw if flat shading
	//glEnable(GL_COLOR_MATERIAL);
	if (drawFlat){
		for (int i = 0; i < faces.size();i++){
			glBegin(GL_TRIANGLES);
			glNormal3fv(faces[i].averageN.returnArray());
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3fv(verts[faces[i].a].returnArray());
			glNormal3fv(faces[i].averageN.returnArray());
			glColor3f(heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight,heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight,heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight);
			glVertex3fv(verts[faces[i].b].returnArray());
			glNormal3fv(faces[i].averageN.returnArray());
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3fv(verts[faces[i].c].returnArray());
			glEnd();
		}
	}else{
	// draw if guorad shading
		for (int i = 0; i < faces.size();i++){
			glBegin(GL_TRIANGLES);
			glNormal3fv(verts[faces[i].a].totalN.returnArray());
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3fv(verts[faces[i].a].returnArray());
			glNormal3fv(verts[faces[i].b].totalN.returnArray());
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3fv(verts[faces[i].b].returnArray());
			glNormal3fv(verts[faces[i].c].totalN.returnArray());
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3fv(verts[faces[i].c].returnArray());
			glEnd();
		}
	}
}

// draw 2D Terrain for terrain editor
void Mesh3D::draw2DTerrain(vector<vector<float> > heightMap,float maxHeight){
	for (int i = 0; i < faces.size();i++){
			glBegin(GL_TRIANGLES);
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3f(verts[faces[i].a].x,verts[faces[i].a].z,0);
			glColor3f(heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight,heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight,heightMap[verts[faces[i].b].x][verts[faces[i].b].z]/maxHeight);
			glVertex3f(verts[faces[i].b].x,verts[faces[i].b].z,0);
			glColor3f(heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight,heightMap[verts[faces[i].a].x][verts[faces[i].a].z]/maxHeight);
			glVertex3f(verts[faces[i].c].x,verts[faces[i].c].z,0);
			glEnd();
	}
}

// calculate face normals
void Mesh3D::calculateFaceNormals(){
	vec3D v1,v2,aN;

	for (int i = 0; i <faces.size(); i++){
		v1 = vec3D(verts[faces[i].a],verts[faces[i].b]);
		v2 = vec3D(verts[faces[i].a],verts[faces[i].c]);
		aN = v1.cross(v2).normalize();		
		faces[i].averageN = aN;
	}
}

// calculate vertex normals
void Mesh3D::calculateVertexNormals(float tSize){
	vec3D tN = vec3D();
	vector<vec3D> normals;

	for (int i = 0; i <verts.size(); i++){
		normals = calculateVertexNormal(verts[i],tSize - 1);
		for (int j = 0; j < normals.size(); j++){
			tN = tN + normals[j];
		}
		tN = tN.normalize();
		verts[i].totalN = tN;
		tN.reset();
	}
}

// calculate single vertex normal
vector<vec3D> Mesh3D::calculateVertexNormal(vertex3D v, float tSize){
	vector<vec3D> normals = vector<vec3D>();
	if (v.x - 1 >= 0 && v.z - 1 >= 0){
		normals.push_back(faces[2*tSize*(v.x - 1) + 2*(v.z-1) + 1].averageN);
	}
	if (v.x - 1 >= 0 && v.z >= 0){
		normals.push_back(faces[2*tSize*(v.x - 1) + 2*(v.z)].averageN);
	}
	if (v.x - 1 >= 0 && v.z >= 0){
		normals.push_back(faces[2*tSize*(v.x - 1) + 2*(v.z) + 1].averageN);
	}
	if (v.x >= 0 && v.z-1 >= 0){
		normals.push_back(faces[2*tSize*(v.x) + 2*(v.z-1)].averageN);
	}
	if (v.x >= 0 && v.z-1 >= 0){
		normals.push_back(faces[2*tSize*(v.x) + 2*(v.z-1) + 1].averageN);
	}
	if (v.x >= 0 && v.z >= 0){
		normals.push_back(faces[2*tSize*(v.x) + 2*(v.z)].averageN);
	}
	return normals;
}

void Mesh3D::loadObj(char* filename){
	// load your obj file
	
	// your current line and your file reading stream
	string line;
	ifstream myfile (filename);
	
	// fc holds first character f or v (face or vertex) along with indexs/ vals for f or v
	char fc;
	float x,y,z;

	if (myfile.is_open()){
	    // for each line in .obj file, get line, put in line variable
	    while (getline(myfile,line)){
	    	// take current line, splits at all spaces
	    	istringstream iss (line);
	    	iss >> fc;

	    	if (fc == 'f'){
	    		faces.resize(faces.size() + 1);
	    		iss >> faces[faces.size() - 1].a;
	    		iss >> faces[faces.size() - 1].b;
	    		iss >> faces[faces.size() - 1].c;
	    	}else if (fc == 'v'){
	    		iss >> x;
	    		iss >> y;
	    		iss >> z;
	    		verts.push_back(vertex3D(x,y,z));
			}
	    }

	    myfile.close();
	}
}

/* STATIC FUNCTIONS */

quaternion angleAxis(float angle, vec3D axis){
	// axis has to be unit vector
	quaternion newQuat = quaternion();
	
	newQuat.w  = cosf(angle/2);
	newQuat.x = axis.x * sinf(angle/2);
	newQuat.y = axis.y * sinf(angle/2);
	newQuat.z = axis.z * sinf(angle/2);

	return newQuat;
}

vec3D operator+ (vec3D v1, vec3D v2)
{
    return vec3D(v1.x + v2.x, v1.y + v2.y,v1.z + v2.z);
}

vec3D operator- (vec3D v1, vec3D v2)
{
    return vec3D(v1.x - v2.x, v1.y - v2.y,v1.z - v2.z);
}