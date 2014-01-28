#include <pECS\Pool\ObjectPool.h>
#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\Poolable.h>



namespace pECS
{

	ObjectPool::ObjectPool(MemoryManager* manager)
	{
		mMemoryManager = manager;
		mReturner = new PoolReturner(manager, this);
	}

	ObjectPool::~ObjectPool()
	{
		Clear();
	}

	void ObjectPool::Allocate(int count, size_t size)
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

	char * ObjectPool::GetOffset(int index)
	{
		return (char *)((intptr_t)mPool) + (mObjectSize * index);
	}

	bool ObjectPool::Return(Poolable * ptr)
	{
		//intptr_t offset = (intptr_t)ptr - (intptr_t)mPool;
		ptr->~Poolable();
		//if (offset < 0 || offset >= mCount)
			//return false;


		mAvailable.push_back(ptr);
		return true;
	}

	size_t ObjectPool::GetObjectSize()
	{
		return mObjectSize;
	}

	size_t ObjectPool::GetObjectCount()
	{
		return mCount;
	}

	size_t ObjectPool::GetAvailableSlots()
	{
		return mAvailable.size();
	}

	void ObjectPool::Clear()
	{
		mAvailable.clear();
		mMemoryManager->DeregisterPool(this);
		free(mPool);
	}
}