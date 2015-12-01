/* CS 3GC3 - Texturing sample
 * by R. Teather
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

int currentChild = 0;

//node ids
int masterID = 0;

Vector3D ip;

int getID(){
	return masterID++;
}
// for the unprojection
double* start = new double[3];
double* finish = new double[3];

SceneGraph *SG;

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		SG->Intersect(x,y,hit);
	}
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
void initGraph(){
	//temporary place which holds out values
	//Vector3D tempVec3;


	//TRANSFORMATION
	//a tranlation transformation node
	//how much translation
	//tempVec3.x = 1;
	//tempVec3.y = 1;
	//tempVec3.z = 1;
	//add the node as a child of root node
	//NodeTransform *T1 = new NodeTransform(Translate, tempVec3);
	//insert the node into the graph
	//SG->insertChildNodeHere(T1);
	//go to the child node
	//SG->goToChild(0);


	//MODEL
	//we will now add a teapot model to the graph as a child of the
	//transformation node
	//NodeModel *M1 = new NodeModel(Teapot);
	//insert the node into the graph
	//SG->insertChildNodeHere(M1);


	//THE SAME FLOW CAN BE USED TO DYNAMICALLY ADD NODES
	//DURING RUNTIME
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
		case 's':
			//solid sphere
			//Add the new transform at the root node
			SG->goToRoot();

			ip.x = 0;
			ip.y = 0;
			ip.z = 0;
			transforms.push_back(new NodeTransform(Translate, ip));
			//NodeTransform *T1 = new NodeTransform(Translate, ip);
			SG->insertChildNodeHere(transforms.at(transforms.size()-1));
			//GO TO NEXT CHILD
			SG->goToChild(currentChild);
			currentChild++;

			models.push_back(new NodeModel(Teapot));
			//NodeModel *M1 = new NodeModel(Teapot);
			SG->insertChildNodeHere(models.at(models.size()-1));
			hit = new Hitbox();
			break;
		case 'd':
			//solid sphere
			//Vector3D ip;
			SG->goToRoot();
			ip.x = 0;
			ip.y = 1;
			ip.z = 1;
			transforms.push_back(new NodeTransform(Translate, ip));
			//NodeTransform *T1 = new NodeTransform(Translate, ip);
			SG->insertChildNodeHere(transforms.at(transforms.size()-1));
			//SG->insertChildNodeHere(T1);
			//GO TO NEXT CHILD
			SG->goToChild(currentChild);

			//NodeModel *M1 = new NodeModel(Cube);
			models.push_back(new NodeModel(Cube));
			//SG->insertChildNodeHere(M1);
			SG->insertChildNodeHere(models.at(models.size()-1));
			hit = new Hitbox();
			PlaneExist = true;
			break;

		case 'a':
			SG->goToChild(1);
			ip.x += 3;
			ip.y += 3;
			ip.x += 0;
			NodeTransform *tmp = new NodeTransform(Translate, ip);
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

	init();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}