#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include "Attribute.h"
#include "Factory.h"
namespace GameEngine
{
	class AttributedFoo : public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo);

	public:
		static const std::size_t ArraySize = 5;
		AttributedFoo();
		AttributedFoo(std::size_t id);
		AttributedFoo(const AttributedFoo&) = default;
		AttributedFoo(AttributedFoo&&) = default;
		AttributedFoo& operator=(const AttributedFoo&) = default;
		AttributedFoo& operator=(AttributedFoo&&) = default;
		virtual ~AttributedFoo();

		int ExternalInteger = 0;
		float ExternalFloat = 0;
		std::string ExternalString;
		glm::vec4 ExternalVector;
		glm::mat4 ExternalMatrix;

		int ExternalIntegerArray[ArraySize];
		float ExternalFloatArray[ArraySize];
		std::string ExternalStringArray[ArraySize];
		glm::vec4 ExternalVectorArray[ArraySize];
		glm::mat4 ExternalMatrixArray[ArraySize];
	
		AttributedFoo* Clone() const override;

		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static Vector<Signature> Signatures();


	};
	ConcreteFactory(AttributedFoo,Scope)
}


