#ifndef PECS_COMPONENT_H
#define PECS_COMPONENT_H
#include "Pool\IPoolable.h"
namespace pECS
{
	class Component : public IPoolable
{
public:
	Component(void);
	virtual ~Component(void);
};
}
#endif

