#pragma once
#include "Attribute.h"
#include "glm/glm.hpp"
#include "GameTime.h"
#include "Factory.h"
namespace GameEngine
{
	/// <summary>
	/// A struct that will be sued as a prescribed attribute for a gameObject. The struct contains 3 vec4's to store the gameobject's position , rotation and transform
	/// </summary>
	struct Transform final
	{
		glm::vec4 position;
		glm::vec4 rotation;
		glm::vec4 scale;
	};
	/// <summary>
	/// A class for the hierarchical root of our game scene i.e. a gameobjecyt. This can store all kinds of scope's and other nested child gameObjects. The game loop will essentially run by calling update on this root which in turn
	/// will call Update on each of its childeren. A game object has 5 prescribed attributes, A name , 3 vec4's for its transform and a Children attribute which stores all of its child Gameobjects. This would mean all pointers of type Scope 
	/// inside its childern datum have to be of type is gameObject 
	/// </summary>
	class GameObject : public Attributed
	{

		RTTI_DECLARATIONS(GameObject);
	public:

		/// <summary>
		/// Default constructor for GameObject which calls Attributed's default constructor which helps populate this scope with its prescribed attributes 
		/// </summary>
		GameObject();
		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="rhs">The rhs Gameobject</param>
		GameObject(const GameObject& rhs) = default;
		/// <summary>
		/// Default move constructor
		/// </summary>
		/// <param name="rhs">The rhs Gameobject</param>
		GameObject& operator=(const GameObject& rhs) = default;
		/// <summary>
		/// Default copy assignment
		/// </summary>
		/// <param name="rhs">The rhs Gameobject</param>
		GameObject(GameObject&& rhs) = default;
		/// <summary>
		/// Default move assignment
		/// </summary>
		/// <param name="rhs">The rhs Gameobject</param>
		GameObject& operator=(GameObject&& rhs) = default;
		virtual ~GameObject();
		/// <summary>
		/// An update method which is the "game loop" which would loop through all of its children and update attributes 
		/// </summary>
		/// <param name="">Takes in a game time instance which would act like delta time </param>
		virtual void Update(const GameTime&);
		/// <summary>
		/// List of signatures for its prescribed attributes
		/// </summary>
		/// <returns>Returns a vector holding all the signatures for a gameObject</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// Clone function for a gameObject that acts as the copy constructor 
		/// </summary>
		/// <returns>A pointer to the newly cloned GameObject</returns>
		GameObject* Clone() const override;

		/// <summary>
		/// An equals method to  compare if two game Objects are equal or not
		/// </summary>
		/// <param name="rhs">The pointer to compare tp</param>
		/// <returns>A bool stating if the two are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		/// <summary>
		/// Returns the name of this class
		/// </summary>
		/// <returns>A string of the name of the class</returns>
		std::string ToString() const override;
		/// <summary>
		/// Reference to the transform struct to store as its prescribed attribute for transform, rotation and scale
		/// </summary>
		Transform transform;
		/// <summary>
		/// String for its prescribed attribute to store as its "Name"
		/// </summary>
		std::string Name;

		const Datum& Actions() const;
		Datum& Actions();
		Scope* CreateAction(const std::string& className, const std::string& instanceName);

	protected:
		/// <summary>
		/// A protected constructor to help children inheriting from gameObject to pass their type ID to attributed to populate their prescribed attributes
		/// </summary>
		GameObject(std::size_t childID);
	};


	ConcreteFactory(GameObject, Scope)
}