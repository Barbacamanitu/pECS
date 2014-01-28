#ifndef POOLRETURNER_H
#define POOLRETURNER_H

#include <memory>



namespace pECS
{
class MemoryManager;
class Poolable;
class ObjectPool;	

class PoolReturner
	{

	private:
		MemoryManager* mMemoryManager;
		ObjectPool* mObjectPool;
	public:
		PoolReturner();
		PoolReturner(MemoryManager* manager, ObjectPool* pool);
		~PoolReturner();

		void operator()(Poolable* poolable);

	};

}

#endif