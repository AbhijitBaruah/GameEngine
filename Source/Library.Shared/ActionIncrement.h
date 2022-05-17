#pragma once
#include "Action.h"
namespace GameEngine
{
	/// <summary>
	/// A class that increments a target value by the Step specified 
	/// </summary>
	class ActionIncrement final : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement);
	public:
	
		/// <summary>
		/// Default constructor to register and populate its prescribed attributes
		/// </summary>
		ActionIncrement();
		~ActionIncrement() = default;
		/// <summary>
		/// Checks its target datum and if it finds it , adds the "Step" value to it
		/// </summary>
		/// <param name="">A game time reference</param>
		void Update(const GameTime&) override;
		static Vector<Signature> Signatures();
		/// <summary>
		/// The target datum key(Must be up the hierarchy)
		/// </summary>
		std::string target;
		/// <summary>
		/// The amount you want to increment or decrement the target value
		/// </summary>
		float step;
		/// <summary>
		/// Clone function for a actionIncrement that acts as the copy constructor 
		/// </summary>
		/// <returns>A pointer to the newly cloned GameObject</returns>
		ActionIncrement* Clone() const override;
		/// <summary>
		/// An equals method to  compare if two Action Increments are equal or not
		/// </summary>
		/// <param name="rhs">The pointer to compare tp</param>
		/// <returns>A bool stating if the two are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// Returns the name of this class
		/// </summary>
		/// <returns>A string of the name of the class</returns>
		std::string ToString() const override;
	private: Datum* _parent{nullptr};
		   bool _targetFound{ false };
		   std::size_t _type;

	};
	ConcreteFactory(ActionIncrement,Scope)
}
