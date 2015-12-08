#include "materials.h"

cMaterial::cMaterial()
{
	/*emerald = {
		{0.0215, 0.1745, 0.0215, 1.0},
		{0.07568, 0.61424, 0.07568, 1.0},
		{0.633, 0.727811, 0.633, 1.0},
		{0.0,0.0,0.0,0.0},
		0.6
	};*/
	emerald.ambient[0] =0.0215;
	emerald.ambient[1] = 0.1745;
	emerald.ambient[2] = 0.0215;
	emerald.ambient[3] = 1.0;

	emerald.diffuse[0] =0.0215;
	emerald.diffuse[1] = 0.1745;
	emerald.diffuse[2] = 0.0215;
	emerald.diffuse[3] = 1.0;
	
	emerald.specular[0] =0.0215;
	emerald.specular[1] = 0.1745;
	emerald.specular[2] = 0.0215;
	emerald.specular[3] = 1.0;

	emerald.emission[0] =0.0;
	emerald.emission[1] =0.0;
	emerald.emission[2] =0.0;
	emerald.emission[3] =0.0;

	emerald.shine = 0.6;

	/*blackRubber = {
		{0.0,0.0,0.0},
		{0.01,0.01,0.01},
		{0.50,0.50,0.50},
		{0.0,0.0,0.0,0.0},
		0.6
	};*/

	blackRubber.ambient[0] =0.0;
	blackRubber.ambient[1] =0.0;
	blackRubber.ambient[2] =0.0;
	blackRubber.ambient[3] =1.0;

	blackRubber.diffuse[0] =0.01;
	blackRubber.diffuse[1] =0.01;
	blackRubber.diffuse[2] =0.01;
	blackRubber.diffuse[3] =1.0;
	
	blackRubber.specular[0] =0.50;
	blackRubber.specular[1] =0.50;
	blackRubber.specular[2] =0.50;
	blackRubber.specular[3] =1.00;

	blackRubber.emission[0] =0.0;
	blackRubber.emission[1] =0.0;
	blackRubber.emission[2] =0.0;
	blackRubber.emission[3] =0.0;

	blackRubber.shine = 0.6;


	jade.ambient[0] =0.135;
	jade.ambient[1] =0.2225;
	jade.ambient[2] =0.1575;
	jade.ambient[3] =1.0;

	jade.diffuse[0] =0.54;
	jade.diffuse[1] =0.89;
	jade.diffuse[2] =0.63;
	jade.diffuse[3] =1.0;
	
	jade.specular[0] =0.316228;
	jade.specular[1] =0.316228;
	jade.specular[2] =0.316228;
	jade.specular[3] =1.00;

	ruby.emission[0] =0.0;
	ruby.emission[1] =0.0;
	ruby.emission[2] =0.0;
	ruby.emission[3] =0.0;

	jade.shine = 0.1;

	/*ruby = {
		{0.1745,0.01175,0.01175,1.0},
		{0.61424,0.04136,0.04136,1.0},
		{0.727811,0.626959,0.626959,1.0},
		{0.0,0.0,0.0,0.0},
		0.6
	};*/

	ruby.ambient[0] =0.1745;
	ruby.ambient[1] =0.01175;
	ruby.ambient[2] =0.01175;
	ruby.ambient[3] =1.0;

	ruby.diffuse[0] =0.61424;
	ruby.diffuse[1] =0.04136;
	ruby.diffuse[2] =0.04136;
	ruby.diffuse[3] =1.0;
	
	ruby.specular[0] =0.727811;
	ruby.specular[1] =0.626959;
	ruby.specular[2] =0.626959;
	ruby.specular[3] =1.00;

	ruby.emission[0] =0.0;
	ruby.emission[1] =0.0;
	ruby.emission[2] =0.0;
	ruby.emission[3] =0.0;

	ruby.shine = 0.6;


	copper.ambient[0] =0.19125;
	copper.ambient[1] =0.0735;
	copper.ambient[2] =0.0225;
	copper.ambient[3] =1.0;

	copper.diffuse[0] =0.7038;
	copper.diffuse[1] =0.27048;
	copper.diffuse[2] =0.0828;
	copper.diffuse[3] =1.0;
	
	copper.specular[0] =0.256777;
	copper.specular[1] =0.137622;
	copper.specular[2] =0.086014;
	copper.specular[3] =1.00;

	copper.emission[0] =0.0;
	copper.emission[1] =0.0;
	copper.emission[2] =0.0;
	copper.emission[3] =0.0;
	copper.shine = 0.1;

	current = emerald;
}


void cMaterial::toRuby(){current = ruby;}
void cMaterial::toBlackRubber(){current = blackRubber;}
void cMaterial::toJade(){current = jade;}
void cMaterial::toEmerald(){current = emerald;}
void cMaterial::toCopper(){current = copper;}