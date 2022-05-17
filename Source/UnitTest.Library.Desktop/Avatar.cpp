#include "pch.h"
#include "Avatar.h"


namespace GameEngine
{

	RTTI_DEFINITIONS(Avatar,GameObject)

		Avatar::Avatar() :GameObject(Avatar::TypeIdClass())
	{
	}

	Avatar::~Avatar()
	{
	}

	Vector<Signature> Avatar::Signatures()
	{
		return Vector<Signature>
		{
			{"Health", DatumTypes::Integer, 1, offsetof(Avatar, health)}
		};
	}

	void Avatar::Update(const GameTime& gameTime)
	{
		GameObject::Update(gameTime);
		--health;
		
	}

	Avatar* Avatar::Clone() const
	{
		return new Avatar(*this);
	}

	bool Avatar::Equals(const RTTI* rhs) const
	{

		const Avatar* const rhsFoo = rhs->As<Avatar>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return health == rhsFoo->health &&
			GameObject::Equals(rhs);
	}

	Avatar::Avatar(std::size_t childID) : GameObject(childID)
	{
	}

}