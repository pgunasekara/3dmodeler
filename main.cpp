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
#include "Math/camera.h"
#include <vector>

float mouseX,mouseY,globalW,globalH;
bool buttonDown = false;
float camPos[] = {2.5, 2.5, 5};
float angle = 0.005f;
bool PlaneExist = false;
Hitbox *hit;
Camera camera;

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

void init(void)
{	GLuint id = 1;

	//init our scenegraph
	SG = new SceneGraph();
	camera = Camera();

	//add various nodes
	//initializing our world
	initGraph();
}

void passive(int x,int y){
	if ((x - mouseX) > 0){
    	camera.Spin(SRIGHT,angle);
	}
	else if ((x - mouseX) < 0){ 
    	camera.Spin(SLEFT,angle);
	}
	if ((y - mouseY) > 0){
		camera.Spin(SDOWN,angle);
	}else if ((y - mouseY) < 0){
		camera.Spin(SUP,angle);
	} 
	glutPostRedisplay();
}

void reshape(int w,int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0, 0, 0, 0);
	gluPerspective(45,1,1,100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);

	globalW = w;
	globalH = h;
	mouseX = w/2;
	mouseY = h/2;
	gluLookAt(2.5, 2.5, 2.5, 0, 0, 0, 0, 1, 0);
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	init();

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	//glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}