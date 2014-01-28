#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <vector>
#include <memory>
#include <pECS\Pool\MemoryManagerUtility.h>


namespace pECS
{

	class FixedPool;

	class MemoryManager
	{
	public:
		MemoryManager();
		~MemoryManager();

		static size_t SizeOfLargestType()
		{

		};
		FixedPool* CreatePool(size_t objectCount, size_t objectSize);



		template<typename... Types>
		FixedPool* CreatePool(size_t objectCount)
		{
			static_assert(is_base_of_all<Poolable, Types...>::value, "You may only pool Poolable objects.");
			size_t largestSize = sizeof(largest<Types...>::type{});
			return CreatePool(objectCount, largestSize);

		}
		void RegisterPool(FixedPool* pool);
		void DeregisterPool(FixedPool* pool);
		bool IsPoolValid(FixedPool* pool);

	private:
		std::vector<FixedPool*> mPools;


	};
}

#endif