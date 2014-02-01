#include <pECS\Entity.h>
#include <string>
namespace pECS
{

	Entity::Entity(void)
	{
		mParent = nullptr;
		mUID = UID::Generate(this);
	}
	Entity::~Entity()
	{
	}


	void Entity::SetParent(Entity* parent)
	{
		mParent = parent;
	}

	Entity* Entity::GetParent()
	{
		return mParent;
	}


	bool Entity::AddComponent(std::unique_ptr<Component>& component)
	{
		std::string cName = component->GetName();
		if (HasComponent(cName))
			return false;
		mComponents.insert(std::make_pair(cName, std::move(component)));
		mTypes.insert(cName);
		return true;
	}

	bool Entity::RemoveComponent(std::string componentName)
	{

		auto it = mComponents.find(componentName);
		if (it == mComponents.end())
			return false;
		mComponents.erase(it);

		auto itt = std::find(mTypes.begin(), mTypes.end(), componentName);
		if (itt != mTypes.end())
		{
			mTypes.erase(itt);
		}
		


		return true;
	}

	bool Entity::HasComponent(std::string componentName)
	{
		auto it = mComponents.find(componentName);
		if (it == mComponents.end())
			return false;
		return true;
	}

	Component::Ptr const & Entity::GetComponent(std::string componentName)
	{
		auto it = mComponents.find(componentName);
		if (it == mComponents.end())
			return nullptr;
		return it->second;
	}

	std::set<std::string> const & Entity::GetComponentTypes()
	{
		return mTypes;
	}



	void Entity::Dump(int level)
	{
		//Entity information
			std::string spaces = "";
			for (int i = 0; i < level; i++)
			{
				spaces.append("  ");
			}
		std::cout<<spaces<<"<>Entity Information<>\n";
		std::cout<<spaces<<"---------------------------\n";
		std::cout<<spaces<<"Address: "<<this<<"\n";
		std::cout<<"\n";
		std::cout<<spaces<<"Components: "<<mComponents.size()<<"\n";
		int count = 0;
		for (auto it = mComponents.begin(); it != mComponents.end(); it++)
		{
			count++;
			std::cout<<spaces<<count<<") Type:["<<it->first<<"]\n";
		}

		std::cout<<spaces<<"Children: "<<mChildren.size()<<"\n";
		count = 0;
		for (auto it = mChildren.begin(); it != mChildren.end(); it++)
		{
		
			count++;
			(*it)->Dump(level + 1);
		}
		std::cout<<spaces<<"---------------------------\n\n\n";

	}

	
	

	void Entity::AddChild(Entity::Ptr& child)
	{
		if (this == child.get())
			return;
		child->SetParent(mParent);
		mChildren.push_back(std::move(child));
	}
	
	Entity::Ptr Entity::RemoveChild(Entity::Ptr& ent)
	{
		auto it = std::find(mChildren.begin(),mChildren.end(),ent);
		if (it == mChildren.end())
			return nullptr;
		Entity::Ptr p = std::move(*it);
		std::swap(*it,mChildren.back());
		mChildren.pop_back();
		return p;
	}
	Entity::Ptr Entity::RemoveChild(int index)
	{
		index = abs(index);
		if (index >= mChildren.size() || mChildren.empty())
			return nullptr;
		return RemoveChild(mChildren[index]);
	}

	std::vector<Entity::Ptr> & Entity::GetChildren()
	{
		return mChildren;
	}
}