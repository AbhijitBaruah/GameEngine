#include "pch.h"
#include "ActionRemoveAction.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(ActionRemoveAction, Action)


		ActionRemoveAction::ActionRemoveAction(): Action(ActionRemoveAction::TypeIdClass())
	{
	}

	void ActionRemoveAction::Update(const GameTime&)
	{
		Datum& actionsDatum = *Search("Actions");
		for (std::size_t i = 0; i < actionsDatum.Size(); ++i)
		{
			if (actionsDatum.Get<Scope*>(i)->As<Action>()->GetName() == nameToDelete)
			{
				_pendingListToRemove.PushBack(std::make_pair(&actionsDatum, i));
				return;
			}
		}

	}

	Vector<Signature> ActionRemoveAction::Signatures()
	{
		return Vector<Signature>
		{
			{"ActionToDelte", DatumTypes::String, 1, offsetof(ActionRemoveAction, nameToDelete)}
		};
	}

	ActionRemoveAction* ActionRemoveAction::Clone() const
	{
		return new ActionRemoveAction(*this);
	}

	bool ActionRemoveAction::Equals(const RTTI* rhs) const
	{
		const ActionRemoveAction* const rhsFoo = rhs->As<ActionRemoveAction>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return name == rhsFoo->name &&
			nameToDelete == rhsFoo->nameToDelete;
	}

	std::string ActionRemoveAction::ToString() const
	{
		return "ActionRemoveAction";
	}


}