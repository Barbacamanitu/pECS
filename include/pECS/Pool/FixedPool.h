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

		MemoryManager * mMemoryManager;
		PoolReturner* mReturner;
		PoolReturner* mDefaultDeleter;

		
		void Clear();
		void Allocate(size_t count, size_t size);
		char * GetOffset(int index);
		bool Return(Poolable * ptr);


	

	public:
		~FixedPool();
		size_t GetObjectSize();
		size_t GetObjectCount();
		size_t GetAvailableSlots();

		template<typename T>
		using Ptr = std::unique_ptr<T, PoolReturner>;

		
		template<typename T>
		Ptr<T> Get()
		{


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

		template<typename T>
		Ptr<T> ForceGet()
		{
			Ptr<T> tObj = Get<T>();
			if (tObj == nullptr)
			{
				return Ptr<T>(new T, *mDefaultDeleter);
			}
			else
				return tObj;
		}

	};
}

#endif