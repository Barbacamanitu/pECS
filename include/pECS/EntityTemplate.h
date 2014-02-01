#ifndef ENTITYTEMPLATE_H
#define ENTITYTEMPLATE_H

#include <string>
#include <vector>
#include <typeindex>

class EntityTemplate
{
private:
	std::string mName;
	std::vector<std::type_index> mComponentTypes;
public:
	EntityTemplate();
	~EntityTemplate();
	void SetName(std::string name);
	std::string GetName();

	template<class T>
	void AddComponentType()
	{
		mComponentTypes.insert(std::type_index(typeid(T)));
	}
};

#endif

