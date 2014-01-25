#ifndef PECSUID_H
#define PECSUID_H

namespace pECS
{
	class UID
	{
	public:
		static unsigned int Generate(void * ptr)
		{
			int rSeed = rand() % 1000 * 1000;
			size_t t = (size_t) ptr;
			int i = t + rSeed;
			return abs(i);

		}
	};
}

#endif