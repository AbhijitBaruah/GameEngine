#include "pch.h"
#include "AttributedFoo.h"
#include <string.h>
using namespace std::literals::string_literals;
namespace GameEngine
{
	RTTI_DEFINITIONS(AttributedFoo, Attributed);
	AttributedFoo::AttributedFoo() : Attributed(AttributedFoo::TypeIdClass())
	{
	}
	AttributedFoo::~AttributedFoo()
	{
	}
	AttributedFoo::AttributedFoo(std::size_t id) : Attributed(id)
	{
	}

	AttributedFoo* AttributedFoo::Clone() const
	{
		return new AttributedFoo(*this);
	}

	Vector<Signature> AttributedFoo::Signatures()
	{
		return Vector<Signature>
		{
			{"ExternalInteger", DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger)},
			{ "ExternalFloat",DatumTypes::Float,1,offsetof(AttributedFoo,ExternalFloat) },
			{ "ExternalVector",DatumTypes::Vector,1,offsetof(AttributedFoo,ExternalVector) },
			{ "ExternalMatrix",DatumTypes::Matrix,1,offsetof(AttributedFoo,ExternalMatrix) },
			{ "ExternalString",DatumTypes::String,1,offsetof(AttributedFoo,ExternalString) },
			{ "ExternalIntegerArray",DatumTypes::Integer,ArraySize,offsetof(AttributedFoo,ExternalIntegerArray) },
			{ "ExternalFloatArray",DatumTypes::Float,ArraySize,offsetof(AttributedFoo,ExternalFloatArray) },
			{ "ExternalMatrixArray",DatumTypes::Matrix,ArraySize,offsetof(AttributedFoo,ExternalMatrixArray) },
			{ "ExternalVectorArray",DatumTypes::Vector,ArraySize,offsetof(AttributedFoo,ExternalVectorArray) },
			{ "ExternalStringArray",DatumTypes::String,ArraySize,offsetof(AttributedFoo,ExternalStringArray) }
		};
	}
	bool AttributedFoo::Equals(const RTTI* rhs) const
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


	std::string AttributedFoo::ToString() const
	{
		return "Attributed Foo";
	}

}