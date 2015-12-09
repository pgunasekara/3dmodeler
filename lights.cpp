/*LIGHTING*/
float light_pos[] = {10.0f, 20.0f, 10.0f, 1.0f};//This is the position for the first light

float light_pos_2[] = {-10.0f, 20.0f, -10.0f, 1.0f};//This is the position for the second light

//Add spheres around the lights

glPushMatrix();
glTranslate3fv(light_pos);//This translate will be move the sphere around light 1
glutSolidSphere(0.5);//Create the sphere
glPopMatrix();


glPushMatrix();
glTranslate3fv(light_pos_2);//This translate will be move the sphere around light 2
glutSolidSphere(0.5);
glPopMatrix();

//Translate key
//Light 1 gets translated by 1 2 3 and ALT 1 2 3
//Light 2 gets translated by 4 5 6 and ALT 4 5 6
void keyboard(...)
{
	switch(key)
	{
		int mod = glutGetModifiers();
		
		//LIGHT 1 SECTION
		case 'Z': //y axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[1] -= 2;
			else
				light_pos[1] += 2;
			break;

		case 'X':	//x-axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[0] -= 2;
			else
				light_pos[0] += 2;
			break;

		case 'C':	//z-axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos[2] -= 2;
			else
				light_pos[2] += 2;
			break;

		//LIGHT 2 SECTION
		case 'V': //y axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[1] -= 2;
			else
				light_pos_2[1] += 2;
			break;

		case 'B':	//x-axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[0] -= 2;
			else
				light_pos_2[0] += 2;
			break;

		case 'N':	//z-axis
			if(mod == GLUT_ACTIVE_ALT)
				light_pos_2[2] -= 2;
			else
				light_pos_2[2] += 2;
			break;
	}
	glutPostRedisplay();
}



//Materials
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


//This Toggles the LIGHTS on or off
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
case '[':
	if(light_1_toggle == true)
	{
		//Currently light1 is ON, turn it off
		glDisable(GL_LIGHT1);
		light_1_toggle = false;
	}
	else
	{
		glEnable(GL_LIGHT0);
		light_1_toggle = true;
	}

//This is the Instructions cout

cout << "COMP SCI 3GC3 Assignment 3: Simple 3D Modeling System\n"
	<< "\tPasindu Gunasekara(001412155, gunasepi), Roberto Temelkovski(001418731 ,temelkr)\n\n"
	<< "\t\tNOTE: Light 2 is initially DISABLED, to enable use the hotkeys below.\n\n"
	<< "Hotkeys\n"
	<< "-------\n"
	<< "Click on an object to pick it using Ray picking\n"
	<< "Add Objects to Scene\n"
	<< "\tz: CUBE\n\tx: SPHERE\n\tc: CONE\n\tb: TORUS\n\tm: TETRAHEDRON\n\n"
	<< "Transforming currently selected object\n"
	<< "\tTranslate(by 0.05 units per press) - t: x-axis\ty: y-axis\tu: z-axis\n\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
	<< "\tRotate(by 1 degree per press) - i: x-axis\to: y-axis\tp: z-axis\n\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
	<< "\tScale(by 0.5x) - g: x-axis\th: y-axis\tj: z-axis\n\tNOTE: Use ALT modifier to go in the reverse direction with the same keys.\n"
	<< "\n\nr: Reset Scene"
	<< "\ns: Save current scene to file save.txt"
	<< "\nl: load from \'filename.txt\'. Enter a file name after the prompt."
	<< "\nClick and Drag on the Scene to rotate the camera about it's current point.(EXTRA FEATURE)"
	<< "\nTranslate Camera"
	<< "\n\t(UPPER CASE)W A S D: Translate back and forth along the x-axis or the z-axis"
	<< "\n\t(UPPER CASE)Q E: Translate up and down, along the y-axis"
	<< "\n\nControlling LIGHT 1:"
	<< "\n\t(UPPERCASE)(Use ALT to go reverse) Z: y-axis, X: x-axis, C: z-axis"
	<< "\n\t[:Toggle ON/OFF LIGHT 1"
	<< "\n\nControlling LIGHT 2:"
	<< "\n\t(UPPERCASE)(Use ALT to go reverse) V: y-axis, B: x-axis, N: z-axis"
	<< "\n\t]:Toggle ON/OFF LIGHT 1"
	<< "\n\nSwitching Materials:"
	<< "\n\t(UPPERCASE) T: Ruby, Y:Emerald, U: Copper, I: Black Rubber, O: Jade";