#pragma once

#include "Datum.h"
#include "HashMap.h"
#include "Vector.h"
#include "Factory.h"

namespace GameEngine
{

	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope);

	public:
		/// <summary>
		/// Scope constructor that initalizes a hashmap with the capacity passed in with a default capacity of 11 if no argument is passed 
		/// </summary>
		Scope(std::size_t size = 10);
		virtual ~Scope();
		/// <summary>
		/// Copy constructor for scope which deep copies one scope to another scope
		/// </summary>
		/// <param name="rhs"> Takes a constant reference to a scope</param>
		Scope(const Scope& rhs);
		/// <summary>
		/// Default copy assignment which deep copies one scope to another scope after clearing the LHS scope
		/// </summary>
		/// <param name="rhs"> A const reference to a scope</param>
		/// <returns> The scope the RHS has been deep copied into</returns>
		Scope& operator=(const Scope& rhs);
		/// <summary>
		/// Move constructor for Scope which shallow copies the RHS scope into this scope and nulls out the rhs scope
		/// </summary>
		/// <param name="rhs">A const scope to RHS scope</param>
		Scope(Scope&& rhs)noexcept;
		/// <summary>
		/// Move assignment for scope which shallow copies the RHS scope into this scope and nulls out the RHS scope
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		Scope& operator=(Scope&& rhs) noexcept;
		/// <summary>
		/// Equality operator for Scope that compares if two scopes are equal as long as they contain the same elements , the order of insertion does not matter
		/// </summary>
		/// <param name="rhs">A const reference to the scope you want to equate to</param>
		/// <returns>A bool indicating if the scope is equal to the RHS </returns>
		bool operator==(const Scope& rhs)const;
		/// <summary>
		/// Equality operator for Scope that compares if two scopes are equal as long as they contain the same elements , the order of insertion does not matter
		/// </summary>
		/// <param name="rhs">A const reference to the scope you want to equate to</param>
		/// <returns>A bool indicating if the scope is equal to the RHS </returns>
		bool operator!=(const Scope& rhs) const;
		/// <summary>
		/// wraps Append, for syntactic convenience.
		/// </summary>
		/// <param name="key">Takes a constant string</param>
		/// <returns>A datum reference corresponding to the Key passed</returns>
		Datum& operator[](const std::string& key);
		/// <summary>
		/// Bracket operator to access pairs in the Scope
		/// </summary>
		/// <param name="index">an unsigned integer</param>
		/// <returns> a reference to a Datum at the given index</returns>
		Datum& operator[](std::int32_t index);
		/// <summary>
		/// Returns a reference to a Datum with the associated name. If it already exists, return that one, otherwise create one
		/// </summary>
		/// <param name="key">A string key</param>
		/// <returns>Returns a reference to a Datum with the associated name</returns>
		Datum& Append(const std::string& key);
		/// <summary>
		///  Returns a reference to a Scope with the associated name. If a Datum already exists at that key reuse it (and append to it a new Scope), otherwise create a new Datum.
		/// </summary>
		/// <param name="key">A string key</param>
		/// <returns>a reference to a Scope with the associated name</returns>
		Scope& AppendScope(const std::string& key);
		/// <summary>
		///  Returns the address of the most-closely nested Datum associated with the given name in this Scope or its ancestors, if it exists, and nullptr otherwise. 
		/// </summary>
		/// <param name="key">The key you want to search</param>
		/// <param name="outScope">The scope you want to serch in , used an as out parameter</param>
		/// <returns>Address of the datum the key is found in</returns>
		Datum* Search(const std::string& key, Scope*& outScope);
		/// <summary>
		///  Returns the address of the most-closely nested Datum associated with the given name in this Scope or its ancestors, if it exists, and nullptr otherwise. 
		/// </summary>
		/// <param name="key">The key you want to search</param>
		/// <returns>Address of the datum the key is found in</returns>
		Datum* Search(const std::string& key);
		/// <summary>
		///  Returns the address of the most-closely nested Datum associated with the given name in this Scope or its ancestors, if it exists, and nullptr otherwise. 
		/// </summary>
		/// <param name="key">The key you want to search</param>
		/// <param name="outScope">The scope you want to serch in , used an as out parameter</param>
		/// <returns>Address of the const datum by the key is found in</returns>
		const Datum* Search(const std::string& key, const Scope*& outScope) const;
		/// <summary>
		///  Returns the address of the most-closely nested Datum associated with the given name in this Scope or its ancestors, if it exists, and nullptr otherwise. 
		/// </summary>
		/// <param name="key">The key you want to search</param>
		/// <returns>Address of the const datum the key is found in</returns>
		const Datum* Search(const std::string& key) const;
		/// <summary>
		///  Return the address of the Datum associated with the given name in this Scope, if it exists, and nullptr otherwise(Local Find).
		/// </summary>
		/// <param name="key">The key used to find the pair</param>
		/// <returns>a pointer to a const Datum</returns>
		const Datum* Find(const std::string& key) const;
		/// <summary>
		///  Return the address of the Datum associated with the given name in this Scope, if it exists, and nullptr otherwise(Local Find).
		/// </summary>
		/// <param name="key">The key used to find the pair</param>
		/// <returns>a pointer to a Datum</returns>
		Datum* Find(const std::string& key);
		/// <summary>
		/// Returns the address of the Scope which contains this one.
		/// </summary>
		/// <returns>A scope pointer which is the parent of the scope calling this function</returns>
		Scope* GetParent();
		/// <summary>
		/// Returns the address of the Scope which contains this one.
		/// </summary>
		/// <returns>A constnat scope pointer which is the parent of the scope calling this function</returns>
		const Scope* GetParent()const;
		/// <summary>
		/// Takes a scope and sets its parent to the scope calling this function
		/// </summary>
		/// <param name="scopeToAdopt">A reference to the scope you wanna adopt</param>
		/// <param name="key">The key you want to associate with this scope</param>
		void Adopt(Scope& scopeToAdopt, const std::string& key);
		/// <summary>
		/// Checks to see if the scope calling this function is a parent to the Scope pointer passed in, if not , returns a null pointer and a size of 0
		/// </summary>
		/// <param name="scopeToFindIn">The scope to find </param>
		/// <returns>A pair of the pointer pointing to the Datum inside which the scope was found and the index at which the scope was found</returns>
		std::pair<Datum*, std::size_t> FindContainedScope(Scope* const scopeToFindIn);
		/// <summary>
		/// Checks to see if the scope calling this function is a parent to the Scope pointer passed in, if not , returns a null pointer and a size of 0
		/// </summary>
		/// <param name="scopeToFindIn">The scope to find </param>
		/// <returns>A constant pair of the pointer pointing to the Datum inside which the scope was found and the index at which the scope was found</returns>
		const std::pair<Datum*, std::size_t> FindContainedScope(Scope* const scopeToFindIn) const;
		/// <summary>
		/// Removes a scope from its parent 
		/// </summary>
		void Orphan();

		/// <summary>
		/// Loops through the entire scope hierarchy and deletes all scopes
		/// </summary>
		virtual void Clear();
		/// <summary>
		/// Checks if the scope is empty or not
		/// </summary>
		/// <returns>A boolean indicating if the scope is empty</returns>
		bool IsEmpty() const;
		/// <summary>
		/// Override for RTTI equals which checks if two Scope pointers are equal or not by calling the Scope equality operator
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool Equals(const RTTI* rhs) const override;

		Datum& At(const std::string key);
		const Datum& At(const std::string key) const;

	protected:
		bool IsAncestorOf(const Scope& scope) const;

		bool IsDescendentOf(const Scope& scope) const;
	protected:
		virtual Scope* Clone() const;
		Vector<typename HashMap<const std::string, Datum>::PairType*> _orderedVector;
		HashMap<std::string, Datum> _map;
		Scope* _parent{ nullptr };

	};

	ConcreteFactory(Scope, Scope)
}
