#ifndef __MATERIALS_H_
#define __MATERIALS_H_

typedef struct customMaterial
{
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
	customMaterial emerald;
	customMaterial blackRubber;
	customMaterial jade;
	customMaterial ruby;
	customMaterial copper;

	customMaterial current;

	void toRuby();
	void toBlackRubber();
	void toJade();
	void toEmerald();
	void toCopper();
};

#endif