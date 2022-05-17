#include "pch.h"
#include "FooFailClass.h"
#include "pch.h"
#include "FooFailClass.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(FooFailClass, AttributedFoo);

	FooFailClass::FooFailClass() : AttributedFoo(FooFailClass::TypeIdClass())
	{
	}



	FooFailClass* FooFailClass::Clone() const
	{

		return new FooFailClass(*this);
	}

	 Vector<Signature> FooFailClass::Signatures()
	{
		return Vector<Signature>
		{
			{"ExternalInteger", DatumTypes::String, 1, offsetof(FooFailClass, a)},

		};
	}
	bool FooFailClass::Equals(const RTTI* rhs) const
	{
		const auto rhsFoo = rhs->As<FooFailClass>();
		if (rhsFoo == nullptr)
		{
			return false;
		}


		return ExternalInteger == rhsFoo->ExternalInteger;
	}

	std::string FooFailClass::ToString() const
	{
		return "Child Attributed Foo";
	}

}
