/*
COMP SCI 3GC3 - Assignment 3
December 11 , 2015
Completed in a group, submitted on gunasepi's SVN trunk
Group:
	Name: Pasindu Gunasekara
		MacID: gunasepi
		StudentNumber: 001412155

	Name: Roberto Temelkovski
		MacID: temelkr
		Student Number: 001418731

Description: Simple 3D modeling software created in OpenGL and C++
*/

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//Built in library includes for various functions such as I/O, vectors, stringstreams, and Math
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Math/camera.h"
#include "Math/Hitbox.h"
#include "structs.h"
#include "Math/math3D.h"
#include "materials.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"

using namespace std;

//Variables used for camera
float mouseX,mouseY,globalW,globalH;
bool PlaneExist = false;
Hitbox *hit;
Camera camera;

//File names that are saved or loaded
string fileNameLoad;
string fileNameSave;

//Master ID for nodes
int masterID = 0;

//Various vectors used for transformation nodes
Vector3D ip;
Vector3D translation;
Vector4D rotation; 
Vector3D scale;

//this function is used to assign an ID to a node
int getID()
{
	return masterID++;
}

// for the unprojection
double* start = new double[3];
double* finish = new double[3];

//The main Scene Graph
SceneGraph *SG;




/*LIGHTING*/
//Positions of the two lights
float light_pos[] = {10.0f, 5.0f, 10.0f, 1.0f};//This is the position for the first light

float light_pos_2[] = {-10.0f, 5.0f, -10.0f, 1.0f};//This is the position for the second light

//Settings for the first light
float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {1, 1, 1, 1};
float spec0[4] = {1, 1, 1, 1};

//Material for the ground plane (CHROME)
float m_amb[] = {0.25, 0.25, 0.25, 1.0};
float m_diff[] = {0.4, 0.4, 0.4, 1.0};
float m_spec[] = {0.774597, 0.774597, 0.774597, 1.0};
float shiny = 0.6;

//Settings for the second Light
float m_amb_2[] = {0.1, 0.18725, 0.1745, 1.0};
float m_diff_2[] = {0.396, 0.74151, 0.69102, 1.0};
float m_spec_2[] = {0.297254, 0.30829, 0.306678, 1.0};
float shiny_2 = 0.1;

//Booleans used to check whether the lights are currently on or off
bool light_0_toggle = true;
bool light_1_toggle = true;

//Position of the ground plane
GLfloat positionA[3][3] = {{-25.0f, -0.5f, -25.0f}, {25.0f, -0.5f, -25.0f}, {25.0f, -0.5f, 25.0f}};
GLfloat positionB[3][3] = {{25.0f, -0.5f, 25.0f},{-25.0f, -0.5f, 25.0f},{-25.0f, -0.5f, -25.0f}};

//Direction vectors for the 2 ground plane triangles
float vecA[3], vecB[3], vecC[3], vecD[3]; 
GLfloat normA[3], normB[3];
bool calculated = false;

//Global output stream variable for creating files
ofstream myfile;


//Function used to create planes
void createPlane()
{
	//Plane coordinates, down by 0.5 units
	//The plane will be 50x50
	//Triangle 1
	//-25, -0.5, -25
	//25, -0.5, -25
	//25, -0.5, 25

	//Triangle 2
	//25, -0.5, 25
	//-25, -0.5, 25
	//-25, -0.5, -25

	//Calculate A and B for A dot B to get the normal of the plane
	//Only need to calculate this once, therefore a boolean is used to control this
	if(calculated == false)
	{
		calculated = true;
		//Triangle 1
		//A is vertex 1 and vertex 2
		//B is vertex 1 and vertex 3
		vecA[0] = positionA[1][0] - positionA[0][0];
		vecA[1] = positionA[1][1] - positionA[0][1];
		vecA[2] = positionA[1][2] - positionA[0][2];

		vecB[0] = positionA[2][0] - positionA[0][0];
		vecB[1] = positionA[2][1] - positionA[0][1];
		vecB[2] = positionA[2][2] - positionA[0][2];

		//Triangle 2
		//C is vertex 1 and vertex 2
		//D is vertex 1 and vertex 3
		vecC[0] = positionB[1][0] - positionB[0][0];
		vecC[1] = positionB[1][1] - positionB[0][1];
		vecC[2] = positionB[1][2] - positionB[0][2];

		vecD[0] = positionB[2][0] - positionB[0][0];
		vecD[1] = positionB[2][1] - positionB[0][1];
		vecD[2] = positionB[2][2] - positionB[0][2];

		//Calcuate Cross product between vecA and vecB to get the normal of the FIRST Triangle
		normA[0] = vecA[1]*vecB[2] - vecA[2]*vecB[1];
		normA[1] = vecA[2]*vecB[0] - vecA[0]*vecB[2];
		normA[2] = vecA[0]*vecB[1] - vecA[1]*vecB[0];

		//Calcuate Cross product between vecA and vecB to get the 
		//normal of the second Triangle
		normB[0] = vecC[1]*vecD[2] - vecC[2]*vecD[1];
		normB[1] = vecC[2]*vecD[0] - vecC[0]*vecD[2];
		normB[2] = vecC[0]*vecD[1] - vecC[1]*vecD[0];
	}

	//Apply a material to this plane
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glNormal3fv(normA);
		glVertex3fv(positionA[2]);
		glVertex3fv(positionA[1]);
		glVertex3fv(positionA[0]);
		glColor3f(1, 0, 0);
		glNormal3fv(normB);
		glVertex3fv(positionB[2]);
		glVertex3fv(positionB[1]);
		glVertex3fv(positionB[0]);
	glEnd();

	glPopMatrix();
}

// put in a model type, get it as a string
//Used for File I/O
string getModelType(ModelType modelType){
	switch (modelType){
		case Sphere:
			return "Sphere";
			break;
		case Cube:
			return "Cube";
			break;
		case Cone:
			return "Cone";
			break;
		case Torus:
			return "Torus";
			break;
		case Tetrahedron:
			return "Tetrahedron";
			break;
		}
}

// put in a transformation type, get it as a string
string getTransformType(transformType transformationType){
	switch (transformationType){
		case Translate:
			return "Translate";
			break;
		case Rotate:
			return "Rotate";
			break;
		case Scale:
			return "Scale";
			break;
		}
	}
// recursively find all the transformations that apply
// to each model after loading them in, and applies them
// to the hitbox as well
void hitboxHelper(Node *n,Node *hitBoxNode){
	if (n->ID > 1){
		for (int i = 0; i < n->children->size();i++){
			hitboxHelper(n->parent,hitBoxNode);
		}
	}
	if (n->nodeType == transformation){
		if (n->transformationType == Translate){
			hitBoxNode->hit.Translate(vec3D(n->amount3.x,n->amount3.y,n->amount3.z));
		}else if (n->transformationType == Scale){
			hitBoxNode->hit.Scale(vec3D(n->amount3.x,n->amount3.y,n->amount3.z));
		}
	}
	return;
}
// apply hitbox transforms on all the hitboxes when they are loade
void applyHitboxes(){
	for (int i = 0; i < SG->hitBoxNodes.size();i++){
		hitboxHelper(SG->hitBoxNodes[i]->parent,SG->hitBoxNodes[i]);
	}
}

// pass in a type, material and min/ max points of hitbox, creates the model
void createModel(string type, string material, vertex3D min, vertex3D max){
	if (type == "Cube"){
		SG->insertChildNodeHere(new NodeModel(Cube,min,max));
		SG->currentNode->currentMat.fromString(material);
	}
	else if (type == "Sphere"){
		SG->insertChildNodeHere(new NodeModel(Sphere,min,max));
		SG->currentNode->currentMat.fromString(material);
	}else if (type == "Cone"){
		SG->insertChildNodeHere(new NodeModel(Cone,min,max));
		SG->currentNode->currentMat.fromString(material);
	}
	else if (type == "Torus"){
		SG->insertChildNodeHere(new NodeModel(Torus,min,max));
		SG->currentNode->currentMat.fromString(material);
	}
	else if (type == "Tetrahedron"){
		SG->insertChildNodeHere(new NodeModel(Tetrahedron,min,max));
		SG->currentNode->currentMat.fromString(material);
	}
	cout << type << endl;
	SG->goToRoot();
	SG->currentNode = SG->currentNode->children->at(0);
}
// insert translation node when loading
void insertTranslation(float x, float y, float z){
	translation.x = x;
	translation.y = y;
	translation.z = z;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Translate,translation));
}

// insert Rotation node when loading
void insertRotation(float w,float x, float y, float z){
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	rotation.w = w;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Rotate,rotation));
}
// insert Scale node when loading
void insertScale(float x, float y, float z){
	translation.x = x;
	translation.y = y;
	translation.z = z;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Scale,translation));
}
// saves every model you have and all their attributes and relationships
// to text file with name you specify
void recursiveSave(Node *n){
	if (n->nodeType == group){
		// if it is a group node, it saves as group{}
		myfile << "group{\n";
	}else if (n->nodeType == model){
		// if model node, it saves as model {details}
		vertex3D min=n->hit.minP;
		vertex3D max=n->hit.maxP;
		myfile << "model{\n";
		// gets model type
		myfile << getModelType(n->modelType) << endl;
		// get material type
		myfile << n->currentMat.current->type << endl;
		// get min and max vals
		myfile << min.x << "," << min.y << "," << min.z << endl;
		myfile << max.x << "," << max.y << "," << max.z << endl;
	}else if (n->nodeType == transformation){
		// if transformation node, it saves as transformation {details}
		myfile << "transformation{\n";
		// Transform type
		myfile << getTransformType(n->transformationType) << endl;
		// vector to transform by
		if (n->transformationType == Rotate){
			myfile << n->amount4.w << "," << n->amount4.x << "," << n->amount4.y << "," << n->amount4.z << endl;
		}else {
			myfile << n->amount3.x << "," << n->amount3.y << "," << n->amount3.z<< endl;
		}
	}
	for (int i = 0; i < n->children->size(); i++){
		// call save for all the children of current node
		recursiveSave(n->children->at(i));
	}
		// close current bracket
		myfile << "}\n";
	return;
}
// parses a string for the type(group,model,transformation)
string parseType(string line){
	string ret = "";
	for (int i = 0; i < line.size(); i++){
		if(line[i] == '{' || line[i] == '}'){
			break;
		}
		ret += line[i];
	}	
	return ret;
}
// iteratively loads a text file into a scenegraph
void iterativeLoad(){
	ifstream infile (fileNameLoad);
	string line;
	if (infile.is_open()){
		getline(infile,line);
		while (getline(infile,line)){
			//cout << parseType(line) << endl;
			if(parseType(line) == "group"){
				// parse group
				SG->insertChildNodeHere(new NodeGroup());
			}else if (parseType(line) == "model"){
				// parse model
				string type,material;
				// gets model type, model material, and gets next line
				getline(infile,type);
				getline(infile,material);
				getline(infile,line);
				string x,y,z;
				vertex3D min,max;
				istringstream iss(line);
				// saves min point
				getline(iss,x,',');
				getline(iss,y,',');
				getline(iss,z,',');
				min = vertex3D(stof(x),stof(y),stof(z));
				// saves max point
				getline(infile,line);
				istringstream issLine2(line);
				getline(issLine2,x,',');
				getline(issLine2,y,',');
				getline(issLine2,z,',');
				max = vertex3D(stof(x),stof(y),stof(z));
				// creates model into Scene graph
				createModel(type,material,min,max);
			}else if (parseType(line) == "transformation"){
				getline(infile,line);
				if (line == "Translate"){
					// parses and insert Translation node
					getline(infile,line);
					istringstream iss(line);
					string x,y,z;
					getline(iss,x,',');
					getline(iss,y,',');
					getline(iss,z,',');
					insertTranslation(stof(x),stof(y),stof(z));
				}else if (line == "Rotate"){
					// parses and insert Rotation node
					getline(infile,line);
					istringstream iss(line);
					string w,x,y,z;
					getline(iss,w,',');
					getline(iss,x,',');
					getline(iss,y,',');
					getline(iss,z,',');				
					insertRotation(stof(w),stof(x),stof(y),stof(z));
				}else if (line == "Scale"){
					// parses and insert Scale node
					getline(infile,line);
					istringstream iss(line);
					string x,y,z;
					getline(iss,x,',');
					getline(iss,y,',');
					getline(iss,z,',');
					insertScale(stof(x),stof(y),stof(z));
				}
			}else if (parseType(line) == ""){
				// do nothing
			}
		}
		infile.close();
	}
	else cout << "Unable to open file"; 
	applyHitboxes();
}

void saveEverything(){
	// save current node
	Node *tempNode = SG->currentNode;
	Node temp = *tempNode;
	// go to the root and recursively save everything
	SG->goToRoot();
	recursiveSave(SG->currentNode);
}
void saveState(){
	// open filestream
	myfile = ofstream(fileNameSave);
	if (myfile.is_open()){
		// put open brackets
		myfile << "{" << endl;
		// save everything
		saveEverything();
		// close file
		myfile.close();
	}else{
		printf("Unable to open file\n");
	}
}


//The mouse function will be used for Ray picking using the intersection function in Scene Graph
void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		SG->Intersect(x,y);
	}
	glutPostRedisplay();
}

//Initializing the 2 lights and their settings
void initLighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos_2);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
}


//This will create the initial Scene Graph
//Root will always be created when the scene graph is initialized, therefore a Top group node is inserted
//The top group node will be used to remove everything from the scene.
void initGraph()
{
	//NODE 0 is Root
	//Node 1 is the top group node, which will be used to delete the entire scene when nessacary
			
	//DELETE THE ENTIRE GROUP NODE, WHEN CLEARING THE SCENE
	//The masterID for this first node will always be 1
	//When clearing, reset masterID to 1
	SG->insertChildNodeHere(new NodeGroup());
	//printf("\nFIRST NODE %i\n", SG->currentNode->nodeType);
}

//Reset the entire scene graph by deleting all the nodes by calling their destructors
void resetGraph(){
	SG->deleteScene();
	SG->hitBoxNodes.clear();
	masterID = 1;
	//Reinitialize the graph to create the root node
	initGraph();
}

//Keyboard function which will be used for Controlling everything in the program
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//UPPERCASE WASD is used to move the camera along the x and z axis
		case 'W':
			camera.Move(FORWARD);
			glutPostRedisplay();
			break;
		case 'A':
			camera.Move(LEFT);
			glutPostRedisplay();
			break;
		case 'S':
			camera.Move(BACK);
			glutPostRedisplay();
			break;
		case 'D':
			camera.Move(RIGHT);
			glutPostRedisplay();
			break;
		//UPPERCASE Q and E are used to move the camera up and down the y axis
		case 'Q':
			camera.Move(DOWN);
			glutPostRedisplay();
			break;
		case 'E':
			camera.Move(UP);
			glutPostRedisplay();
			break;
		//Quit with q
		case 'q':
		case 27:
			exit (0);
			break;
		case 'z':
			//CUBE
			//Set current to false so that the old node is not still selected
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->current = false;
			}
			//Go to top group node
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}

			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			//SG->insertChildNodeHere(new NodeGroup());
			//Create the initial transform at 0,0,0
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			//Add the cube
			SG->insertChildNodeHere(new NodeModel(Cube));
			PlaneExist = true;
			break;
		
		//The rest of these cases do the same thing for the other 4 objects
		case 'x':
			//SPHERE
			//Go to the top group node
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}
			
			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			
			SG->insertChildNodeHere(new NodeModel(Sphere));
			SG->currentNode->current = true;
			PlaneExist = true;
			break;
		case 'c':
			//CONE
			//Go to the top group node
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}
			
			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			
			SG->insertChildNodeHere(new NodeModel(Cone));
			PlaneExist = true;
			break;
		case 'b':
			//TORUS
			//Go to the top group node
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}
			
			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			
			SG->insertChildNodeHere(new NodeModel(Torus));
			PlaneExist = true;
			break;
		case 'm':
			// Tetrahedron
			//Go to the top group node
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}
			
			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			
			SG->insertChildNodeHere(new NodeModel(Tetrahedron));
			PlaneExist = true;
			break;


		/*The process for all the transformations are the same, I have commented the first case, 
		the only difference is that for rotation a vector 4D is used with an angle*/
		//---------------TRANSLATION-------------------//
		case 'y':
			if (PlaneExist){
				//Modify Transformation Node
				
				//If on a model, go to it's transformation parent
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				translation.x = 0;

				int mod = glutGetModifiers();
				
				//Only want to move along y axis
				if(mod == GLUT_ACTIVE_ALT)
					translation.y = -0.05;
				else
					translation.y = 0.05;
				
				translation.z = 0;

				//Create a tempNode so that we can delete and relink
				NodeTransform *tempNode = new NodeTransform(Translate, translation);

				//Find the hitbox
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				//Translate the hitbox 
				SG->hitBoxNodes.at(count)->hit.Translate(vec3D(translation.x, translation.y, translation.z));


				//qNow we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				//Add a push and pop matrix to make sure the translation is correct
				SG->insertChildNodeHere(new NodeGroup());
				//Move the child node back and link it
				SG->insertChildNodeHere(tempNode);

				//Redraw the nodes with the new transform
				SG->draw();
			}
			break;
		case 't':
			if (PlaneExist){
				//Modify Transformation Node
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				if(mod == GLUT_ACTIVE_ALT)
					translation.x = -0.05;
				else
					translation.x = 0.05;

				translation.y = 0;
				translation.z = 0;

				NodeTransform *tempNode = new NodeTransform(Translate, translation);
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				SG->hitBoxNodes.at(count)->hit.Translate(vec3D(translation.x, translation.y, translation.z));



				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
				break;
			}

		case 'u':
			if (PlaneExist){
				//Modify Transformation Node
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				translation.x = 0;
				translation.y = 0;
				if(mod == GLUT_ACTIVE_ALT)
				{
					translation.z = -0.05;
				}

				else
					translation.z = 0.05;

				NodeTransform *tempNode = new NodeTransform(Translate, translation);
				
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				SG->hitBoxNodes.at(count)->hit.Translate(vec3D(translation.x, translation.y, translation.z));

				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
			break;
		//---------------TRANSLATION-------------------//
		//------------------SCALE---------------------//
		case 'g':
		{
			//Modify Transformation Node
			if (PlaneExist){
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				scale.x = 1.0;

				int mod = glutGetModifiers();
				
				if(mod == GLUT_ACTIVE_ALT)
					scale.y = 0.5;
				else
					scale.y = 2.0;
				
				scale.z = 1.0;

				NodeTransform *tempNode = new NodeTransform(Scale, scale);

				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				SG->hitBoxNodes.at(count)->hit.Scale(vec3D(scale.x, scale.y, scale.z));


				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
		}
		break;

		case 'h':
		{
			if (PlaneExist){
				//Modify Transformation Node
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				if(mod == GLUT_ACTIVE_ALT)
					scale.x = 0.5;
				else
					scale.x = 2.0;

				scale.y = 1.0;
				scale.z = 1.0;

				NodeTransform *tempNode = new NodeTransform(Scale, scale);
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				SG->hitBoxNodes.at(count)->hit.Scale(vec3D(scale.x, scale.y, scale.z));



				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
		}
		break;

		case 'k':
		{
			if (PlaneExist){
				//Modify Transformation Node
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				scale.x = 1.0;
				scale.y = 1.0;
				if(mod == GLUT_ACTIVE_ALT)
					scale.z = 0.5;
				else
					scale.z = 2.0;

				NodeTransform *tempNode = new NodeTransform(Scale, scale);
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				SG->hitBoxNodes.at(count)->hit.Scale(vec3D(scale.x, scale.y, scale.z));

				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
		}
		break;
		//------------------SCALE---------------------//
		//-----------------ROTATE---------------------//
		case 'i':
		{
			//Modify Transformation Node
			if (PlaneExist){
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();
				
				if(mod == GLUT_ACTIVE_ALT)
					rotation.w = 1.0;
				else
					rotation.w = -1.0;
				
				rotation.x = 1.0;
				rotation.y = 0.0;
				rotation.z = 0.0;

				NodeTransform *tempNode = new NodeTransform(Rotate, rotation);

				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
			break;
		}

		case 'o':
		{
			//Modify Transformation Node
			if (PlaneExist){
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				if(mod == GLUT_ACTIVE_ALT)
					rotation.w = 1.0;
				else
					rotation.w = -1.0;
				
				rotation.x = 0.0;
				rotation.y = 1.0;
				rotation.z = 0.0;

				NodeTransform *tempNode = new NodeTransform(Rotate, rotation);
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
			break;
		}

		case 'p':
		{
			if (PlaneExist){
				//Modify Transformation Node
				while(SG->currentNode->nodeType == model)
					SG->goToParent();

				int mod = glutGetModifiers();

				if(mod == GLUT_ACTIVE_ALT)
					rotation.w = 1.0;
				else
					rotation.w = -1.0;
				
				rotation.x = 0.0;
				rotation.y = 0.0;
				rotation.z = 1.0;

				NodeTransform *tempNode = new NodeTransform(Rotate, rotation);
				
				int count;
				for(count = 0; count < SG->hitBoxNodes.size(); count++)
				{
					if(SG->hitBoxNodes.at(count)->current == true)
					{
						break;
					}
				}

				//Now we need to link nodes below it to the new node
				for(int i = 0; i < SG->currentNode->children->size(); i++)
				{
					tempNode->children->push_back(SG->currentNode->children->at(i));
					//The current node also needs to have it's old nodes removed
				}

				//The only node the currentNode should have is the the new node
				
				SG->currentNode->children->clear();

				SG->insertChildNodeHere(new NodeGroup());
				SG->insertChildNodeHere(tempNode);
				SG->draw();
			}
			break;
		}
		//------------------SCALE---------------------//


		case 'j':
			//delete the current Node
			if (PlaneExist){
			//Make sure that the node being deleted is a NodeModel
				if(SG->currentNode->nodeType == model)
				{
					SG->deleteThisNode();
				}
			}
			//Afterwards, select the next hitbox

			break;

		//File I/O
		case 's':
			printf("Enter a filename to save: ");
			cin >> fileNameSave;
			saveState();
			printf("\nSaved\n");
			break;
		case 'l':
			printf("Enter a filename to load: \n");
			cin >> fileNameLoad;
			iterativeLoad();
			if (SG->hitBoxNodes.size() >= 1){
				PlaneExist = true;
			}
			printf("\nLoaded\n");
			break;

		//Changing materials
		case 'T':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toRuby();
			}
			break;
		case 'Y':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toEmerald();
			}
			break;
		case 'U':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toCopper();
			}
			break;
		case 'I':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toBlackRubber();
			}
			break;
		case 'O':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toJade();
			}
			break;

		//Lighting Controls		
		//LIGHT 1 SECTION
		case ',': //y axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[1] -= 2;
			else
				light_pos[1] += 2;
			break;
		}

		case '.':	//x-axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[0] -= 2;
			else
				light_pos[0] += 2;
			break;
		}

		case '/':	//z-axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[2] -= 2;
			else
				light_pos[2] += 2;
			break;
		}

		//LIGHT 2 SECTION
		case '-': //y axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[1] -= 2;
			else
				light_pos_2[1] += 2;
			break;
		}

		case '=':	//x-axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[0] -= 2;
			else
				light_pos_2[0] += 2;
			break;
		}

		case '\\':	//z-axis
		{
			int mod = glutGetModifiers();
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[2] -= 2;
			else
				light_pos_2[2] += 2;
			break;
		}

		//This Section holds the toggles for the lights
		case '[':
			if(light_0_toggle == true)
			{
				//Currently light0 is ON, turn it off
				glDisable(GL_LIGHT0);
				light_0_toggle = false;
			}
			else
			{
				glEnable(GL_LIGHT0);
				light_0_toggle = true;
			}
			break;
		case ']':
			if(light_1_toggle == true)
			{
				//Currently light1 is ON, turn it off
				glDisable(GL_LIGHT1);
				light_1_toggle = false;
			}
			else
			{
				glEnable(GL_LIGHT1);
				light_1_toggle = true;
				//printf("light1on\n");
			}
			break;

		//Resetting the graph
		case 'r':
			resetGraph();
			break;
	}
	glutPostRedisplay();
}

//Init function
//Creates the scene graph
//Calls the first initGraph();
void init(void)
{	
	GLuint id = 1;
	camera = Camera();

	//init our scenegraph
	SG = new SceneGraph();

	//add various nodes
	//initializing our world
	initGraph();
}

//Used with GLUTReshape Func
//Sets Initial Camera POS
void reshape(int w, int h)
{
	glEnable(GLUT_DEPTH);

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);

	globalW = w;
	globalH = h;
	mouseX = w/2;
	mouseY = h/2;
	gluLookAt(5.0, 0.0, 5.0, 0, 0, 0, 0, 1, 0);
}


//Draws the Spheres around the lights
//And sets the materials of the objects
void lightSpheres()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb_2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff_2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec_2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny_2);

	glPushMatrix();
	glTranslatef(light_pos[0],light_pos[1],light_pos[2]);//This translate will be move the sphere around light 1
	glutSolidSphere(0.5,10,10);//Create the sphere
	glPopMatrix();


	glPushMatrix();
	glTranslatef(light_pos_2[0],light_pos_2[1],light_pos_2[2]);//This translate will be move the sphere around light 2
	glutSolidSphere(0.5,10,10);
	glPopMatrix();
	glPopMatrix();
}

//Display Function
//Draws all nodes, draws planes, and spheres around the lights
//Then Swaps buffers
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	createPlane();
	SG->draw();
	lightSpheres();

	glutSwapBuffers();
}

//Passive function, used for click and drag to look around
void passive(int x,int y){
	if (x < globalW && y < globalH){
		if ((x - mouseX) > 0){
			camera.Spin(SRIGHT,(x - mouseX)/globalW);
			mouseX = x;
		}
		else if ((x - mouseX) < 0){ 
			camera.Spin(SLEFT,-1*(x - mouseX)/globalW);
			mouseX = x;
		}
		if ((y - mouseY) > 0){
			camera.Spin(SDOWN,(y - mouseY)/globalH);
			mouseY = y;
		}else if ((y - mouseY) < 0){
			camera.Spin(SUP,-1*(y - mouseY)/globalH);
			mouseY = y;
		} 
	}
	glutPostRedisplay();
}

//Main Function
int main(int argc, char** argv)
{
	//cout the instructions
	cout << "\n\nCOMP SCI 3GC3 Assignment 3: Simple 3D Modeling System\n"
		<< "\tPasindu Gunasekara(001412155, gunasepi), Roberto Temelkovski(001418731 ,temelkr)\n\n"
		//<< "\t\tNOTE: Light 2 is initially DISABLED, to enable use the hotkeys below.\n\n"
		<< "Hotkeys\n"
		<< "-------\n"
		<< "Click on an object to pick it using Ray picking\n"
		<< "Add Objects to Scene\n"
		<< "\tz: CUBE\n\tx: SPHERE\n\tc: CONE\n\tb: TORUS\n\tm: TETRAHEDRON\n\n"
		<< "Transforming currently selected object\n"
		<< "\tTranslate(by 0.05 units per press) - t: x-axis\ty: y-axis\tu: z-axis\n\t\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
		<< "\tRotate(by 1 degree per press) - i: x-axis\to: y-axis\tp: z-axis\n\t\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
		<< "\tScale(by 0.5x) - g: x-axis\th: y-axis\tj: z-axis\n\t\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
		<< "\n\nr: Reset Scene"
		<< "\ns: Save current scene to file name entered in console"
		<< "\nl: load from \'filename.txt\'. Enter a file name after the prompt."
		<< "\nClick and Drag on the Scene to rotate the camera about it's current point.(EXTRA FEATURE)"
		<< "\nTranslate Camera"
		<< "\n\t(UPPER CASE)W A S D: Translate back and forth along the x-axis or the z-axis"
		<< "\n\t(UPPER CASE)Q E: Translate up and down, along the y-axis"
		<< "\n\nControlling LIGHT 1:"
		<< "\n\t(UPPERCASE)(Use ALT to go reverse) , (COMMA): y-axis, . (PERIOD): x-axis, / (FORWARD SLASH): z-axis"
		<< "\n\t[:Toggle ON/OFF LIGHT 1"
		<< "\n\nControlling LIGHT 2:"
		<< "\n\t(UPPERCASE)(Use ALT to go reverse) - (MINUS): y-axis, = (EQUALS): x-axis, \\ (BACK SLASH): z-axis"
		<< "\n\t]:Toggle ON/OFF LIGHT 1"
		<< "\n\nSwitching Materials:"
		<< "\n\t(UPPERCASE) T: Ruby, Y:Emerald, U: Copper, I: Black Rubber, O: Jade"
		<< "\nj: Delete currently selected object"
		<< "\nq: Quit\n";

	//Stuff for glut initialization
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	init();

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment 3 (gunasepi, temelkr)");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(passive);

	initLighting();

	//Enable culling on back faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Start the main loop
	glutMainLoop();
	return(0);
}