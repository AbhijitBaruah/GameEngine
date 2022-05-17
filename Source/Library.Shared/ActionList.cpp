#include "pch.h"
#include "ActionList.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(ActionList, Action)

		ActionList::ActionList() : Action(ActionList::TypeIdClass())
	{
	}

	Datum& ActionList::Actions() { return *(Find("Actions")); }
	bool ActionList::Equals(const RTTI* rhs) const
	{

		const ActionList* const rhsFoo = rhs->As<ActionList>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return name == rhsFoo->name;
	}
	std::string ActionList::ToString() const
	{
		return "ActionList";
	}
	ActionList::ActionList(std::size_t childID) : Action(childID)
	{

	}
	void ActionList::Update(const GameTime& gameTime)
	{
		Datum* actionChildren = Find("Actions");
		if (actionChildren != nullptr)
		{
			for (std::size_t i = 0; i < actionChildren->Size(); ++i)
			{
				assert(actionChildren->Get<Scope*>(i)->As<Action>() != nullptr);
				static_cast<Action*> (actionChildren->Get<Scope*>(i))->Update(gameTime);
			}
		}
	}
	Scope* ActionList::CreateAction(std::string& className, std::string& instanceName)
	{
		Scope* actionCreated = Factory<Scope>::Create(className);
		assert(actionCreated != nullptr);
		assert(actionCreated->As<Action>() != nullptr);
		static_cast<Action*>(actionCreated)->SetName(instanceName);
		Adopt(*actionCreated, "Actions");
		return actionCreated;
	}
	Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
		{
			{"Actions", DatumTypes::Table, 0, 0}
		};
	}

	ActionList* ActionList::Clone() const
	{
		return new ActionList(*this);
	}

	

	
}