#pragma once
#include "HashMap.h"
#include "gsl/gsl"
#include "gsl/pointers"
namespace GameEngine
{
	/// <summary>
	/// A templated class that helps create abstract factoires that un turn create concrete objects of that type
	/// </summary>
	template<typename AbstractFactory>
	class Factory
	{
	
	public:
		/// <summary>
		/// Default factory constructor
		/// </summary>
		Factory()=default;
		virtual ~Factory()=default;
		Factory(const Factory<AbstractFactory>& rhs) = delete;
		Factory<AbstractFactory>& operator=(const Factory<AbstractFactory>& rhs) = delete;
		Factory(Factory<AbstractFactory>&& rhs) = delete;
		Factory<AbstractFactory>& operator=(Factory<AbstractFactory>&& rhs) = delete;
		/// <summary>
		/// Checks the static hashmap and returns the concrete factory type 
		/// </summary>
		/// <param name="className">The concrete factory you want to find</param>
		/// <returns>A gsl owner pointer to the factory if it exists , nullptr otherwise</returns>
		inline static Factory<AbstractFactory>* Find(const std::string& className);
		/// <summary>
		/// Creates a concrete factory object 
		/// </summary>
		/// <param name="className">Name of the concrete factory you want to create</param>
		/// <returns>A pointer of the abstract class type , nullptr if the key does not exist</returns>
		inline  static gsl::owner<AbstractFactory*>  Create(const std::string& className);
		

	protected:
		inline  static void  Add(Factory<AbstractFactory>& concreteFactory);
		inline  static  void  Remove(Factory<AbstractFactory>& concreteFactory);
		virtual gsl::owner<AbstractFactory*> Create() const = 0;
		virtual const std::string& ClassName() const = 0;
	private:
		// Making it const breaks it, why?
		inline  static  HashMap<std::string, Factory<AbstractFactory>*> _factoryList;
			
	};


#define ConcreteFactory(concreteFactoryClass,AbstractFactoryGroup)\
class concreteFactoryClass ## Factory : public Factory<AbstractFactoryGroup>\
{\
public:\
concreteFactoryClass ## Factory():_className(#concreteFactoryClass)\
{\
Add(*this);\
}\
~concreteFactoryClass ## Factory()\
{\
Remove(*this);\
}\
const std::string& ClassName()const override\
{\
return _className;\
}\
gsl::owner<AbstractFactoryGroup*>Create() const override\
{\
return new concreteFactoryClass;\
}\
private: std::string _className;\
};\

}
#include "Factory.inl"