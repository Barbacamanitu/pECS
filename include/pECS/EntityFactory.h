#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <pECS\Entity.h>
#include <pECS\Component.h>
#include <pECS\System.h>
#include <pECS\EntityTemplate.h>

#include <string>
#include <map>

namespace pECS
{

	class EntityFactory
	{
	public:
		EntityFactory();
		~EntityFactory();

		Entity::Ptr CreateEntity();
		Entity::Ptr CreateEntityFromTemplate(std::string templateName);
		Entity::Ptr CreateEntityFromTemplate(EntityTemplate& entityTemplate);
		void AddTemplate(EntityTemplate temp);
	private:
		std::map<std::string, EntityTemplate> mTemplates;

	};
}

#endif