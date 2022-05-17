#include "pch.h"
#include "GameObject.h"
#include "Action.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(GameObject, Attributed)
		GameObject::GameObject() :Attributed(GameObject::TypeIdClass())
	{
	}
#pragma region GameObject
	GameObject::~GameObject()
	{
	}

	void GameObject::Update(const GameTime& gameTime)
	{
		Datum* children = Find("Children");
		if (children != nullptr)
		{
			for (std::size_t i = 0; i < children->Size(); ++i)
			{
				assert(children->Get<Scope*>(i)->As<GameObject>() != nullptr);
				static_cast<GameObject*> (children->Get<Scope*>(i))->Update(gameTime);
			}
		}

		Datum* actionDatum = Find("Actions");
		if (actionDatum != nullptr)
		{
			for (std::size_t i = 0; i < actionDatum->Size(); ++i)
			{
				assert(actionDatum->Get<Scope*>(i)->As<Action>() != nullptr);
				static_cast<Action*> (actionDatum->Get<Scope*>(i))->Update(gameTime);
			}

		}

	}

	Vector<Signature> GameObject::Signatures()
	{
		return Vector<Signature>
		{
			{"Position", DatumTypes::Vector, 1, offsetof(GameObject, transform.position)},
			{ "Rotation",DatumTypes::Vector,1,offsetof(GameObject,transform.rotation) },
			{ "Scale",DatumTypes::Vector,1,offsetof(GameObject,transform.scale) },
			{ "Name", DatumTypes::String, 1, offsetof(GameObject, Name) },
			{ "Children",DatumTypes::Table,0,0 },
			{ "Actions",DatumTypes::Table,0,0 }
		};
	}
#pragma endregion

#pragma region Action
	const Datum& GameObject::Actions() const { return *(Find("Actions")); }
	Scope* GameObject::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Scope* actionCreated = Factory<Scope>::Create(className);
		assert(actionCreated != nullptr);
		assert(actionCreated->As<Action>() != nullptr);
		static_cast<Action*>(actionCreated)->SetName(instanceName);
		Adopt(*actionCreated, "Actions");
		return actionCreated;
	}
	Datum& GameObject::Actions() { return *(Find("Actions")); }

#pragma endregion

#pragma region RTTI
	GameObject* GameObject::Clone() const
	{
		return new GameObject(*this);
	}

	GameObject::GameObject(std::size_t childID) : Attributed(childID)
	{
	}
	bool GameObject::Equals(const RTTI* rhs) const
	{
		const GameObject* const rhsFoo = rhs->As<GameObject>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return Name == rhsFoo->Name &&
			transform.position == rhsFoo->transform.position &&
			transform.rotation == rhsFoo->transform.rotation &&
			transform.scale == rhsFoo->transform.scale &&
			(*this).At("Children") == (*rhsFoo).At("Children");
	}
	std::string GameObject::ToString() const
	{
		return "GameObject";
	}
#pragma endregion
}