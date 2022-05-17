#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include "Attribute.h"
#include "FooFailClass.h"
#include "AttributedFoo.h"
namespace GameEngine
{
	class FooFailClass: public AttributedFoo
	{
		RTTI_DECLARATIONS(FooFailClass);

	public:
		static const std::size_t ArraySize = 5;
		FooFailClass();
		FooFailClass(const FooFailClass&) = default;
		FooFailClass(FooFailClass&&) = default;
		FooFailClass& operator=(const FooFailClass&) = default;
		FooFailClass& operator=(FooFailClass&&) = default;
		virtual ~FooFailClass() = default;

		int a;
		FooFailClass* Clone() const override;

		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static  Vector<Signature> Signatures();
	};

}



