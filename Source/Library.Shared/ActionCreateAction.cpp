#include "pch.h"
#include "ActionCreateAction.h"
#include "ActionList.h"
namespace GameEngine
{

	RTTI_DEFINITIONS(ActionCreateAction, Action)



		ActionCreateAction::ActionCreateAction() : Action(ActionCreateAction::TypeIdClass())
	{

	}



	void ActionCreateAction::Update(const GameTime&)
	{
		if (!_parentFound)
		{
			while (_parentScope != nullptr)
			{
				Datum& parentDatum = *_parentScope->Search("Actions");

				for (std::size_t i = 0; i < parentDatum.Size(); ++i)
				{
					if (parentDatum.Get<Scope*>()->Find("Name")->Get<std::string>().c_str() == parentInstanceName)
					{
						_parentFound = true;
					}
				}
				if (_parentFound) { break; }
				else
				{
					_parentScope = _parentScope->GetParent();
				}
			}
		}
		assert(_parentFound != false);
		Scope* actionCreated = Factory<Scope>::Create(actionClassName);
		assert(actionCreated != nullptr);
		assert(actionCreated->As<Action>() != nullptr);
		static_cast<Action*>(actionCreated)->SetName(actionInstanceName);
		_pendingListToAdd.PushBack(std::make_pair(_parentScope, actionCreated));

	}

	Vector<Signature> ActionCreateAction::Signatures()
	{
		return Vector<Signature>
		{

			{"ClassName", DatumTypes::String, 1, offsetof(ActionCreateAction, actionClassName)},
			{ "InstanceName",DatumTypes::String,1,offsetof(ActionCreateAction,actionInstanceName) },
			{"ParentName",DatumTypes::String,1,offsetof(ActionCreateAction,parentInstanceName)}
		};
	}

	ActionCreateAction* ActionCreateAction::Clone() const
	{
		return new ActionCreateAction(*this);

	}

	bool ActionCreateAction::Equals(const RTTI* rhs) const
	{
		const ActionCreateAction* const rhsFoo = rhs->As<ActionCreateAction>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return name == rhsFoo->name &&
			parentInstanceName == rhsFoo->parentInstanceName &&
			actionInstanceName == rhsFoo->actionInstanceName &&
			actionClassName == rhsFoo->actionClassName;
	}

	std::string ActionCreateAction::ToString() const
	{
		return "ActionCreateAction";
	}

	

}