#ifndef __NODETRANSFORM_H__	//guard against cyclic dependancy
#define __NODETRANSFORM_H__

#include "node.h"
#include "structs.h"
#include <string>

//Header for the tranformation nodes inheriting from Node.h

class NodeTransform:public Node{
public:
	NodeTransform(transformType whatType, Vector3D vec3);	//constructor
	NodeTransform(transformType whatType, Vector4D vec4);

	std::string type;
	virtual void nodeSpecificCodeDown();
};

#endif