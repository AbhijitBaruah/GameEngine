#include "pch.h"
#include "AttributedBar.h"
#include "AttributedFoo.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(AttributedBar, AttributedFoo);
	AttributedBar::AttributedBar() : AttributedFoo(AttributedBar::TypeIdClass())
	{
	}
	AttributedBar::~AttributedBar()
	{
	}


	AttributedBar* AttributedBar::Clone() const
	{
		return new AttributedBar(*this);
	}

	 Vector<Signature> AttributedBar::Signatures()
	{
		return Vector<Signature>
		{
			{"ExternalInteger", DatumTypes::Integer, 1, offsetof(AttributedBar, ExternalInteger)},
			{ "ExternalFloat",DatumTypes::Float,1,offsetof(AttributedBar,ExternalFloat) },
			{ "ExternalVector",DatumTypes::Vector,1,offsetof(AttributedBar,ExternalVector) },
			{ "ExternalMatrix",DatumTypes::Matrix,1,offsetof(AttributedBar,ExternalMatrix) },
			{ "ExternalString",DatumTypes::String,1,offsetof(AttributedBar,ExternalString) },
			{ "ExternalIntegerArray",DatumTypes::Integer,ArraySize,offsetof(AttributedBar,ExternalIntegerArray) },
			{ "ExternalFloatArray",DatumTypes::Float,ArraySize,offsetof(AttributedBar,ExternalFloatArray) },
			{ "ExternalMatrixArray",DatumTypes::Matrix,ArraySize,offsetof(AttributedBar,ExternalMatrixArray) },
			{ "ExternalVectorArray",DatumTypes::Vector,ArraySize,offsetof(AttributedBar,ExternalVectorArray) },
			{ "ExternalStringArray",DatumTypes::String,ArraySize,offsetof(AttributedBar,ExternalStringArray) }
		};
	}
	

	bool AttributedBar::Equals(const RTTI* rhs) const
	{
		const AttributedFoo* const rhsFoo = rhs->As<AttributedFoo>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return ExternalInteger == rhsFoo->ExternalInteger &&
			ExternalFloat == rhsFoo->ExternalFloat &&
			ExternalString == rhsFoo->ExternalString &&
			ExternalVector == rhsFoo->ExternalVector &&
			ExternalMatrix == rhsFoo->ExternalMatrix &&
			std::equal(std::begin(ExternalIntegerArray), std::end(ExternalIntegerArray), std::begin(rhsFoo->ExternalIntegerArray)) &&
			std::equal(std::begin(ExternalFloatArray), std::end(ExternalFloatArray), std::begin(rhsFoo->ExternalFloatArray)) &&
			std::equal(std::begin(ExternalMatrixArray), std::end(ExternalMatrixArray), std::begin(rhsFoo->ExternalMatrixArray)) &&
			std::equal(std::begin(ExternalVectorArray), std::end(ExternalVectorArray), std::begin(rhsFoo->ExternalVectorArray)) &&
			std::equal(std::begin(ExternalStringArray), std::end(ExternalStringArray), std::begin(rhsFoo->ExternalStringArray));

	}

	std::string AttributedBar::ToString() const
	{
		return "Attributed Bar";
	}

}