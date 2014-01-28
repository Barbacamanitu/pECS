#ifndef PECS_ENTITY_H
#define PECS_ENTITY_H
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>
#include "Component.h"
#include "Algo\UID.h"
#include <set>
#include <pECS\Pool\Poolable.h>

namespace pECS
{
	class Entity : public Poolable
	{

	public:
		typedef std::unique_ptr<Entity> Ptr;
		Entity(void);
		virtual ~Entity(void);

	
		void SetParent(Entity* parent);
		Entity* GetParent();
		std::set<std::type_index> const & GetComponentTypes();		
		
		Ptr RemoveChild(int index);
		Ptr RemoveChild(Ptr& ent);
		void AddChild(Ptr& child);
		std::vector<Ptr> & GetChildren();
		
		void Dump(int level);


		template<class T>
		void AddComponent(std::unique_ptr<Component>& comp)
		{
			static_assert(std::is_base_of<Component, T>::value, "You may only add objects derived from Component");
			std::type_index ti(typeid(T));
			if (!HasComponent<T>())
				mTypes.insert(ti);
			mComponents.insert(std::make_pair(ti,std::move(comp)));
		}

		template<class T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "You may only remove objects derived from Component");
			
			std::type_index ti(typeid(T));
			
			auto f = mComponents.find(ti);
			if (f != mComponents.end())
				mComponents.erase(f);
			
			auto t = mTypes.find(ti);
				if (t != mTypes.end())
					mTypes.erase(t);
		}

		template<class T>
		T* GetComponent()
		{
			auto it = mComponents.find(std::type_index(typeid(T)));
			if (it == mComponents.end())
				return nullptr;
			T* tmp = dynamic_cast<T*>(it->second.get());
			return tmp;
		}

		template<class T>
		bool HasComponent()
		{
			std::type_index ti(typeid(T));
			bool has = (mComponents.find(ti) != mComponents.end());
			return (has);
		}

		bool HasComponent(std::type_index ti);



	private:
		//Bag of components
		std::unordered_map<std::type_index,std::unique_ptr<Component>> mComponents;
		std::set<std::type_index> mTypes;
		Entity* mParent;
		std::vector<Ptr> mChildren;
		//Entityies can contain child entities so that they can be used as a container.
		
		unsigned int mUID;
	};
}
#endif

