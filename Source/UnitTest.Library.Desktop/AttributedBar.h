#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include "Attribute.h"
#include "AttributedFoo.h"
namespace GameEngine
{
	class AttributedBar : public AttributedFoo
	{
		RTTI_DECLARATIONS(AttributedBar);

	public:
		static const std::size_t ArraySize = 5;
		AttributedBar();
		AttributedBar(const AttributedBar&) = default;
		AttributedBar(AttributedBar&&) = default;
		AttributedBar& operator=(const AttributedBar&) = default;
		AttributedBar& operator=(AttributedBar&&) = default;
		virtual ~AttributedBar();

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
		
		AttributedBar* Clone() const override;

		bool Equals(const RTTI* rhs) const ;
		std::string ToString() const override;

		static  Vector<Signature> Signatures();
	};

}


#pragma once
