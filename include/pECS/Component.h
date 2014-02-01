#ifndef PECS_COMPONENT_H
#define PECS_COMPONENT_H

#include <string>
#include <memory>
#include <typeindex>
namespace pECS
{

	class Component
	{
	public:
		typedef std::unique_ptr<Component> Ptr;
		Component(void);
		virtual ~Component(void);
		std::string GetName()
		{
			return mName;
		}
	private:
		void SetName(std::string name);
		std::string mName;
	};
}
#endif

