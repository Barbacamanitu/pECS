#include <pECS\System.h>

namespace pECS
{
	System::System(void)
	{
	}
	
	
	System::~System(void)
	{
	}

	void System::ProcessEntity(Entity::Ptr & entity)
	{
		
		Logic(entity);
		Process(entity->GetChildren()); //Process all children of current entity
	};

	void System::Process(std::vector<Entity::Ptr>& entities)
	{
		for (Entity::Ptr& child : entities)
		{
			if (IsEntityValid(child))
				ProcessEntity(child);
		}
	}

	bool System::IsEntityValid(Entity::Ptr const& entity)
	{
		
		return true;
	}




}
