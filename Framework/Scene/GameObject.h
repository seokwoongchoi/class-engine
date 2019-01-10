#pragma once
#include "./Component/IComponent.h"
class GameObject
{
public:
	GameObject(class Context* context);
	virtual ~GameObject();

	void Initialize(class Transform* transform);

	void Start();
	void Update();
	void Stop();

	class Transform* GetTransform()const { return transform; }
	const string& GetName()const { return name; }
	const bool& IsActive()const { return bActive; }

	void SetName(const string& name) { this->name = name; }
	void SetIsActive(const bool& bActive) { this->bActive = bActive; }

	class IComponent* AddComponent(const ComponentType& type);
	template<typename T>T* AddComponent();
	template<typename T>T* GetComponent();
	template<typename T>vector<T*> GetComponents(); //나머지는 하나씩이지만 script는 여러개라서 여러개빼오는거 만들어준다.
	
	const bool HasComponent(const ComponentType& type);
	//{
	//	return components.find(type) != components.end();//이터레이터의 위치가 end면 없다는뜻

	//}
	template<typename T>
	const bool HasComponent()
	{
		return HasComponent(IComponent::DeduceComponentType<T>());
	}
	template<typename T>
	void RemoveComponent();

	

private:
	class Context* context;
	class Transform* transform;
	string name;
	bool bActive;

	vector<class IComponent*> components; //script만 여러개 중복되서멀티맵으로 만든다.
};

template<typename T>
inline T * GameObject::AddComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();
	if (HasComponent(type)&& type != ComponentType::Script)//존재한다면
		return GetComponent<T>();

	components.emplace_back(new T(context, this, transform));//부모의 트렌스폼

	auto newComponent = static_cast<T*>(components.back());
	newComponent->SetComponentType(type);
	newComponent->OnInitialize();

	//components.insert(make_pair(type,newComponent));//없으면 새로 만들어서 내꺼에 푸쉬백해서 다시 내보낸다

	return newComponent;
}

template<typename T>
inline T * GameObject::GetComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();
	//if (components.find(type) == components.end())//못찾았다면
	//	return nullptr;

	for (auto component : components)
	{
		if (component->GetComponentType() == type)
		{
			return static_cast<T*>(component);
		}
	}
	
	//return static_cast<T*>(components.find(type)->second);//찾았다면
	return nullptr;//위에서 못찾았다면 null반환
}

template<typename T>
inline vector<T*> GameObject::GetComponents()
{
	ComponentType type = IComponent::DeduceComponentType<T>();
	vector<T*>tempComponents;

	for (auto component : components)
	{
		if (component->GetComponentType() != type)
			continue;
		tempComponents.emplace_back(static_cast<T*>(component));
	}
	return tempComponents;
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	ComponentType type = IComponent::DeduceComponentType<T>();
	
	for (auto iter = components.begin(); iter != components.end();)
	{
		auto component = *iter;
		if (type == component.second->GetComponentTypeType())
		{
			component->OnDestroy();
			SAFE_DELETE(component.second); //second->밸류값
			iter = componets.erase(iter);
		else
			iter++;
		}
	}
}
