#include <pECS\Pool\MemoryManager.h>
#include <pECS\Pool\ObjectPool.h>

namespace pECS
{

	MemoryManager::MemoryManager()
	{
	}


	MemoryManager::~MemoryManager()
	{
	}

	ObjectPool* MemoryManager::CreatePool(size_t objectCount, size_t objectSize)
	{
		ObjectPool* newPool = new ObjectPool(this);
		newPool->Allocate(objectCount, objectSize);
		RegisterPool(newPool);
		return newPool;
	}

	void MemoryManager::RegisterPool(ObjectPool* pool)
	{
		mPools.push_back(pool);
	}

	void MemoryManager::DeregisterPool(ObjectPool* pool)
	{
		auto f = std::find(mPools.begin(), mPools.end(), pool);
		if (f != mPools.end())
		{
			std::swap(mPools.back(), *f);
			mPools.pop_back();
		}
	}

	bool MemoryManager::IsPoolValid(ObjectPool* pool)
	{
		auto f = std::find(mPools.begin(), mPools.end(), pool);
		return (f != mPools.end()) ? true : false;
	}
}