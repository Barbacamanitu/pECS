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
		bool mDefault;
	public:
		PoolReturner();
		PoolReturner(MemoryManager* manager, FixedPool* pool);
		~PoolReturner();
		void SetDefaultDeleter();
		void operator()(Poolable* poolable);

	};

}

#endif