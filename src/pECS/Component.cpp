#include <pECS\Component.h>

namespace pECS
{
Component::Component(void)
{
}


Component::~Component(void)
{
}

void Component::SetName(std::string name)
{
	mName = name;
}

}
