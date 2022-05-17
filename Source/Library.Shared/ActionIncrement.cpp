#include "pch.h"
#include "ActionIncrement.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(ActionIncrement, Action)
		ActionIncrement::ActionIncrement() :Action(ActionIncrement::TypeIdClass())
	{
	}
	void GameEngine::ActionIncrement::Update(const GameTime&)
	{
		if (!_targetFound)
		{
			_parent = Search(target);
			if (_parent == nullptr) { throw std::runtime_error("No such value to increment"); }
			_targetFound = true;
			assert(_parent->Type() == DatumTypes::Integer || _parent->Type() == DatumTypes::Float);
			(_parent->Type() == DatumTypes::Integer ? _type = 0 : _type = 1);
		}
		if (_type == 0) { _parent->Set(std::int32_t(_parent->Get<std::int32_t>() + step)); }
		else { _parent->Set(_parent->Get<float>() + step); }
	}

	Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector<Signature>
		{
			{"Target", DatumTypes::String, 1, offsetof(ActionIncrement, target)},
			{ "Step",DatumTypes::Float,1,offsetof(ActionIncrement,step) }
		};
	}

	ActionIncrement* ActionIncrement::Clone() const
	{
		return new ActionIncrement(*this);
	}

	bool ActionIncrement::Equals(const RTTI* rhs) const
	{

		const ActionIncrement* const rhsFoo = rhs->As<ActionIncrement>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return name == rhsFoo->name &&
			target == rhsFoo->target &&
			step == rhsFoo->step;
	}

	std::string ActionIncrement::ToString() const
	{
		return "ActionIncrement";
	}

}
