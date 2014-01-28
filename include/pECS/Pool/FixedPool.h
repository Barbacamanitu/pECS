#ifndef FixedPool_H
#define FixedPool_H

#include <vector>
#include <memory>

#include <pECS\Pool\PoolReturner.h>
namespace pECS
{
	class Poolable;
	class MemoryManager;
	class FixedPool
	{
		friend class MemoryManager;
		friend class PoolReturner;
	private:
		FixedPool(MemoryManager* manager);
		void * mPool;
		std::vector<void *> mAvailable;

		
		size_t mObjectSize;
		size_t mCount;
		size_t mOverflowLimit;

		MemoryManager * mMemoryManager;
		PoolReturner* mReturner;

		
		void Clear();
		void Allocate(int count, size_t size);
		char * GetOffset(int index);
		bool Return(Poolable * ptr);
	public:
		~FixedPool();
		size_t GetObjectSize();
		size_t GetObjectCount();
		size_t GetAvailableSlots();

		template<typename T>
		using Ptr = std::unique_ptr<Poolable, PoolReturner>;

		template<typename T>
		Ptr<T> Get()
		{
			static_assert(std::is_base_of<Poolable, T>::value, "You may only pool Poolable objects.");
			if (sizeof(T) > mObjectSize)
				throw(std::out_of_range("Object too large for this Pool."));

			if (mAvailable.empty())
				return nullptr;

			//int index = mAvailableIndices.back();
			//mAvailableIndices.pop_back();
			Ptr<T> obj(new (mAvailable.back()) T, *mReturner);
			mAvailable.pop_back();
			return obj;
		}
	};
}

#endif