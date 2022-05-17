#pragma once
#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include "Attribute.h"
#include "ChildAttributedFoo.h"
#include "AttributedFoo.h"
namespace GameEngine
{
	class ChildAttributedFoo : public AttributedFoo
	{
		RTTI_DECLARATIONS(ChildAttributedFoo);

	public:
		static const std::size_t ArraySize = 5;
		ChildAttributedFoo();
		ChildAttributedFoo(const ChildAttributedFoo&) = default;
		ChildAttributedFoo(ChildAttributedFoo&&) = default;
		ChildAttributedFoo& operator=(const ChildAttributedFoo&) = default;
		ChildAttributedFoo& operator=(ChildAttributedFoo&&) = default;
		virtual ~ChildAttributedFoo()=default;

		int externalChildInt;
		ChildAttributedFoo* Clone() const override;

		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static  Vector<Signature> Signatures();
	};

}



