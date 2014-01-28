#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <vector>
#include <memory>
#include <pECS\Pool\MemoryManagerUtility.h>


namespace pECS
{

	class ObjectPool;

	class MemoryManager
	{
	public:
		MemoryManager();
		~MemoryManager();

		static size_t SizeOfLargestType()
		{

		};
		ObjectPool* CreatePool(size_t objectCount, size_t objectSize);



		template<typename... Types>
		ObjectPool* CreatePool(size_t objectCount)
		{
			static_assert(is_base_of_all<Poolable, Types...>::value, "You may only pool Poolable objects.");
			size_t largestSize = sizeof(largest<Types...>::type{});
			return CreatePool(objectCount, largestSize);

		}
		void RegisterPool(ObjectPool* pool);
		void DeregisterPool(ObjectPool* pool);
		bool IsPoolValid(ObjectPool* pool);

	private:
		std::vector<ObjectPool*> mPools;


	};
}

#endif