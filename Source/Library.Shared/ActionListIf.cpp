#include "pch.h"
#include "ActionListIf.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(ActionListIf,ActionList)



		ActionListIf::ActionListIf():ActionList(ActionListIf::TypeIdClass())
	{
	}

	Vector<Signature> GameEngine::ActionListIf::Signatures()
	{
		return Vector<Signature>
		{
			{"Condition", DatumTypes::Integer, 1, offsetof(ActionListIf, condition)}
		};
	}

	void ActionListIf::Update(const GameTime& gameTime) { (condition == 0 ? Find("Actions")->Get<Scope*>(0)->As<Action>()->Update(gameTime) : Find("Actions")->Get<Scope*>(1)->As<Action>()->Update(gameTime)); }

	ActionListIf* ActionListIf::Clone() const
	{
		return new ActionListIf(*this);
	}

	bool ActionListIf::Equals(const RTTI* rhs) const
	{
		const ActionListIf* const rhsFoo = rhs->As<ActionListIf>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return name == rhsFoo->name &&
			condition == rhsFoo->condition;
	}

	std::string ActionListIf::ToString() const
	{
		return "ActionListIF";
	}


}