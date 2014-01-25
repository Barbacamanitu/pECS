#include <pECS\Pool\Pool.h>

namespace pECS
{
	Pool::Pool()
		{
			mPool = nullptr;
			mMaxOverflow = -1;
		};

	void Pool::Allocate(int objectCount,size_t size)
	{
		mObjectSize = size;
		mPool = malloc(size * objectCount);
		for (int i = 0; i < objectCount; i++)
		{
			mAvailable.push_back(GetOffset(i));
		}
	}

	void Pool::SetMaximumOverflow(int maxOverflow)
	{
		mMaxOverflow = maxOverflow;
	}

	char * Pool::GetOffset(int index)
	{
		return (char *)((unsigned int)mPool) + (mObjectSize * index);
	}	

	void Pool::Return(IPoolable* obj)
	{
		if (obj->IsFromOverflow())
			ReturnOverflow(obj);
		else
		mAvailable.push_back((char*)obj);		
	}

	void Pool::ReturnOverflow(IPoolable* obj)
		{
			auto it = std::find(mOverflow.begin(),mOverflow.end(),obj);
			if (*it)
			{
				std::swap(*it,mOverflow.back());
				mOverflow.pop_back();
			}
		}

	void Pool::Clear()
	{
		delete[] mPool;
		while (!mOverflow.empty())
		{
			delete mOverflow.back();
			mOverflow.pop_back();
		}
	}
}