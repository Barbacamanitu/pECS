#ifndef PECS_IPOOLABLE_H
#define PECS_IPOOLABLE_H
namespace pECS
{
	class Pool;
/**
Poolable Interface. All poolable objects must derive from IPoolable.
*/
class IPoolable
{
public:
	IPoolable(void):
		mPool(nullptr),
		mOverflow(false){};
	~IPoolable(void){};

	/**
	*	Sets object's Pool.
	*	The pool automatically sets this so that the Poolable may return itself when necessary.
	*/
	void SetPool(Pool* pool);
	Pool* GetPool() const;

	void SetOverflow();
	bool IsFromOverflow();
	void operator delete(void* obj);

private:

	/**
	Pointer to the Pool this object belongs to. 
	Necessary so the object may return itself to its Pool when it is destroyed.
	*/
	Pool* mPool;
	bool mOverflow;
};
}

#endif