#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "RTTI.h"
#pragma warning (push)
#pragma warning (disable : 4201)
#pragma warning (disable : 4635)
#include "glm/glm.hpp"
#pragma warning (pop)
#include <utility>
#pragma warning (push)
#pragma warning (disable : 4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning (pop)

namespace GameEngine
{
	class Scope;
	class TableParserHelper;
	enum class DatumTypes
	{
		Unknown,
		Integer,
		Float,
		Vector,
		Matrix,
		String,
		Pointer,
		Table,
		Begin = Integer,
		End = Table
	};



	class Datum final
	{
		friend class Attributed;
		friend class Scope;
		friend class TableParserHelper;
	public:

		/// <summary>
		/// Default compiler supplied Constructor for Datum
		/// </summary>
		Datum() = default;
	
		~Datum();
		/// <summary>
		///TypeCast constructor Integer overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a copy of a std::int32_t </param>
		/// <returns> Returns a reference to a Datum </returns>

		Datum(std::int32_t value);

		/// <summary>
		/// TypeCast constructor Float overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a copy of a float </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum(float value);

		/// <summary>
		/// TypeCast constructor String overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a const reference to a std::string</param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum(const std::string& value);

		/// <summary>
		/// TypeCast constructor glm::Vec4 overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a const reference to a glm::vec4</param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum(const glm::vec4& value);

		/// <summary>
		/// TypeCast constructor glm::Mat4 overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a const reference to a glm::vec4</param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum(const glm::mat4& value);
		/// <summary>
		/// TypeCast constructor RTTI pointer overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a copy of a RTTI pointer</param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum(RTTI* value);
		/// <summary>
		/// Copy Constructor for Datum
		/// </summary>
		/// <param name="other"> Takes a const reference to a Datum </param>
		Datum(const Datum& rhs);
		/// <summary>
		/// Copy Assignment Operator for Datum
		/// </summary>
		/// <param name="other"> Takes a const reference to a Datum </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(const Datum& rhs);
		/// <summary>
		/// Copy Assignment Operator Integer overload for Datum
		/// </summary>
		/// <param name="i"> Takes a copy of an int </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(std::int32_t integer);
		/// <summary>
		/// Copy Assignment Operator Float overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a copy of a float </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(float f);
		/// <summary>
		/// Copy Assignment Operator GLM Vector overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a const reference to a glm::vec4 </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(const glm::vec4& v);
		/// <summary>
		/// Copy Assignment Operator GLM Matrix overload for Datum 
		/// </summary>
		/// <param name="f"> Takes a const reference to a glm::mat4 </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(const glm::mat4& m);
		/// <summary>
		/// Copy Assignment Operator String overload for Datum
		/// </summary>
		/// <param name="s"> Takes a const reference to a std::string </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(const std::string& s);
		/// <summary>
		/// Copy Assignment Operator RTTI Pointer overload for Datum
		/// </summary>
		/// <param name="r"> Takes a pointer to an RTTI </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(RTTI* p);
		/// <summary>
		/// Move Constructor for Datum
		/// </summary>
		/// <param name="other"> Takes a rvalue reference to a Datum </param>
		Datum(Datum&& rhs) noexcept;
		/// <summary>
		/// Move Assignment Operator for Datum
		/// </summary>
		/// <param name="other"> Takes a rvalue reference to a Datum </param>
		/// <returns> Returns a reference to a Datum </returns>
		Datum& operator=(Datum&& rhs) noexcept;
		/// <summary>
		/// Equality Operator for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a Datum </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(const Datum& rhs) const;
		/// <summary>
		/// Equality Operator Integer Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an int </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(std::int32_t rhs) const;
		/// <summary>
		/// Equality Operator Float Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of a float </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(float rhs) const;
		/// <summary>
		/// Equality Operator String Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a Datum </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(const std::string& rhs) const;
		/// <summary>
		/// Equality Operator GLM Matrix Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::mat4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(const glm::mat4& rhs) const;
		/// <summary>
		/// Equality Operator GLM Vector Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::vec4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(const glm::vec4& rhs) const;
		/// <summary>
		/// Equality Operator RTTI Pointer Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a pointer to a RTTI </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator==(RTTI* rhs) const;
		/// <summary>
		/// In-equality operator for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a Datum </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(const Datum& rhs);
		/// <summary>
		/// In-equality operator Integer Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an int </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(std::int32_t rhs);
		/// <summary>
		/// In-equality operator Float Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of a float </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(float rhs);
		/// <summary>
		/// In-equality operator String Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a std::string </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(const std::string& rhs);
		/// <summary>
		/// In-equality operator GLM Matrix Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::mat4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(const glm::mat4& rhs);

		/// <summary>
		/// In-equality operator GLM Vector Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::vec4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(const glm::vec4& rhs);
		/// <summary>
		/// In-equality operator RTTI Pointer Overload for Datum
		/// </summary>
		/// <param name="value"> Takes a pointer to a RTTI </param>
		/// <returns> Returns a copy of a bool </returns>
		bool operator!=(RTTI* rhs);

		/// <summary>
		/// Resize method for Datum, which sets size and capacity and equal for the datum and default constructs the objects.
		/// </summary>
		/// <param name="size"> Takes a copy of a size_t </param>
		void Resize(std::size_t newSize);
		/// <summary>
		/// ShrinkToFit method for Datum , deletes all extra memory, and sets capacity to size passed in 
		/// </summary>
		void ShrinkToFit(std::size_t newSize);
		/// <summary>
		/// Clear method for Datum, clears and removes all datum elements and frees the memory
		/// </summary>
		void Clear();
		/// <summary>
		/// Set Storage Integer overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="intArray"> Takes a pointer to an int </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(std::int32_t* array, std::size_t size);
		/// <summary>
		/// Set Storage Float overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="floatArray"> Takes a pointer to an float </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(float* array, std::size_t size);
		/// <summary>
		/// Set Storage String overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="stringArray"> Takes a pointer to an std::string </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(std::string* array, std::size_t size);
		/// <summary>
		/// Set Storage GLM Vector overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="vecArray"> Takes a pointer to an glm::vec4 </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(glm::vec4* array, std::size_t size);
		/// <summary>
		/// Set Storage GLM Matrix overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="matArray"> Takes a pointer to an glm::mat4 </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(glm::mat4* array, std::size_t size);
		/// <summary>
		/// Set Storage RTTI Pointer overload for Datum, sets the datum to an external datum
		/// </summary>
		/// <param name="pointerArray"> Takes a double pointer to a RTTI </param>
		/// <param name="size"> Takes a copy of a size_t </param>
		void SetStorage(RTTI** array, std::size_t size);
		/// <summary>
		/// Set From String for Datum, takes in a string and parses it before setting the appropriate type
		/// </summary>
		/// <param name="inputString"> Takes a const reference to a std::string </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void SetFromString(const std::string&, std::size_t index = 0);
		/// <summary>
		/// ToString method for Datum, which returns a string value of the data contained in the index passed in
		/// </summary>
		/// <param name="index"> Takes a copy of a size_t </param>
		/// <returns> Returns a copy of a std::string </returns>
		std::string ToString(std::size_t = 0);
		/// <summary>
		/// SetType method for Datum , checks if the datum type is unknown and if it is it does set the type to the type passed in
		/// </summary>
		/// <param name="type"> Takes a copy of a DatumType enum class </param>
		void SetType(DatumTypes d);
		/// <summary>
		/// Reserve method for Datum
		/// </summary>
		/// <param name="capacity"> Takes a copy of a size_t </param>
		void Reserve(std::size_t capacity);
		/// <summary>
		/// RemoveAt method for Datum, Deletes the element at the specified index 
		/// </summary>
		/// <param name="index"> Takes a copy of a size_t </param>
		void RemoveAt(std::size_t index);
		/// <summary>
		/// Remove Integer overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an int </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(std::int32_t obj);
		/// <summary>
		/// Remove Float overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an float </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(float obj);
		/// <summary>
		/// Remove GLM Vector overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::vec4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(const glm::vec4& obj);
		/// <summary>
		/// Remove GLM Matrix overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::mat4 </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(const glm::mat4& obj);
		/// <summary>
		/// Remove String overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a std::string </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(const std::string& obj);
		/// <summary>
		/// Remove RTTI Pointer overload for Datum
		/// </summary>
		/// <param name="value"> Takes a pointer to a RTTI </param>
		/// <returns> Returns a copy of a bool </returns>
		bool Remove(RTTI* obj);

		/// <summary>
		/// Find overload for std::int32_t.
		/// </summary>
		/// <param name="obj"></param>
		/// <returns>a std::pair(bool,size_t) that indicates if the value has been found and its index</returns>
		std::pair<bool, std::size_t> Find( std::int32_t obj);
		/// <summary>
		/// Find Float overload for Datum
		/// </summary>
		/// <param name="obj"></param>
		/// <returns>a std::pair(bool,size_t) that indicates if the value has been found and its index</returns>
		std::pair<bool, std::size_t> Find(float obj);
		/// <summary>
		/// Find String overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const std::string reference</param>
		/// <returns> Returns a copy of a std::pair(bool,size_t) </returns>
		std::pair<bool, std::size_t> Find(const std::string& obj);
		/// <summary>
		/// Find Vector overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const std::glm vec 4 reference</param>
		/// <returns> Returns a copy of a std::pair (bool,size_t) </returns>
		std::pair<bool, std::size_t> Find(const glm::vec4& obj);
		/// <summary>
		/// Find Matrix overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const std::glm mat 4 reference</param>
		/// <returns> Returns a copy of a std::pair (bool,size_t) </returns>
		std::pair<bool, std::size_t> Find(const glm::mat4& obj);
		/// <summary>
		/// Find Pointer overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of RTTI*</param>
		/// <returns> Returns a copy of a std::pair (bool,size_t) </returns>
		std::pair<bool, std::size_t> Find(RTTI* obj);
		/// <summary>
		/// Set Integer overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an int </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(std::int32_t value, std::size_t index = 0);
		/// <summary>
		/// Set Float overload for Datum
		/// </summary>
		/// <param name="value"> Takes a copy of an float </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(float value, std::size_t index = 0);
		/// <summary>
		/// Set GLM Vector overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::vec4 </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(const glm::vec4& value, std::size_t index = 0);
		/// <summary>
		/// Set GLM Matrix overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a glm::mat4 </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(const glm::mat4& value, std::size_t index = 0);
		/// <summary>
		/// Set String overload for Datum
		/// </summary>
		/// <param name="value"> Takes a const reference to a std::string </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(const std::string& value, std::size_t index = 0);
		/// <summary>
		/// Set RTII Pointer overload for Datum
		/// </summary>
		/// <param name="value"> Takes a pointer to a RTTI </param>
		/// <param name="index"> Takes a copy of a size_t </param>
		void Set(RTTI* value, std::size_t index = 0);
		/// <summary>
		/// PushBack Integer overload for Datum 
		/// </summary>
		/// <param name="i"> Takes a copy of an int </param>
		void PushBack(std::int32_t value);
		/// <summary>
		/// PushBack Float overload for Datum
		/// </summary>
		/// <param name="f"> Takes a copy of a float </param>
		void PushBack(float value);
		/// <summary>
		/// PushBack String overload for Datum
		/// </summary>
		/// <param name="s"> Takes a const reference to a std::string </param>
		void PushBack(const std::string& value);
		/// <summary>
		/// PushBack GLM Vector overload for Datum
		/// </summary>
		/// <param name="v"> Takes a const reference to a glm::vec4 </param>
		void PushBack(const glm::vec4& value);
		/// <summary>
		/// PushBack GLM Matrix overload for Datum
		/// </summary>
		/// <param name="m"> Takes a const reference to a glm::mat4 </param>
		void PushBack(const glm::mat4& value);
		/// <summary>
		/// PushBack RTTI Pointer overload for Datum
		/// </summary>
		/// <param name="r"> Takes a copy of a RTTI pointer </param>
		void PushBack(RTTI* value);
		/// <summary>
		/// PushBack String overload for Datum
		/// </summary>
		/// <param name="s"> Takes a const R value reference to a std::string </param>
		void PushBack(const std::string&& value);
		void PushBackFromString(const std::string&);
		/// <summary>
		/// PopBack method for Datum 
		/// </summary>
		void PopBack();
		/// <summary>
		/// Templated get for Datum, returns a reference to the data held in the index passed in, default value is 0
		/// </summary>
		/// <typeparam name="AbstractFactory"></typeparam>
		/// <param name="index"> The index you want to retrieve the value from</param>
		/// <returns>A =AbstractFactory reference </returns>
		template <typename AbstractFactory>
		AbstractFactory& Get(std::size_t index = 0);
		/// <summary>
		/// Overload for Templated get for Datum, returns a const AbstractFactory reference to the data held in the index passed in,default value is 0
		/// </summary>
		/// <typeparam name="AbstractFactory"></typeparam>
		/// <param name="index"> The index you want to retrieve the value from</param>
		/// <returns>A =AbstractFactory reference </returns>
		template <typename AbstractFactory>
		const AbstractFactory& Get(std::size_t index = 0) const;
		/// <summary>
		/// Templated version of Front, returns the first value in the datum
		/// </summary>
		/// <typeparam name="AbstractFactory"></typeparam>
		/// <returns>a AbstractFactory reference to the first element</returns>
		template <typename AbstractFactory>
		AbstractFactory& Front();
		/// <summary>
		/// Templated version of Front, returns the first value in the datum
		/// </summary>
		/// <typeparam name="AbstractFactory"></typeparam>
		/// <returns>a A const AbstractFactory reference to the first element</returns>
		template <typename AbstractFactory>
		const AbstractFactory& Front() const;
		/// <summary>
		/// Size method for Datum
		/// </summary>
		/// <returns> Returns a copy of a size_t </returns>
		std::size_t Size()const;
		/// <summary>
		/// Capacity method for Datum
		/// </summary>
		/// <returns> Returns a copy of a size_t </returns>
		std::size_t Capacity()const;
		/// <summary>
		/// Type method for Datum
		/// </summary>
		/// <returns> Returns a copy of a DatumType enum class </returns>
		DatumTypes Type() const;

		bool IsExternal() const;

	private:
		void SetStorage(void* vp, std::size_t size, DatumTypes type);
		union DatumValues final
		{
			std::int32_t* i;
			float* f;
			std::string* s;
			glm::mat4* m;
			glm::vec4* v;
			RTTI** r;
			Scope** t;
			std::uint8_t* b;
			void* vp{ nullptr };
		};
		Datum(Scope* _value);

		void Set(Scope* _value, std::size_t index = 0);

		void PushBack(Scope* value);

		Scope& operator[](std::size_t index);

		DatumValues _data;
		DatumTypes _type{ DatumTypes::Unknown };
		std::size_t _capacity{ 0 };
		std::size_t _size{ 0 };
		static const std::size_t DatumTypeSizes[static_cast<std::size_t>(DatumTypes::End) + 1];
		bool _isExternal{ false };
		
	};

}

#include "Datum.inl"