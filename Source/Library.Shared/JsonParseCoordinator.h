#pragma once
#include "RTTI.h"
#include "Vector.h"
#pragma warning (push)
#pragma warning (disable:4635)
#pragma warning (disable:26812)
#include <json/json.h>
#pragma warning (pop)
namespace GameEngine 
{
	class IJsonParseHelper;
	/// <summary>
	/// A JSON coordinator class that follows the chain of responsibility pattern to help parse JSON grammar
	/// </summary>
	class JsonParseCoordinator final
	{
	public:
		/// <summary>
		/// A class that acts as a wrapper to hold the de-serialized data
		/// </summary>
		class SharedData :public RTTI
		{
			friend JsonParseCoordinator;
			RTTI_DECLARATIONS(SharedData);
		public:
			/// <summary>
			/// Pure virtual function to provide a polymorphic construction behavior.
			/// </summary>
			/// <returns>A pointer to the wrapper that contains the de-serialized data</returns>
			virtual SharedData* Create() const=0;
			/// <summary>
			/// Sets depth to zero
			/// </summary>
			virtual void Initialize();
			/// <summary>
			/// Returns the owner of this shared Data class i.e. the coordinator that owns the shared data
			/// </summary>
			/// <returns>A pointer to the coordinator </returns>
			JsonParseCoordinator* GetJsonParseCoordinator();
			/// <summary>
			/// Increments the nesting depth
			/// </summary>
			void IncrementDepth();
			/// <summary>
			/// Decrements the nesting depth
			/// </summary>
			void DecrementDepth();
			/// <summary>
			/// Returns the nesting depth
			/// </summary>
			/// <returns>A size t indicvating the nesting depth </returns>
			std::size_t Depth();
			/// <summary>
			/// Returns the maximum level of nesting during parsing
			/// </summary>
			/// <returns>A size t indicating the nesting max nesting depth</returns>
			std::size_t MaxDepth();
			
		private:
			void SetJsonParseCoordinator(JsonParseCoordinator* coordinator);
			JsonParseCoordinator* _owner{ nullptr };
			std::size_t _depth{ 0 };
			std::size_t _maxDepth{ 0 };
			
		};
		~JsonParseCoordinator();
		JsonParseCoordinator(const JsonParseCoordinator& rhs) = delete;
		JsonParseCoordinator& operator=(const JsonParseCoordinator& rhs) = delete;
		/// <summary>
		/// Shallow copies one coordinator the other and fixes the owner pointer, the move constructor 
		/// </summary>
		/// <param name="rhs">The coordinator you want to shallow copy</param>
		JsonParseCoordinator(JsonParseCoordinator&& rhs) noexcept;
		/// <summary>
		/// Shallow copies one coordinator the other and fixes the owner pointer, the move assignment operator
		/// </summary>
		/// <param name="rhs">The coordinator you want to shallow copy</param>
		/// <returns>A reference to the coordinator that holds the shallow copy</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& rhs) noexcept;
		/// <summary>
		/// Constructor for the coordinator that takes a shared data reference and sets the shared Data pointer to point to the reference passed in
		/// </summary>
		/// <param name="sharedData">A shared data reference</param>
		JsonParseCoordinator(SharedData& sharedData);
		/// <summary>
		/// Returns a pointer to the shared data this coordinator contains
		/// </summary>
		/// <returns></returns>
		SharedData* GetSharedData();
		/// <summary>
		/// Sets the shared Data pointer to point to the reference passed in
		/// </summary>
		/// <param name="sharedData">A shared data pointer</param>
		void SetSharedData(SharedData* sharedData);
		/// <summary>
		/// Add a helper to the list of helpers this coordinator holds
		/// </summary>
		/// <param name="helperToAdd">A reference to the helper needed to add</param>
		void AddHelper(IJsonParseHelper& helperToAdd);
		/// <summary>
		/// Remove a helper from the list of helpers this coordinator holds
		/// </summary>
		/// <param name="helperToAdd">A reference to the helper needed to remove</param>
		bool RemoveHelper(IJsonParseHelper& helperToRemove);
		/// <summary>
		/// A method to de-serialize a JSON string by converting it to a JSON value
		/// </summary>
		/// <param name="parseString">The string needed to parse</param>
		void Parse(Json::String& parseString);
		/// <summary>
		///  A method to de-serialize an istream by converting it to a JSON value
		/// </summary>
		/// <param name="data">The i stream needed to parse</param>
		void Parse(std::istream& data);
		/// <summary>
		///  A method to de-serialize a file by converting it to a JSON value
		/// </summary>
		/// <param name="data">File name to parse</param>
		void ParseFromFile(std::string& fileName);
		/// <summary>
		/// Acts like a copy constructor and clones the this coordinator
		/// </summary>
		/// <returns>A pointer to the newly created clone</returns>
		JsonParseCoordinator* Clone();
		/// <summary>
		/// Gets the list of all the parse helpers
		/// </summary>
		/// <returns>A Vector of all the helpers</returns>
		const Vector<IJsonParseHelper*>& GetParseHelpers()const;
		/// <summary>
		/// Helps clean up memory that might have been allocated if it was a clone
		/// </summary>
		void Cleanup();
		/// <summary>
		/// Checks if this current coordinator is a clone
		/// </summary>
		/// <returns>A bool if it is a clone</returns>
		bool IsClone();
	private:
		void Parse(std::pair < const std::string&, Json::Value>);
		void ParseMembers(Json::Value&);
		SharedData* _sharedData{nullptr};
		Vector<IJsonParseHelper*> _parseHelpers;
		
		bool _isClone{ false };
		
	};


}
