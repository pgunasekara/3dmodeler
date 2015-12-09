/*TODO

When clicked, switch currentNode

With ray casting, once an object is selected, search for it's ID
Then switch current node based on the ID*/

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Math/camera.h"
#include "Math/Hitbox.h"
#include "structs.h"
#include "Math/math3D.h"

//#include "node.h"
#include "materials.h"
//sceneGraph
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"

#include "nodeTransform.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

float mouseX,mouseY,globalW,globalH;
bool buttonDown = false;
float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.005f;
bool PlaneExist = false;
Hitbox *hit;
Camera camera;
ofstream myfile ("save.txt");
ifstream infile ("save.txt");

//node ids
int masterID = 0;

Vector3D ip;
Vector3D translation;
Vector4D rotation; 
Vector3D scale;

int getID()
{
	return masterID++;
}
// for the unprojection
double* start = new double[3];
double* finish = new double[3];

SceneGraph *SG;


/*LIGHTING*/
float light_pos[] = {0.0f, 10.0f, 0.0f, 1.0f};
float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {1, 1, 1, 1};
float spec0[4] = {1, 1, 1, 1};

float m_amb[] = {0.0215, 0.1745, 0.0215, 1.0};
float m_diff[] = {0.07568, 0.61424, 0.07568, 1.0};
float m_spec[] = {0.633, 0.727811, 0.633, 1.0};
float shiny = 0.6;
//LIGHTING

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
		case Cylinder:
			return "Cylinder";
			break;
		case Torus:
			return "Torus";
			break;
		case Tetrahedron:
			return "Tetrahedron";
			break;
		case Dodecahedron:
			return "Dodecahedron";
			break;
		case Icosahedron:
			return "Icosahedron";
			break;
		}
}

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
/*
void recursiveSave(Node *n){
	if (n->nodeType == group){
		myfile << "group:{\n";
		// save ID
		myfile << "ID:" << n->ID << "," << endl;
	}else if (n->nodeType == model){
		vertex3D min=n->hit.minP;
		vertex3D max=n->hit.maxP;
		myfile << "model:{\n";
		// gives number
		myfile << "modelType:"  << getModelType(n->modelType) << endl;
		// put materials once pasi gets it
		myfile << "lowHit" << min.x << "," << min.y << "," << min.z << ")" << endl;
		myfile << "highHit:(" << max.x << "," << max.y << "," << max.z << ")" << endl;
		myfile << "Material:" << n->currentMat.current->type << endl;
	}else if (n->nodeType == transformation){
		myfile << "transformation:{\n";
		// gives number
		myfile << "transformType: "  << getTransformType(n->transformationType) << endl;
		if (n->transformationType == Rotate){
			myfile << "vector:(" << n->amount4.w << "," << n->amount4.x << "," << n->amount4.y << "," << n->amount4.z << ")" << endl;
		}else {
			//cout << "\t vector: (" << n->amount3.x << "," << n->amount3.y << "," << n->amount3.z << ")" << endl;
			myfile << "vector:(" << n->amount3.x << "," << n->amount3.y << "," << n->amount3.z << ")" << endl;
		}
		// put materials once pasi gets it
		//myfile << 
	}
	for (int i = 0; i < n->children->size(); i++){
		recursiveSave(n->children->at(i));
	}
		myfile << "}\n";
	return;
}
*/

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
	//SG->currentNode->hit.updateHitbox(min,max);
}

void insertTranslation(float x, float y, float z){
	//printf("%f %f %f\n", x,y,z);
	translation.x = x;
	translation.y = y;
	translation.z = z;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Translate,translation));
}

void insertRotation(float w,float x, float y, float z){
	//printf("%f %f %f %f\n",w,x,y,z);
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	rotation.w = w;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Rotate,rotation));
}

void insertScale(float x, float y, float z){
	//printf("%f %f %f\n", x,y,z);
	translation.x = x;
	translation.y = y;
	translation.z = z;
	SG->insertChildNodeHere(new NodeGroup());
	SG->insertChildNodeHere(new NodeTransform(Scale,translation));
}

void recursiveSave(Node *n){
	if (n->nodeType == group){
		myfile << "group{\n";
	}else if (n->nodeType == model){
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
		myfile << "transformation{\n";
		// gives number
		myfile << getTransformType(n->transformationType) << endl;
		if (n->transformationType == Rotate){
			myfile << n->amount4.w << "," << n->amount4.x << "," << n->amount4.y << "," << n->amount4.z << endl;
		}else {
			myfile << n->amount3.x << "," << n->amount3.y << "," << n->amount3.z<< endl;
		}
	}
	for (int i = 0; i < n->children->size(); i++){
		recursiveSave(n->children->at(i));
	}
		myfile << "}\n";
	return;
}

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

void recursiveLoad(){
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
				getline(infile,type);
				getline(infile,material);
				getline(infile,line);
				string x,y,z;
				vertex3D min,max;
				istringstream iss(line);
				getline(iss,x,',');
				getline(iss,y,',');
				getline(iss,z,',');
				min = vertex3D(stof(x),stof(y),stof(z));
				getline(infile,line);
				istringstream issLine2(line);
				getline(issLine2,x,',');
				getline(issLine2,y,',');
				getline(issLine2,z,',');
				max = vertex3D(stof(x),stof(y),stof(z));
				createModel(type,material,min,max);
			}else if (parseType(line) == "transformation"){
				getline(infile,line);
				if (line == "Translate"){
					getline(infile,line);
					istringstream iss(line);
					string x,y,z;
					getline(iss,x,',');
					getline(iss,y,',');
					getline(iss,z,',');
					insertTranslation(stof(x),stof(y),stof(z));
				}else if (line == "Rotate"){
					getline(infile,line);
					istringstream iss(line);
					string w,x,y,z;
					getline(iss,w,',');
					getline(iss,x,',');
					getline(iss,y,',');
					getline(iss,z,',');				
					insertRotation(stof(w),stof(x),stof(y),stof(z));
				}else if (line == "Scale"){
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
}

void saveEverything(){
	Node *tempNode = SG->currentNode;
	Node temp = *tempNode;
	//delete tempNode;
	SG->goToRoot();
	recursiveSave(SG->currentNode);
}
void saveState(){
	if (myfile.is_open()){
		myfile << "{" << endl;
		saveEverything();
		myfile.close();
	}else{
		printf("Unable to open file\n");
	}
}

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		SG->Intersect(x,y);
	}
	glutPostRedisplay();
}

void initLighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
}

/* drawAxis() -- draws an axis at the origin of the coordinate system
 *   red = +X axis, green = +Y axis, blue = +Z axis
 */
void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0,0,0);
	glVertex3f(50,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,50,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,50);
	glEnd();
}

//function which will populate a sample graph 
void initGraph()
{
	//Initial Transformation node
	//This is node 1, every time a node is created the masterId will incremenet by 2
	//NODE 0 is Root
		
	//DELETE THE ENTIRE GROUP NODE, WHEN CLEARING THE SCENE
	//The masterID for this first node will always be 1
	//When clearing, reset masterID to 0
	SG->insertChildNodeHere(new NodeGroup());
	printf("\nFIRST NODE %i\n", SG->currentNode->nodeType);
}

void resetGraph(){
	SG->deleteScene();
	SG->hitBoxNodes.clear();
	masterID = 1;
	initGraph();
}

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
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
		case 'Q':
			camera.Move(DOWN);
			glutPostRedisplay();
			break;
		case 'E':
			camera.Move(UP);
			glutPostRedisplay();
			break;
		case 'q':
		case 27:
			exit (0);
			break;
		case 'z':
			//CUBE
			//Go to the top group node
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->current = false;
			}
			while(SG->currentNode->ID > 1)
			{
				SG->goToParent();
			}

			//Create new transformation Node
			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			//SG->insertChildNodeHere(new NodeGroup());
			SG->insertChildNodeHere(new NodeTransform(Translate, ip));
			
			SG->insertChildNodeHere(new NodeModel(Cube));
			hit = new Hitbox();
			break;
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
			//hit = new Hitbox();
			break;

			//hit = new Hitbox();
			//PlaneExist = true;
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
			hit = new Hitbox();
			break;
		case 'v':
			//CYLINDER
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
			
			SG->insertChildNodeHere(new NodeModel(Cylinder));
			hit = new Hitbox();
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
			hit = new Hitbox();
			break;
		case 'm':
			//CUBE
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
			hit = new Hitbox();
			break;


		//---------------TRANSLATION-------------------//
		case 'y':
		{
			//Modify Transformation Node
			//Node *tempCurrentNode = SG->currentNode;
			
			while(SG->currentNode->nodeType == model)
				SG->goToParent();

			translation.x = 0;

			int mod = glutGetModifiers();
			
			if(mod == GLUT_ACTIVE_ALT)
				translation.y = -0.05;
			else
				translation.y = 0.05;
			
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


			//qNow we need to link nodes below it to the new node
			for(int i = 0; i < SG->currentNode->children->size(); i++)
			{
				tempNode->children->push_back(SG->currentNode->children->at(i));
				//The current node also needs to have it's old nodes removed
			}

			//The only node the currentNode should have is the the new node
			
			SG->currentNode->children->clear();

			SG->insertChildNodeHere(new NodeGroup());
			SG->insertChildNodeHere(tempNode);
			//SG->currentNode = tempCurrentNode;

			SG->draw();
			break;
		}

		case 't':
		{
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
		{
			Node *tempCurrentNode;
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
			break;
		}
		//---------------TRANSLATION-------------------//
		//------------------SCALE---------------------//
		case 'g':
		{
			//Modify Transformation Node
			//Node *tempCurrentNode = SG->currentNode;
			
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
			//SG->currentNode = tempCurrentNode;

			break;
		}

		case 'h':
		{
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
			break;
		}

		case 'k':
		{
			Node *tempCurrentNode;
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
			break;
		}
		//------------------SCALE---------------------//
		//-----------------ROTATE---------------------//
		case 'i':
		{
			//Modify Transformation Node
			//Node *tempCurrentNode = SG->currentNode;
			
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

			SG->hitBoxNodes.at(count)->hit.Rotate(quaternion(rotation.w,rotation.x, rotation.y, rotation.z));


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
			//SG->currentNode = tempCurrentNode;

			break;
		}

		case 'o':
		{
			//Modify Transformation Node
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

			SG->hitBoxNodes.at(count)->hit.Rotate(quaternion(rotation.w,rotation.x, rotation.y, rotation.z));



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

		case 'p':
		{
			Node *tempCurrentNode;
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

			SG->hitBoxNodes.at(count)->hit.Rotate(quaternion(rotation.w,rotation.x, rotation.y, rotation.z));

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
		//------------------SCALE---------------------//


		case 'j':
			//delete the current Node
			//TODO, FIRST select the node to delete!

			//Make sure that the node being deleted is a NodeModel
			if(SG->currentNode->nodeType == model)
			{
				SG->deleteThisNode();
			}
			break;
		case 's':
			printf("saved\n");
			saveState();
			break;
		case 'l':
			printf("loaded\n");
			recursiveLoad();
			break;

		//CHANGE THE MATERIAL
		case '[':
			if(SG->currentNode->nodeType == model)
			{
				SG->currentNode->currentMat.toRuby();
			}
			break;
		case 'r':
			resetGraph();
			break;
	}
	glutPostRedisplay();
}

/*void special(int key, int x, int y)
{
	/* arrow key presses move the camera *0/
	switch(key)
	{
		case GLUT_KEY_LEFT:
			camPos[0]-=0.1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=0.1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 0.1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 0.1;
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 0.1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 0.1;
			break;

	}
	glutPostRedisplay();
}*/

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
	gluLookAt(2.5, 2.5, 2.5, 0, 0, 0, 0, 1, 0);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw the sceneGraph
	drawAxis();
	SG->draw();
	//if (PlaneExist){
	//	hit->draw();
	//}

	glutSwapBuffers();
}

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

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	init();

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("SimpleSceneGraph");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(passive);

	initLighting();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}