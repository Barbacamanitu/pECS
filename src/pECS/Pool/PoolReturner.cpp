#include <pECS\Pool\PoolReturner.h>
#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\FixedPool.h>
#include <iostream>

namespace pECS
{

	PoolReturner::PoolReturner()
	{
		mMemoryManager = nullptr;
		mFixedPool = nullptr;
		mDefault = false;
	}
	PoolReturner::PoolReturner(MemoryManager* manager, FixedPool* pool)
	{
		mMemoryManager = manager;
		mFixedPool = pool;
		mDefault = false;
	}
	PoolReturner::~PoolReturner()
	{

	}

	void PoolReturner::SetDefaultDeleter()
	{
		mDefault = true;
	}

	void PoolReturner::operator()(Poolable* poolable)
	{
		if (mDefault)
		{
			delete poolable;
			return;
		}
		//Check if Pool is still valid.
		if (mMemoryManager->IsPoolValid(mFixedPool))
		{
			//Pool is valid, remove Poolable Object
				mFixedPool->Return(poolable);

		}
		else
		{
			//Pool has been deleted. 

		}
	}
}