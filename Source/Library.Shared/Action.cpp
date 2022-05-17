#include "pch.h"
#include "Action.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(Action, Attributed)

		Action::Action() : Attributed(Action::TypeIdClass())
	{
	}

	const std::string& Action::GetName() const { return name; }
	void Action::SetName(const std::string& actionName) { name = actionName; }
	
	Vector<Signature> Action::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", DatumTypes::String, 1, offsetof(Action, name)}
		};
	}

	Action::Action(std::size_t childID) : Attributed(childID)
	{
	}



}