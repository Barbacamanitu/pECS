#include <pECS\Pool\FixedPool.h>
#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\Poolable.h>


namespace pECS
{

	FixedPool::FixedPool(MemoryManager* manager)
	{
		mMemoryManager = manager;
		mReturner = new PoolReturner(manager, this);
		mDefaultDeleter = new PoolReturner(manager, this);
		mDefaultDeleter->SetDefaultDeleter();

		
	}

	FixedPool::~FixedPool()
	{
		Clear();
	}

	void FixedPool::Allocate(size_t count, size_t size)
	{
		mObjectSize = size;
		mCount = count;
		mPool = malloc(count * size);
		mAvailable.reserve(count);
		for (int i = 0; i < count; i++)
		{
			mAvailable.push_back(GetOffset(i));
		}
	}

	char * FixedPool::GetOffset(int index)
	{
		return (char *)((intptr_t)mPool) + (mObjectSize * index);
	}

	bool FixedPool::Return(Poolable * ptr)
	{
		intptr_t offset = (intptr_t)ptr - (intptr_t)mPool;
		ptr->~Poolable();
		if (offset < 0 || offset >= mCount)
			return false;


		mAvailable.push_back(ptr);
		return true;
	}


	size_t FixedPool::GetObjectSize()
	{
		return mObjectSize;
	}

	size_t FixedPool::GetObjectCount()
	{
		return mCount;
	}

	size_t FixedPool::GetAvailableSlots()
	{
		return mAvailable.size();
	}

	void FixedPool::Clear()
	{
		mAvailable.clear();
		mMemoryManager->DeregisterPool(this);
		free(mPool);
	}
}