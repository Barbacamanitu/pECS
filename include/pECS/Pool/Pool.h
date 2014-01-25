#ifndef PECS_Pool_H
#define PECS_Pool_H
#include "IPoolable.h"
#include <memory>
#include <vector>
namespace pECS
{
	class Pool
	{
	
	private:
			
		/**
		*	Main object pool.
		*/
		void * mPool;
		std::vector<void *> mOverflow;
		int mMaxOverflow;
		size_t mObjectSize;
		std::vector<char *> mAvailable;
		std::string lastInstruction;
	public:	
		Pool();

		~Pool(void)
		{
			Clear();
		};


		void SetMaximumOverflow(int maxOverflow);
		void Allocate(int objectCount,size_t size);

		char * GetOffset(int index);


		template<class T>
		std::unique_ptr<T> Create()
		{
			if (sizeof(T) > mObjectSize)
				return nullptr;
			

			T* nObj;
			if (mAvailable.empty())
			{
				if (mOverflow.size() >= mMaxOverflow)
					return nullptr;
				else
					mOverflow.push_back(new char[mObjectSize]);
					nObj = new(mOverflow.back()) T;
					nObj->SetOverflow();
			}
			else
			{
				nObj = new(mAvailable.back()) T;
				mAvailable.pop_back();
			}
		


			nObj->SetPool(this);
			std::unique_ptr<T> t(nObj);
			return t;
		}

	
		void Return(IPoolable* obj);

		void ReturnOverflow(IPoolable* obj);

	private:
		void Clear();
	};
}

#endif