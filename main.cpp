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

//sceneGraph
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"
#include <vector>

float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;
bool PlaneExist = false;
Hitbox *hit;

vector<NodeTransform*> transforms;
vector<NodeModel*> models;

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



void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		SG->Intersect(x,y,hit);
	}
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

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;
		case 'z':
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
			hit = new Hitbox();
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
		case 'n':
			//TEAPOT
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
			
			SG->insertChildNodeHere(new NodeModel(Teapot));
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

		case 'd':
			//delete the current Node
			//TODO, FIRST select the node to delete!

			//Make sure that the node being deleted is a NodeModel
			if(SG->currentNode->nodeType == model)
			{
				SG->deleteThisNode();
			}
			break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
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
}

void init(void)
{	GLuint id = 1;
	start[0] = 0;
	start[1] = 0;
	start[2] = 0;
	finish[0] = 1;
	finish[1] = 1;
	finish[2] = 1;

	glEnable(GLUT_DEPTH);

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	//init our scenegraph
	SG = new SceneGraph();

	//add various nodes
	//initializing our world
	initGraph();
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);

	//draw the sceneGraph
	drawAxis();
	SG->draw();
	if (PlaneExist){
		hit->draw();
	}

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("SimpleSceneGraph");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	initLighting();

	init();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}