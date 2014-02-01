#include <pECS\EntityFactory.h>

namespace pECS
{

	EntityFactory::EntityFactory()
	{
	}


	EntityFactory::~EntityFactory()
	{
	}

	Entity::Ptr EntityFactory::CreateEntity()
	{
		return nullptr;
	}

	Entity::Ptr EntityFactory::CreateEntityFromTemplate(std::string templateName)
	{
		auto it = mTemplates.find(templateName);
		if (it == mTemplates.end())
			return nullptr;
		return CreateEntityFromTemplate(it->second);
	}

	Entity::Ptr EntityFactory::CreateEntityFromTemplate(EntityTemplate& entityTemplate)
	{
		return nullptr;
	}

	void EntityFactory::AddTemplate(EntityTemplate temp)
	{
		mTemplates.insert(std::make_pair(temp.GetName(), temp));
	}
}
