#pragma once
#include <functional>
namespace GameEngine 
{
	
	template <typename AbstractFactory>
	class SList final
	{
	private:
		struct Node final
		{
			 AbstractFactory data;
		   Node* next;

		   Node(const AbstractFactory& Data, Node* Next);
		};
	/// <summary>
	/// Iterator Class For An S list to help iterate through the nodes
	/// </summary>
	/// <typeparam name="AbstractFactory"></typeparam>
	public:
		class Iterator 
		{
			friend SList;

		public:
			Iterator() = default;
			Iterator(const Iterator& other) = default;
			~Iterator() = default;
			Iterator& operator=(const Iterator& other) = default;
			/// <summary>
			/// Overload of the not equal to operator to check if two iterators  not equal i.e. they DO NOT point to the same list or the same node
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const Iterator& other) const;
			/// <summary>
		/// Overload of the not equal to operator to check if two iterators are equal i.e. they point to the same list AND the same node
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// Post increment operator, makes the iterator point to the next node in the list
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();
			Iterator operator++(int);
			AbstractFactory& operator*();
			
		private:
			Iterator(const SList& list, Node* Node = nullptr);
			Node* _node{ nullptr };
			const SList* _owner{ nullptr };
		
		};
	public:
		/// <summary>
		/// Creates a constIterator for SList
		/// </summary>
		class ConstIterator
		{
			friend SList;
		public:
			ConstIterator() = default;
			~ConstIterator() = default;
			ConstIterator& operator=(const ConstIterator& other) = default;
			ConstIterator(const Iterator& other);
			bool operator!=(const ConstIterator& other)const;
			bool operator==(const ConstIterator& other) const;
			ConstIterator& operator++();
			ConstIterator operator++(int);
			const AbstractFactory& operator*() const;
			
			
		private:
			ConstIterator(const SList& list, Node* Node = nullptr);
			Node* _node{ nullptr };
			const SList* _owner{nullptr};
		};
		/// <summary>
		/// Returns the number of nodes in the list
		/// </summary>
		/// <returns></returns>
		inline const std::size_t Size() const;
		/// <summary>
		/// Checks if the list is empty or not
		/// </summary>
		/// <returns></returns>
		 bool IsEmpty();
		/// <summary>
		/// Default constructor that builds a linked list with 0 nodes
		/// </summary>
		SList();
		~SList();
		/// <summary>
		/// Copy constructor to deep copy one linked list into another
		/// </summary>
		/// <param name="other"></param>
		SList(const SList& other);
		/// <summary>
		/// Assignment operator to deep copy one list to another.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		SList& operator=(SList& other);
		/// <summary>
		/// Equals to operator to provide a way of comparing two lists
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator ==( const SList& rhs) const;
		/// <summary>
		/// Pushes the given node into the beginning of the list
		/// </summary>
		/// <param name="data"></param>
		Iterator PushFront(const AbstractFactory& data);
		/// <summary>
		/// Pushes the given node at the end of the list
		/// </summary>
		/// <param name="data"></param>
		Iterator PushBack(const AbstractFactory& data);
		/// <summary>
		/// Checks the front of the list and returns a constant value of the node at the front
		/// </summary>
		/// <returns></returns>
		const AbstractFactory& Front() const;
		/// <summary>
		/// Checks the front of the list and returns a non constant value of the node at the front
		/// </summary>
		/// <returns></returns>
		AbstractFactory& Front();
		/// <summary>
		/// Checks the back of the list and returns a constant value of the node at the back
		/// </summary>
		/// <returns></returns>
		const AbstractFactory& Back() const;
		/// <summary>
		/// Checks the back of the list and returns a non constant value of the node at the back
		/// </summary>
		/// <returns></returns>
		AbstractFactory& Back();
		/// <summary>
		/// Deletes the node at the front of the list.
		/// </summary>
		/// <returns></returns>
		void PopFront();
		/// <summary>
		/// Deletes the node at the end of the list.
		/// </summary>
		/// <returns></returns>
		void PopBack();
		/// <summary>
		/// Deletes every node of the linked list
		/// </summary>
		virtual void Clear();

		/// <summary>
		/// Returns an iterator that is assigned to the calling list and points to its front node
		/// </summary>
		/// <returns></returns>
		Iterator begin();
		/// <summary>
		///  Returns a ConstIterator that is assigned to the calling list and points to its front node
		/// </summary>
		/// <returns></returns>
		ConstIterator begin()const;
		/// <summary>
		/// Returns a ConstIterator that is assigned to the calling list and points to its front node
		/// </summary>
		/// <returns></returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// Returns an iterator that is assigned to this list but points to a nullptr as its node i.e. one node after the end
		/// </summary>
		/// <returns></returns>
		Iterator end();
		/// <summary>
		/// Returns an iterator that is assigned to this list but points to a nullptr as its node i.e. one node after the end
		/// </summary>
		/// <returns></returns>
		ConstIterator end()const;
		/// <summary>
		/// Returns an iterator that is assigned to this list but points to a nullptr as its node i.e. one node after the end
		/// </summary>
		/// <returns></returns>
		ConstIterator cend()const;
		/// <summary>
		/// Finds a particular value and returns an iterator pointing to that value in the list by either using the default == operator for that data type, alternatively a functor can be provided for the same.
		/// </summary>
		/// <param name="value"></param>
		/// <param name="equalityFunctor"></param>
		/// <returns></returns>
		Iterator Find(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor = std::equal_to<AbstractFactory>());
		/// <summary>
		/// Finds a particular value and returns a ConstIterator pointing to that value in the list by either using the default == operator for that data type, alternatively a functor can be provided for the same.
		/// </summary>
		/// <param name="value"></param>
		/// <param name="equalityFunctor"></param>
		/// <returns></returns>
		ConstIterator Find(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor = std::equal_to<AbstractFactory>()) const;
		/// <summary>
		/// Inserts a value after the node the iterator passed in is currently pointing to as long as they refer to the same list
		/// </summary>
		/// <param name="it"></param>
		/// <param name="value"></param>
		void InsertAfter(const Iterator& it, const AbstractFactory& value);
		/// <summary>
		/// Removes a value from the list thas has a data equal to the value passed in by using the == operator for that data type, alternatively a functor can be provided for the same.
		/// </summary>
		/// </summary>
		/// <param name="value"></param>
		/// <param name="equalityFunctor"></param>
		void Remove(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor = std::equal_to<AbstractFactory>());
		bool IsEmpty()const;
	private:
		std::size_t _size{ 0 };
		/// <summary>
		/// Node pointer that points to the front of the list
		/// </summary>
		Node* _front{ nullptr };
		/// <summary>
		/// Node pointer that points to the back of the list
		/// </summary>
		Node* _back{ nullptr };

		
	};
	
}

#include "SList.inl"

