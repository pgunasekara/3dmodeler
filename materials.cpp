#include "materials.h"

cMaterial::cMaterial()
{
	emerald = {
		{0.0215, 0.1745, 0.0215, 1.0},
		{0.07568, 0.61424, 0.07568, 1.0},
		{0.633, 0.727811, 0.633, 1.0},
		{0.0,0.0,0.0,0.0},
		0.6
	};

	blackRubber = {
		{0.0,0.0,0.0},
		{0.01,0.01,0.01},
		{0.50,0.50,0.50},
		{0.0,0.0,0.0,0.0},
		0.6
	};

	jade = {
		{0.135,0.2225,0.1575,1.0},
		{0.54,0.89,0.63,1.0},
		{0.316228,0.316228,0.316228},
		{0.0,0.0,0.0,0.0},
		0.1
	};

	ruby = {
		{0.1745,0.01175,0.01175,1.0},
		{0.61424,0.04136,0.04136,1.0},
		{0.727811,0.626959,0.626959,1.0},
		{0.0,0.0,0.0,0.0},
		0.6
	};

	copper = {
		{0.19125,0.0735,0.0225,1.0},
		{0.7038,0.27048,0.0828,1.0},
		{0.256777,0.137622,0.086014,1.0},
		{0.0,0.0,0.0,0.0},
		0.1
	};

	current = emerald;
}


void cMaterial::toRuby(){current = ruby;}
void cMaterial::toBlackRubber(){current = blackRubber;}
void cMaterial::toJade(){current = jade;}
void cMaterial::toEmerald(){current = emerald;}
void cMaterial::toCopper(){current = copper;}