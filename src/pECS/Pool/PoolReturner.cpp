#include <pECS\Pool\PoolReturner.h>
#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\ObjectPool.h>
#include <iostream>

namespace pECS
{

	PoolReturner::PoolReturner()
	{
		mMemoryManager = nullptr;
		mObjectPool = nullptr;
	}
	PoolReturner::PoolReturner(MemoryManager* manager, ObjectPool* pool)
	{
		mMemoryManager = manager;
		mObjectPool = pool;
	}
	PoolReturner::~PoolReturner()
	{

	}

	void PoolReturner::operator()(Poolable* poolable)
	{
		//Check if Pool is still valid.
		if (mMemoryManager->IsPoolValid(mObjectPool))
		{
			//Pool is valid, remove Poolable Object
			mObjectPool->Return(poolable);

		}
		else
		{
			//Pool has been deleted. 

		}
	}
}