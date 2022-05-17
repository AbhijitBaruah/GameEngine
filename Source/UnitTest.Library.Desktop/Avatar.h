#pragma once
#include "GameObject.h"
namespace GameEngine
{
	class Avatar : public GameObject
	{
		RTTI_DECLARATIONS(Avatar);
	public:
		Avatar();
		virtual ~Avatar();
		static Vector<Signature> Signatures();
		 void Update(const GameTime&) override;
		std::int32_t health;

		Avatar* Clone() const override;

		bool Equals(const RTTI* rhs) const override;
	protected:
		Avatar(std::size_t childID);
	};

	
	ConcreteFactory(Avatar, Scope)
}