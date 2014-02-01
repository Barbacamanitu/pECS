#pragma once
#include <string>
#include <typeindex>
#include <set>
namespace pECS
{

	class ComponentType
	{
	private:
		std::string mName;
		std::type_index* mTypeIndex;
	public:
		ComponentType()
		{
			mTypeIndex = &std::type_index(typeid(this));
			mName = "";
		}

		std::type_index & ComponentType::TypeIndex() const
		{
			return *mTypeIndex;
		}

		template<typename T>
		void SetTypeIndex()
		{
			*mTypeIndex = std::type_index(typeid(T));
		}

		void SetName(std::string name)
		{
			mName = name;
		}

		std::string Name() const
		{
			return mName;
		}
		
		bool ComponentType::operator <(const ComponentType &rhs) const
		{
			return TypeIndex() < rhs.TypeIndex() || (TypeIndex() == rhs.TypeIndex() && Name() < rhs.Name());
		}
	};
	
	template <class T>
	struct my_less
	{
		bool operator()(const T& _Left, const T& _Right) const
		{
			return (_Left < _Right);
		}
	};
	
	class ComponentTypeManager
	{
	private:
		std::set<ComponentType> mTypes;
	public:
		ComponentTypeManager();
		~ComponentTypeManager();
	};
}
