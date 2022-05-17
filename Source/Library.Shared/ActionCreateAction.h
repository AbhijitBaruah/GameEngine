#pragma once
#include "Action.h"
#include "GameState.h"
namespace GameEngine
{	
	/// <summary>
	/// A class that creates another action and adds it to the target datum
	/// </summary>
	class ActionCreateAction final : public Action
	{
		
		friend class GameState;
		RTTI_DECLARATIONS(ActionCreateAction);

	public:
		/// <summary>
		/// Default constructor to register its prescribed attributes
		/// </summary>
		ActionCreateAction();
		~ActionCreateAction()=default;
		/// <summary>
		/// Just creates the class and adds it to the pending list vector.
		/// </summary>
		/// <param name=""></param>
		void Update(const GameTime&) override;
		/// <summary>
		/// Holds the list of prescribed attributes for this class
		/// </summary>
		/// <returns>A vector holding all the signatures</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The prescribed attribute which specifies the kind of class to be created
		/// </summary>
		std::string actionClassName;
		/// <summary>
		/// The name to be given to the newly created action
		/// </summary>
		std::string actionInstanceName;
		 /// <summary>
		 /// The scope which needs to adopt the newly created action
		 /// </summary>
		 std::string parentInstanceName;

		 /// <summary>
		/// Clone function for a ActionCreateAction that acts as the copy constructor 
		/// </summary>
		/// <returns>A pointer to the newly cloned ActionCreateAction</returns>
		 ActionCreateAction* Clone() const override;
		 /// <summary>
		 /// An equals method to  compare if two ActionCreateAction are equal or not
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
		bool _parentFound{ false };
		Scope* _parentScope{ this };
		inline static Vector<std::pair<Scope*, Scope*>> _pendingListToAdd;
		
	};

	ConcreteFactory(ActionCreateAction,Scope)
}