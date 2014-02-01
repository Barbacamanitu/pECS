#ifndef PECS_ENTITY_H
#define PECS_ENTITY_H
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>
#include "Component.h"
#include "Algo\UID.h"
#include <set>
#include <string>

namespace pECS
{
	class Entity
	{

	public:
		typedef std::unique_ptr<Entity> Ptr;
		Entity(void);
		virtual ~Entity(void);

	
		void SetParent(Entity* parent);
		Entity* GetParent();
		
		Ptr RemoveChild(int index);
		Ptr RemoveChild(Ptr& ent);
		
		void AddChild(Ptr& child);
		std::vector<Ptr> & GetChildren();

		bool AddComponent(Component::Ptr& component);
		bool RemoveComponent(std::string componentName);
		Component::Ptr const & GetComponent(std::string componentName);
		bool HasComponent(std::string componentName);
		std::set<std::string> const & GetComponentTypes();

		void Dump(int level);
		




	private:

		std::unordered_map<std::string,std::unique_ptr<Component>> mComponents;
		std::set<std::string> mTypes;
		Entity* mParent;
		std::vector<Ptr> mChildren;
		unsigned int mUID;
	};
}
#endif

