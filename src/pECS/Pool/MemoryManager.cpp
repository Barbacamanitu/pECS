#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\FixedPool.h>

namespace pECS
{

	MemoryManager::MemoryManager()
	{
	}


	MemoryManager::~MemoryManager()
	{
	}

	FixedPool* MemoryManager::CreatePool(size_t objectCount, size_t objectSize)
	{
		FixedPool* newPool = new FixedPool(this);
		newPool->Allocate(objectCount, objectSize);
		RegisterPool(newPool);
		return newPool;
	}

	void MemoryManager::RegisterPool(FixedPool* pool)
	{
		mPools.push_back(pool);
	}

	void MemoryManager::DeregisterPool(FixedPool* pool)
	{
		auto f = std::find(mPools.begin(), mPools.end(), pool);
		if (f != mPools.end())
		{
			std::swap(mPools.back(), *f);
			mPools.pop_back();
		}
	}

	bool MemoryManager::IsPoolValid(FixedPool* pool)
	{
		auto f = std::find(mPools.begin(), mPools.end(), pool);
		return (f != mPools.end()) ? true : false;
	}
}