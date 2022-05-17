#pragma once
#include "Action.h"
namespace GameEngine
{
	class ActionList : public Action
	{
		/// <summary>
		/// A class that implements Action by adding its own list of prescribed attributes called "Actions" which lets it store "Action" children
		/// </summary>
		/// <param name=""></param>
		RTTI_DECLARATIONS(ActionList);
	public:
		/// <summary>
		/// Default constructor that registers its attributes 
		/// </summary>
		ActionList();
		virtual ~ActionList() = default;
		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="rhs">The action list to copy</param>
		ActionList(const ActionList& rhs) = default;
		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="rhs">The rhs Action list you wanna assign to</param>
		/// <returns>A reference to the copied action list</returns>
		ActionList& operator=(const ActionList& rhs) = default;
		/// <summary>
		/// Default copy assignment for a shallow copy of an action list
		/// </summary>
		/// <param name="rhs">The action list to shallow copy from</param>
		ActionList(ActionList&& rhs) noexcept = default;
		/// <summary>
		/// Default move assignment for shallow copy of an action list
		/// </summary>
		/// <param name="rhs">he action list to shallow copy from</param>
		/// <returns>Reference to the shallow copied action List </returns>
		ActionList& operator=(ActionList&& rhs) = default;
		/// <summary>
		/// Returns the "Actions" datum that holds its action children
		/// </summary>
		/// <returns>Datum consisting of all action children</returns>
		Datum& Actions();
		/// <summary>
		/// Create a new action and add it to the Actions datum
		/// </summary>
		/// <param name="className">The kind of action to create</param>
		/// <param name="instanceName">The instance name for the newly created action</param>
		/// <returns></returns>
		Scope* CreateAction(std::string& className, std::string& instanceName);
		/// <summary>
		/// Update method tasked with looping through its children and calling update on each child Action
		/// </summary>
		/// <param name=""></param>
		void Update(const GameTime&) override;
		/// <summary>
		/// List of prescribed attributes for an action list
		/// </summary>
		/// <returns>A vector holding all the signatures needed to populate an action list scope</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// Clone function for a actionList that acts as the copy constructor 
		/// </summary>
		/// <returns>A pointer to the newly cloned GameObject</returns>
		ActionList* Clone() const override;
		/// <summary>
		/// An equals method to  compare if two ActionLists are equal or not
		/// </summary>
		/// <param name="rhs">The pointer to compare tp</param>
		/// <returns>A bool stating if the two are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// Returns the name of this class
		/// </summary>
		/// <returns>A string of the name of the class</returns>
		std::string ToString() const override;
	protected:
		ActionList(std::size_t childID);
	};
	ConcreteFactory(ActionList, Scope)

}