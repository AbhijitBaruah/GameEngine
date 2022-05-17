#pragma once
#include "Vector.h"
#include "SList.h"
#include "DefaultHash.h"
#include <functional>
#include <cstddef>
#include <utility>

namespace GameEngine
{
	/// <summary>
	/// HashMap implementation by using a chaining for collision handling
	/// </summary>
	/// <typeparam name="TData"></typeparam>
	/// <typeparam name="TKey"></typeparam>
	template <typename TKey, typename TData>
	class HashMap final
	{
	public:
		using value_type = std::pair<TKey, TData>;
		using size_type = std::size_t;
		using PairType = std::pair<const TKey, TData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;
		/// <summary>
		/// Iterator class for a hashMap that points to the correct node in the list where the key,Value pair exists.
		/// </summary>
		class Iterator
		{
			friend HashMap;
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = std::pair<TKey, TData>;
			using reference = TKey&;
			using pointer = TKey*;
			using iterator_category = std::forward_iterator_tag;
			/// <summary>
			/// Default constructor
			/// </summary>
			Iterator() = default;
			~Iterator() = default;
			/// <summary>
			/// Default copy constructor 
			/// </summary>
			/// <param name="other"></param>
			Iterator(const Iterator& other) = default;
			/// <summary>
			/// Default assignment operator 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			Iterator& operator=(const Iterator& other) = default;
			/// <summary>
			/// Equality comparison which compares two iterators to see if they are pointing to the same node in the same list under the same bucket
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const Iterator& other) const;
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// Increment operator which iterates through the hashmap to find the next valid Key,Value pair node
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();
			Iterator operator++(int);
			/// <summary>
			/// De-reference operator which returns a Key value pair the iterator is currently pointing to
			/// </summary>
			/// <returns></returns>
			std::pair<const TKey, TData>& operator*();
			/// <summary>
			/// De-reference operator which returns a pointer Key value pair the iterator is currently pointing to
			/// </summary>
			/// <returns></returns>
			std::pair<const TKey, TData>* operator->();

		private:
			/// <summary>
			/// Constructor override for Iterator which stores the bucket number its pointing to as its index, a Slist iterator pointing to a specific node and the hashmap its associated to.
			/// </summary>
			/// <param name="owner"></param>
			/// <param name="index"></param>
			/// <param name="node"></param>
			Iterator(HashMap& owner, size_t index = 0, typename ChainType::Iterator node = typename ChainType::Iterator::Iterator());
			size_t _index{ 0 };
			typename ChainType::Iterator _node;;
			HashMap* _owner{ nullptr };


		};
		/// <summary>
		/// ConstIterator class for a hashMap that points to the correct node in the list where the key,Value pair exists.
		/// </summary>
		class ConstIterator
		{
			friend HashMap;
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = std::pair<TKey, TData>;
			using reference = TKey&;
			using pointer = TKey*;
			using iterator_category = std::forward_iterator_tag;
			/// <summary>
			/// Default constructor
			/// </summary>
			ConstIterator() = default;
			~ConstIterator() = default;
			/// <summary>
	     	/// Default copy constructor 
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const ConstIterator& other) = default;
			/// <summary>
			/// Default assignment operator 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			ConstIterator& operator=(const ConstIterator& other) = default;
			/// <summary>
			/// Equality comparison which compares two ConstIterators to see if they are pointing to the same node in the same list under the same bucket
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const ConstIterator& other) const;
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// Increment operator which iterates through the hashmap to find the next valid Key,Value pair node
			/// </summary>
			/// <returns></returns>
			ConstIterator& operator++();
			ConstIterator operator++(int);
			/// <summary>
			/// Converts an iterator passed in to a ConstIterator
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const Iterator& other);
			/// <summary>
			/// De-reference operator which returns a Key value pair the ConstIterator is currently pointing to
			/// </summary>
			/// <returns></returns>
			const std::pair<const TKey, TData>& operator*() const;
			/// <summary>
			/// De-reference operator which returns a pointer to a Key value pair the ConstIterator is currently pointing to
			/// </summary>
			/// <returns></returns>
			const std::pair<const TKey, TData>* operator->() const;

		private:
			/// <summary>
			/// Constructor override for ConstIterator which stores the bucket number its pointing to as its index, a Slist iterator pointing to a specific node and the hashmap its associated to.
			/// </summary>
			/// <param name="owner"></param>
			/// <param name="index"></param>
			/// <param name="node"></param>
			ConstIterator(const HashMap& owner, size_t index = 0, typename ChainType::ConstIterator node = typename ChainType::ConstIterator::ConstIterator());
			size_t _index{ 0 };
			typename ChainType::ConstIterator _node{ typename ChainType::ConstIterator::ConstIterator() };
			const HashMap* _owner{ nullptr };


		};
		/// <summary>
		/// constructor for hashmap which takes in the number of buckets , a hashFunction and an equality function both of which are defaulted
		/// </summary>
		/// <param name="Size"></param>
		/// <param name="defaultHash"></param>
		/// <param name="equalityFunctor"></param>
		HashMap(size_t Size = 11, std::function<size_t(const TKey&)>defaultHash = DefaultHash<TKey>{}, std::function<bool(const TKey&, const TKey&)> equalityFunctor = std::equal_to<TKey>());
		~HashMap() = default;
		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other"></param>
		HashMap(const HashMap& other) = default;
		/// <summary>
		/// Default copy assignment for hashMap
		/// </summary>
		/// <param name="other"></param>
		HashMap(HashMap&& other) = default;
		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		HashMap& operator=(const HashMap& other) = default;
		/// <summary>
		/// Default move assignment
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		HashMap& operator=(HashMap&& other) = default;
		/// <summary>
		/// Inserts a Key value pair into the hashmap by hashing the key using a hash functor and returns a std::pair of an terator pointing to the node containing the key and a bool if the pair passed in was inserted or not, as if there is an existing key, the pair passed in wont be insered
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		std::pair<Iterator, bool> Insert(const PairType&);
		/// <summary>
		/// operator[], which takes a “key” argument of the appropriate type and which returns a reference to the TData part. Create an entry with the associated key, if one isn’t already in the hash map.
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		TData& operator[](const TKey& key);
		/// <summary>
		/// Returns an iterator pointing to the first node containing a key value pair in the map
		/// </summary>
		/// <returns></returns>
		Iterator begin();
		/// <summary>
		/// Returns an iterator with index as one after bucketSize, the Slist iterator pointing to the end of the list.
		/// </summary>
		/// <returns></returns>
		Iterator end();
		/// <summary>
		/// Returns an ConstIterator pointing to the first node containing a key value pair in the map
		/// </summary>
		/// <returns></returns>
		ConstIterator begin()const;
		/// <summary>
		/// Returns an ConstIterator with index as one after bucketSize, the Slist ConstIterator pointing to the end of the list.
		/// </summary>
		/// <returns></returns>
		ConstIterator end()const;
		/// <summary>
		/// Returns an ConstIterator pointing to the first node containing a key value pair in the map
		/// </summary>
		/// <returns></returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// Returns an ConstIterator with index as one after bucketSize, the Slist ConstIterator pointing to the end of the list.
		/// </summary>
		/// <returns></returns>
		ConstIterator cend() const;
		/// <summary>
		/// returns a TData reference at the given key 
		/// /// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		TData& At(const TKey& key);
		/// <summary>
		/// returns a const TData reference at the given key 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		const TData& At(const TKey& key) const;
		/// <summary>
		/// Returns the number of elements in the hashMap
		/// </summary>
		/// <returns></returns>
		size_t Size() const;
		/// <summary>
		/// returns a Boolean indicating the presence of a key within the hash map
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool ContainsKey(const TKey& key) const;
		/// <summary>
		/// returns a Boolean indicating the presence of a key within the hash map and provides an out parameter to modify the data the passed in key refers to
		/// </summary>
		/// <param name="key"></param>
		/// <param name="out"></param>
		/// <returns></returns>
		bool ContainsKey(const TKey& key, TData*& out);
		/// <summary>
		///  which takes a “key” argument of the appropriate type and returns an iterator pointing to the node IF the key was found, which is indicated by the bool
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<Iterator, bool> Find(const TKey& key);
		/// <summary>
		///  which takes a “key” argument of the appropriate type and returns an ConstIterator pointing to the node IF the key was found, which is indicated by the bool
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<ConstIterator, bool> Find(const TKey& key) const;
		/// <summary>
		/// empties the table and deletes any memory it allocated.
		/// </summary>
		void Clear();
		/// <summary>
		/// which takes a “key” argument (as above) and which returns nothing. It should remove the matching entry, if it exists, otherwise it should do nothing.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool Remove(const TKey& value);
		size_t LoadFactor();
		std::size_t  Capacity() const;
	
		void ReHash(size_t newCapacity);
	private:
		BucketType _hashMap;
		size_t _size;
		std::function<size_t(TKey)> _hash{ DefaultHash<TKey>{} };
		std::function<bool(const TKey&, const TKey&)> _equality{ std::equal_to<TKey>() };
		
	};

}

#include "HashMap.inl"