#pragma once
#include <functional>
#include <cstddef>
#include <cstdint>
namespace  GameEngine
{
	template <typename T>
	class Vector final
	{
	private:
		std::size_t _capacity;
		std::size_t _size{ 0 };
		T* _data{ nullptr };

	public:
		using value_type = T;
		using size_type = std::size_t;
		/// <summary>
		/// Iterator class to help iterator through the vector. The iterator is only a forward iterator.
		/// </summary>
		class Iterator
		{
			friend Vector;
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T*;
			using iterator_category = std::bidirectional_iterator_tag;

			/// <summary>
			/// Default constructor for Iterator
			/// </summary>
			Iterator() = default;
			Iterator(const Iterator& other) = default;
			~Iterator() = default;
			Iterator& operator=(const Iterator& other) = default;
			bool operator!=(const Iterator& other) const;
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// Pre-Increments the iterator by one to point to the next thing in the vector. 
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();
			/// <summary>
			/// Post-Increments the iterator by one to point to the next thing in the vector. 
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			Iterator operator++(int);
			/// <summary>
			/// De reference operator for an iterator that returns the type of data it is currently pointing to
			/// </summary>
			/// <returns></returns>
			T& operator*();

			Iterator operator--(int);
			Iterator& operator--();


		private:
			Iterator(const Vector& vector, size_t index);
			const Vector* _owner{ nullptr };
			size_t _index{ 0 };

		};

		/// <summary>
		/// A class that returns a ConstIterator for a vector.
		/// </summary>
		class ConstIterator
		{
			friend Vector;
			
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T*;
			using iterator_category = std::bidirectional_iterator_tag;

			ConstIterator() = default;
			~ConstIterator() = default;
			ConstIterator& operator=(const ConstIterator& other) = default;
			/// <summary>
			/// A ConstIterator constructor that converts an iterator passed in to a ConstIterator
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const Iterator& other);
			bool operator!=(const ConstIterator& other)const;
			bool operator==(const ConstIterator& other) const;
			ConstIterator& operator++();
			ConstIterator operator++(int);
			/// <summary>
			/// De-reference operator that returns a constant reference to the data it is pointing to.
			/// </summary>
			/// <returns></returns>
			const T& operator*() const;

			ConstIterator& operator--();
			ConstIterator operator--(int);

		private:
			ConstIterator(const Vector& vector, size_t index);
			const Vector* _owner{ nullptr };
			size_t _index{ 0 };

		};
		/// <summary>
		/// Default constructor of a vector that creates a vector with capacity 10
		/// </summary>
		/// <param name="Capacity"></param>
		Vector(size_t Capacity = 0);
		Vector(std::initializer_list<T> list);
		~Vector();
		/// <summary>
		/// Default copy constructor for Vector
		/// </summary>
		/// <param name="other"></param>
		Vector(const Vector& other);
		/// <summary>
		/// Default move constructor for Vector
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector(Vector&& other) noexcept;
		/// <summary>
		/// Default copy assignment implementation for vector
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		Vector& operator=(const Vector& rhs);
		/// <summary>
		/// Default move assignment implementation for vector 
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		Vector& operator=(Vector&&) noexcept;
		/// <summary>
		/// Operator[] returns the data of the index passed in as a reference.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& operator[](size_t index);
		/// <summary>
		/// Operator[] returns the data of the index passed in as a const T reference.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		const T& operator[](size_t index)const;
		/// <summary>
		///  returns the data of the index passed in as a reference.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& At(size_t index);
		/// <summary>
		///  returns the data of the index passed in as a const T reference.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		const T& At(size_t index) const;
		/// <summary>
		/// Deletes the item at the end of the vector
		/// </summary>
		void PopBack();
		/// <summary>
		/// Checks if the vector is empty , i.e. if size is 0
		/// </summary>
		/// <returns></returns>
		bool isEmpty() const;
		/// <summary>
		/// Returns the front of the Vector as a T reference
		/// </summary>
		/// <returns></returns>
		T& Front();
		/// <summary>
		/// Returns the front of the Vector as a const T reference
		/// </summary>
		/// <returns></returns>
		const T& Front() const;
		/// <summary>
		/// Returns the last element in the vector
		/// </summary>
		/// <returns></returns>
		T& Back();
		/// <summary>
		/// Reserves a capacity for the given vector, the capacity passed in cannot be smaller than existing capaciity i.e. not possible to shrink the vector
		/// </summary>
		/// <param name="capacity"></param>
		void Reserve(size_t capacity);
		const T& Back() const;
		/// <summary>
		/// Returns the size of the Vector
		/// </summary>
		/// <returns></returns>
		size_t Size() const;
		/// <summary>
		/// Returns the capacity of the vector
		/// </summary>
		/// <returns></returns>
		size_t Capacity() const;
		/// <summary>
		/// Adds the element to the end of the vector
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Iterator PushBack(const T& value);
		/// <summary>
		/// Removes all data from the vector, DOES NOT reduce capacity
		/// </summary>
		void Clear();
		/// <summary>
		/// Finds an element in the vector and returns an iterator pointing to that element 
		/// </summary>
		/// <param name="value"></param>
		/// <param name="equalityFunctor"></param>
		/// <returns></returns>
		Iterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>());
		/// <summary>
		/// Finds an element in the vector and returns a Const-iterator pointing to that element 
		/// </summary>
		/// <param name="value"></param>
		/// <param name="equalityFunctor"></param>
		/// <returns></returns>
		ConstIterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunctor = std::equal_to<T>()) const;
		/// <summary>
		/// Returns an iterator pointing to the beginning of the Vector 
		/// </summary>
		/// <returns></returns>
		Iterator begin();
		/// <summary>
		/// Returns an iterator pointing to the end of the Vector 
		/// </summary>
		/// <returns></returns>
		Iterator end();
		
		/// <summary>
		/// Removes the first element that matches the value passed in from the vector
		/// </summary>
		/// <param name="value"></param>
		void Remove(const T& value);
		/// <summary>
		/// Removes all the elements between the two iterators passed in
		/// </summary>
		/// <param name="it1"></param>
		/// <param name="it2"></param>
		void Remove(const Iterator& it1, const Iterator& it2);

		void RemoveAt(std::size_t index);
		ConstIterator begin()const;
		ConstIterator end()const;
		ConstIterator cbegin() const;
		ConstIterator cend() const;
		void Resize(size_t size);

		void ShrinkToFit();
		

	};


}

#include "Vector.inl"