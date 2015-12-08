#include "nodeTransform.h"
#include <stdio.h> //needed for printf command
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Math/math3D.h"
#include <stdio.h>

//for gltranslate and gl scale
NodeTransform::NodeTransform(transformType whatType, Vector3D vec3){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = vec3;
	//printf("%f %f %f\n",amount3.x,amount3.y,amount3.z);
}

//for gl rotate
NodeTransform::NodeTransform(transformType whatType, Vector4D vec4){
	nodeType = transformation;
	transformationType = whatType;
	amount4 = vec4;
}

void NodeTransform::nodeSpecificCodeDown(){
	switch (transformationType){
	case Translate:
		glTranslatef(amount3.x, amount3.y, amount3.z);
		tr = vec3D(amount3.x, amount3.y, amount3.z);
		break;
	case Rotate:
		glRotatef(amount4.w, amount4.x, amount4.y, amount4.z);
		rot = quaternion(amount4.w, amount4.x, amount4.y, amount4.z);
		break;
	case Scale:
		glScalef(amount3.x, amount3.y, amount3.z);
		sc = vec3D(amount3.x, amount3.y, amount3.z);
		break;
	}
}
