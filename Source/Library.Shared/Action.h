#pragma once
#include "Attribute.h"
#include "GameTime.h"
namespace GameEngine
{
	/// <summary>
	/// Abstract class that is the root of all "Actions" i.e. verbs of this game engine. These actions will perfrom some sort of function on the "nouns" i.e. gameobjects
	/// in the scene
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action);
	public:
		/// <summary>
		/// Constructor that registers its signatures by calling attributed's constructor which calls populate 
		/// </summary>
		Action();

		virtual ~Action()=default;
		/// <summary>
		/// Pure virtual update method that child classes will override for action specific update behaviour
		/// </summary>
		/// <param name="">A reference to gameTime</param>
		virtual void Update(const GameTime&) = 0;
		/// <summary>
		/// Return the instance name of this Action
		/// </summary>
		/// <returns>The name of this action</returns>
		const std::string& GetName() const;
		/// <summary>
		/// Sets the instance of this action
		/// </summary>
		/// <param name="actionName">The name to set</param>
		void SetName(const std::string& actionName);

		/// <summary>
		/// A list of all prescribed attributes an action will have
		/// </summary>
		/// <returns>Vector containing all the signatures</returns>
		static Vector<Signature> Signatures();
		std::string name;

	protected: Action(std::size_t childID);
	};


}