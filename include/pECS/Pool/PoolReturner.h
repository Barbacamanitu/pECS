#ifndef POOLRETURNER_H
#define POOLRETURNER_H

#include <memory>



namespace pECS
{
class MemoryManager;
class Poolable;
class FixedPool;	

class PoolReturner
	{

	private:
		MemoryManager* mMemoryManager;
		FixedPool* mFixedPool;
	public:
		PoolReturner();
		PoolReturner(MemoryManager* manager, FixedPool* pool);
		~PoolReturner();

		void operator()(Poolable* poolable);

	};

}

#endif