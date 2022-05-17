#include "pch.h"
#include "AttributedFoo.h"
#include "ChildAttributedFoo.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(ChildAttributedFoo, AttributedFoo);
	
	ChildAttributedFoo::ChildAttributedFoo() : AttributedFoo(ChildAttributedFoo::TypeIdClass())
	{
	}
	


	ChildAttributedFoo* ChildAttributedFoo::Clone() const
	{
		return new ChildAttributedFoo(*this);
	}

	 Vector<Signature> ChildAttributedFoo::Signatures()
	{
		return Vector<Signature>
		{
			{"externalChildInt", DatumTypes::Integer, 1, offsetof(ChildAttributedFoo, externalChildInt)},
			
		};
	}
	bool ChildAttributedFoo::Equals(const RTTI* rhs) const
	{

		const auto rhsFoo = rhs->As<ChildAttributedFoo>();
		if (rhsFoo == nullptr)
		{
			return false;
		}
		return(AttributedFoo::Equals(rhs) && externalChildInt == rhsFoo->externalChildInt);
		
	}

	std::string ChildAttributedFoo::ToString() const
	{
		return "Child Attributed Foo";
	}

}
