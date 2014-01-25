#include <pECS\Pool\IPoolable.h>
#include <pECS\Pool\Pool.h>
namespace pECS
{
	void IPoolable::SetPool(Pool* oPool)
	{
		mPool = oPool;
	}

	void IPoolable::SetOverflow()
	{
		mOverflow = true;
	}

	bool IPoolable::IsFromOverflow()
	{
		return mOverflow;
	}

	Pool* IPoolable::GetPool() const
	{
		return mPool;
	}

	void IPoolable::operator delete(void * obj)
	{
		if (IPoolable* ip = static_cast<IPoolable*>(obj))
			if (ip->GetPool() != nullptr)
			{
				ip->GetPool()->Return(ip);
				return;
			}
		::delete obj;
	}
}