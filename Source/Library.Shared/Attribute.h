#pragma once
#include "Scope.h"
#include "TypeRegistry.h"

namespace GameEngine
{
	/// <summary>
	/// Public abstract class attributed that inherits from scope
	/// </summary>
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed);
	public:
		/// <summary>
		/// A method that queries the type register and populates the hashmap and orderd vector of scope by inserting all the prescribed attributes of the given class
		/// </summary>
		/// <param name="key">The Type ID of the class</param>
		void Populate(std::size_t key);
		/// <summary>
		/// General function that fixes external pointers in case of move or copy.
		/// </summary>
		/// <param name="vector">The signature vector for this clas that exists in the type registry</param>
		/// <param name="index">The index in the vector that this needs fixing </param>
		void FixExternalPointers(const Vector<Signature>& vector, const std::size_t index);
		/// <summary>
		/// Appends an auxillary attribute to the class calling it
		/// </summary>
		/// <param name="key">The Type ID of the class</param>
		/// <returns>A refernce to the datum that holds the newly created auxillary attribute</returns>
		Datum& AppendAuxillary(const std::string& key);

		/// <summary>
		/// Checks if the key passed in is an attribute
		/// </summary>
		/// <param name="key">The key to check</param>
		/// <returns>Bool indicating if it is an attribute or not</returns>
		bool IsAttribute(const std::string& key);
		/// <summary>
		/// Checks if the key passed in is a prescribed attribute
		/// </summary>
		/// <param name="key">The key to check</param>
		/// <returns>Bool indicating if it is a prescribed attribute or not</returns>
		bool IsPrescribedAttribute(const std::string& key);
		/// <summary>
		/// Checks if the key passed in is an attribute
		/// </summary>
		/// <param name="key">The key to check</param>
		/// <returns>Bool indicating if it is an auxillary attribute or not</returns>
		bool IsAuxillaryAttribute(const std::string& key);


		//Vector<const std::string&>& GetPrescribedAttributes();
		//const Vector<const std::string&>& GetPrescribedAttributes() const;
		//
		//Vector<const std::string&>& GetAttributes();
		////const Vector<const std::string&>& GetAttributes()const;
		//
		//Vector<const std::string&>& GetAuxillaryAttributes();

	protected:
		
		Attributed(std::size_t type);
		virtual ~Attributed() = default;
		Attributed(const Attributed & rhs);
		
		Attributed(Attributed && rhs)noexcept;
		
		Attributed& operator=(const Attributed & rhs);
		
		Attributed& operator=(Attributed && rhs) noexcept;
	};

}


