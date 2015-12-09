#ifndef __MATERIALS_H_
#define __MATERIALS_H_

#include <string>
using namespace std;

//Class to hold the materials and switch between them


typedef struct customMaterial
{
	string type;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shine;

}customMaterial;

class cMaterial
{
public:
	cMaterial();
	~cMaterial();
	customMaterial emerald;
	customMaterial blackRubber;
	customMaterial jade;
	customMaterial ruby;
	customMaterial copper;

	customMaterial *current;

	string currentString;

	void fromString(string arg);
	void toRuby();
	void toBlackRubber();
	void toJade();
	void toEmerald();
	void toCopper();
};

#endif