#ifndef __NODEGROUP_H__	//guard against cyclic dependancy
#define __NODEGROUP_H__

#include "node.h"

//Node group
class NodeGroup: public Node
{
public:
	NodeGroup();

	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
};

#endif