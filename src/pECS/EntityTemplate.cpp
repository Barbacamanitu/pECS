#include "..\..\include\pECS\EntityTemplate.h"


EntityTemplate::EntityTemplate()
{
}


EntityTemplate::~EntityTemplate()
{
}

void EntityTemplate::SetName(std::string name)
{
	mName = name;
}

std::string EntityTemplate::GetName()
{
	return mName;
}
