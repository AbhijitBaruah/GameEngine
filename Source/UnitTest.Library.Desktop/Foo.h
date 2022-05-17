#pragma once
#include "RTTI.h"
#include "Factory.h"
namespace GameEngine
{
	class Foo:public RTTI
	{
		RTTI_DECLARATIONS(Foo);

	public:	
		/// <summary>
		/// A constructor that assigns the value of mData to the data passed
		/// </summary>
		/// <param name="data"></param>
		Foo(std::int32_t data=0);
		/// <summary>
		/// Copy constructor to deep copy the value of mData from one Foo to another
		/// </summary>
		/// <param name="other"></param>
		Foo(const Foo& other);
		/// <summary>
		/// Assignment operator to deep copy the value of mData from one Foo to another
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Foo& operator = (const Foo& other);

		~Foo();

		  /// <summary>
		  /// Return mData as a non const reference
		  /// </summary>
		  /// <returns></returns>
		  std::int32_t& Data();
		 /// <summary>
		 /// Return mData as a const reference
		 /// </summary>
		 /// <returns></returns>
		 const std::int32_t& Data() const;
		/// <summary>
		/// Overloading the == operator to compare two Foo objects and check if they are equal or not
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const Foo& rhs) const;
		/// <summary>
		/// Overloading the != operator to compare two Foo objects and check if they are equal or not
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const Foo& rhs) const;


	private:
		std::int32_t* mData{ 0 };

	};

	/*class FooFactory : public Factory<RTTI>
	{
	public:
		FooFactory(): _className("Foo")
		{
			Add(*this);
		}
		~FooFactory()
		{
			Remove(*this);
		}
		const std::string& ClassName() const override
		{
			return _className;
		}

		gsl::owner<RTTI*> Create() const override
		{
			return new Foo;
		}

	private: std::string _className;
	};*/

	ConcreteFactory(Foo,RTTI)
}


