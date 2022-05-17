#pragma once
#include "Action.h"
namespace GameEngine
{
	
	class ActionRemoveAction final  : public Action
	{
		/// <summary>
		/// Class to remove a specific action from a datum
		/// </summary>
		friend class GameState;
		RTTI_DECLARATIONS(ActionRemoveAction);
	public:
		/// <summary>
		/// Default constructor to populate 
		/// </summary>
		ActionRemoveAction();
		/// <summary>
		/// Loops through the actions datum in the hierarchy and deletes the instance name stored as a prescribed attribute 
		/// </summary>
		/// <param name=""></param>
		void Update(const GameTime&) override;
		/// <summary>
		/// A list of all the prescribed attributes
		/// </summary>
		/// <returns>A vector holding all the signatures</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// Prescribed attribute that holds the name of the instance to delete
		/// </summary>
		std::string nameToDelete;
		/// <summary>
		/// Clone function for a ActionRemoveAction that acts as the copy constructor 
		/// </summary>
		/// <returns>A pointer to the newly cloned GameObject</returns>
		ActionRemoveAction* Clone() const override;
		/// <summary>
		/// An equals method to  compare if two ActionRemoveAction are equal or not
		/// </summary>
		/// <param name="rhs">The pointer to compare tp</param>
		/// <returns>A bool stating if the two are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// Returns the name of this class
		/// </summary>
		/// <returns>A string of the name of the class</returns>
		std::string ToString() const override;
	
	private:
		inline static Vector<std::pair<Datum*, std::size_t>> _pendingListToRemove;
	};
	ConcreteFactory(ActionRemoveAction,Scope)

}
