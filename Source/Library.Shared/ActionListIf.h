#pragma once
#include "ActionList.h"
namespace GameEngine
{
	/// <summary>
	/// A specific action class that implements an If statement, in its Actions datum the first entry is executed if the condition is true or else the second entry is executed
	/// </summary>
	class ActionListIf final : public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf);
	public:
		/// <summary>
		/// Default constructor to register an Action list If class with its signatures
		/// </summary>
		ActionListIf();
		/// <summary>
		/// Holds the list of prescribed attributes for an ActionListIf
		/// </summary>
		/// <returns>A Vector wholding all of the signatures</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The prescribed attribtue which indicates if the if block is true or false, 0 ==true, 1==false
		/// </summary>
		std::int32_t condition;
		/// <summary>
		/// Checks the condition and calls update on the matching action block in its Actions datum
		/// </summary>
		/// <param name="">A game time reference</param>
		void Update(const GameTime&)override;
		/// <summary>
	   /// Clone function for a ActionIf that acts as the copy constructor 
	   /// </summary>
	   /// <returns>A pointer to the newly cloned ActionIf</returns>
		ActionListIf* Clone() const override;
		/// <summary>
		/// An equals method to  compare if two ActionIf are equal or not
		/// </summary>
		/// <param name="rhs">The pointer to compare tp</param>
		/// <returns>A bool stating if the two are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// Returns the name of this class
		/// </summary>
		/// <returns>A string of the name of the class</returns>
		std::string ToString() const override;

	};

	ConcreteFactory(ActionListIf,Scope)
}