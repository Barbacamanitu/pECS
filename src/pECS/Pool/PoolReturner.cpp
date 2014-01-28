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
	}
	PoolReturner::PoolReturner(MemoryManager* manager, FixedPool* pool)
	{
		mMemoryManager = manager;
		mFixedPool = pool;
	}
	PoolReturner::~PoolReturner()
	{

	}

	void PoolReturner::operator()(Poolable* poolable)
	{
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