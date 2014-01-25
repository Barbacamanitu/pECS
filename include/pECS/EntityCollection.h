#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <vector>
#include <memory>


namespace pECS
{
	class Entity;
	class EntityCollection
	{
	private:
		typedef std::vector<std::unique_ptr<Entity>> EntVec;
		EntVec mChildren;
		Entity* mParent;
	public:
		std::unique_ptr<Entity> EntityCollection::Remove(int index);
		std::unique_ptr<Entity> EntityCollection::Remove(std::unique_ptr<Entity>& ent);
		void EntityCollection::Add(std::unique_ptr<Entity>& child);
		EntVec & EntityCollection::All();
		
	};
}

#endif