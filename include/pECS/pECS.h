#ifndef PECS_H
#define PECS_H
#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "Pool\Pool.h"
#include <memory>
namespace pECS
{

	//Typedefs
	typedef std::unique_ptr<Entity> EntityPtr;
	typedef std::unique_ptr<Component> ComponentPtr;



	
}

#endif