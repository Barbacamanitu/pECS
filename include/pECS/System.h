#ifndef PECS_SYSTEM_H
#define PECS_SYSTEM_H
#include "Entity.h"
#include <set>
namespace pECS
{
	class System
	{
	public:
		System(void);
		~System(void);


		
		void Process(std::vector<Entity::Ptr>& entities);
		void ProcessEntity(Entity::Ptr & entity);
		template<class T>
		void AddComponentType()
		{
			mTypes.insert(std::type_index(typeid(T)));
		}
	protected:
		virtual void Logic(Entity::Ptr & entity) = 0;
	private:
		bool IsEntityValid(Entity::Ptr const& entity);
		std::set<std::type_index> mTypes;


	};
}
#endif

