
#include "SList.h"
namespace GameEngine
{

	template <typename AbstractFactory>
	SList<AbstractFactory>::SList() : _size(0), _front(nullptr), _back(nullptr)
	{
	}
	template <typename AbstractFactory>
	SList<AbstractFactory>::~SList()
	{
		Clear();
	}
	template <typename AbstractFactory>
	SList<AbstractFactory>::Iterator::Iterator(const SList& list, Node* Node) : _owner(&list), _node(Node)
	{
	}
	template <typename AbstractFactory>
	SList<AbstractFactory>::ConstIterator::ConstIterator(const SList& list, Node* Node) : _owner{ &list }, _node(Node)
	{
	}
	template <typename AbstractFactory>
	SList<AbstractFactory>::Node::Node(const AbstractFactory& Data, Node* Next) : data(Data), next(Next)
	{
	}

	template<typename AbstractFactory>
	SList<AbstractFactory>::SList(const SList& other)
	{
		Node* currentOther = other._front;
		while (currentOther != nullptr)
		{
			PushBack(currentOther->data);
			currentOther = currentOther->next;
		}
	}

	template<typename AbstractFactory>
	SList<AbstractFactory>& SList<AbstractFactory>::operator=(SList& other)
	{
		if (this != &other)
		{
			Clear();
			Node* rhsFront;
			rhsFront = other._front;
			while (rhsFront != nullptr)
			{
				PushBack(rhsFront->data);
				rhsFront = rhsFront->next;
			}
			delete(rhsFront);
		}
		return *this;
	}

	template<typename AbstractFactory>
	bool SList<AbstractFactory>::operator==(const SList& rhs)const
	{
		Node* rhsFront;
		Node* lhsFront;
		if (rhs._front == nullptr)
		{
			if (_front == nullptr)
			{
				return true;
			}
			return false;
		}
		if (_size == rhs._size)
		{
			lhsFront = _front;
			rhsFront = rhs._front;
			while (lhsFront != nullptr)
			{
				if (lhsFront->data == rhsFront->data)
				{
					lhsFront = lhsFront->next;
					rhsFront = rhsFront->next;
					continue;
				}
				else
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename AbstractFactory>
	typename SList<AbstractFactory>::Iterator SList<AbstractFactory>::PushFront(const AbstractFactory& data)
	{
		_front = new Node(data, _front);

		if (_size == 0)
		{
			_back = _front;
		}
		_size++;

		return  Iterator{ *this, _front };


	}

	template <typename AbstractFactory>
	typename SList<AbstractFactory>::Iterator SList<AbstractFactory>::PushBack(const AbstractFactory& data)
	{
		Node* nodeToAdd = new Node(data, nullptr);
		if (_size == 0)
		{
			_front = nodeToAdd;
		}
		else
		{
			_back->next = nodeToAdd;


		}
		_back = nodeToAdd;
		_size++;
		return Iterator(*this, _back);
	}
	template <typename AbstractFactory>
	void SList<AbstractFactory>::PopFront()
	{
		Node* temp;


		_size--;

		temp = _front;
		if (_front->next == nullptr)
		{
			_front = nullptr;
			_back = nullptr;
		}
		else
		{
			_front = _front->next;
		}
		delete(temp);



	}
	template <typename AbstractFactory>
	void SList<AbstractFactory>::PopBack()
	{
		Node* temp;
		_size--;
		temp = _front;
		if (temp->next == nullptr)
		{
			_front = nullptr;
			_back = nullptr;
			delete(temp);

		}
		else
		{
			while (temp->next->next != nullptr)
			{
				temp = temp->next;
			}
			delete(temp->next);
			temp->next = nullptr;
			_back = temp;
		}
	}

	template <typename AbstractFactory>
	inline const std::size_t SList<AbstractFactory>::Size() const
	{
		return _size;
	}

	template <typename AbstractFactory>
	inline  bool SList<AbstractFactory>::IsEmpty()
	{
		return _size == 0;
	}
	template <typename AbstractFactory>
	const AbstractFactory& SList<AbstractFactory>::Front() const
	{

		if (_front == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		return _front->data;
	}
	template <typename AbstractFactory>
	AbstractFactory& SList<AbstractFactory>::Front()
	{
		if (_front == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		return _front->data;
	}

	template <typename AbstractFactory>
	const AbstractFactory& SList<AbstractFactory>::Back() const
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		return _back->data;
	}
	template <typename AbstractFactory>
	AbstractFactory& SList<AbstractFactory>::Back()
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		return _back->data;
	}

	template <typename AbstractFactory>
	void SList<AbstractFactory>::Clear()
	{
		if (_front == nullptr)
		{
			return;
		}
		Node* nextNode;
		Node* current;
		current = _front;
		while (current != nullptr)
		{
			nextNode = current->next;
			delete(current);
			current = nextNode;

		}
		_size = 0;
		_front = nullptr;
		_back = nullptr;

	}

	template<typename AbstractFactory>
	typename inline SList<AbstractFactory>::Iterator SList<AbstractFactory>::begin()
	{
		return  Iterator{ *this, _front };
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::Iterator SList<AbstractFactory>::end()
	{

		return Iterator{ *this };
	}

	template<typename AbstractFactory>
	typename inline SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::begin() const
	{
		return   ConstIterator{ *this,_front };
	}
	template<typename AbstractFactory>
	typename SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::cbegin() const
	{
		return  ConstIterator{ *this,_front };
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::cend() const
	{
		return  ConstIterator{ *this };
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::end() const
	{
		return ConstIterator{ *this };
	}
	template<typename AbstractFactory>
	inline bool SList<AbstractFactory>::Iterator::operator!=(const Iterator& other) const
	{
		return (_owner != other._owner || _node != other._node);
	}

	template<typename AbstractFactory>
	inline bool SList<AbstractFactory>::Iterator::operator==(const Iterator& other) const
	{
		return !operator!=(other);
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::Iterator& SList<AbstractFactory>::Iterator::operator++()
	{
		if (_owner == nullptr || _node == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		if (_node != nullptr)
		{
			_node = _node->next;
		}
		return *this;
	}

	template<typename AbstractFactory>
	typename inline SList<AbstractFactory>::Iterator SList<AbstractFactory>::Iterator::operator++(int)
	{
		Iterator copy = *this;
		operator++();
		return copy;
	}

	template<typename AbstractFactory>
	inline AbstractFactory& SList<AbstractFactory>::Iterator::operator*()
	{
		if (_owner == nullptr || _node == nullptr)
		{
			throw std::runtime_error("De referencing null pointer");
		}
		return (_node->data);
	}
	template<typename AbstractFactory>
	inline const AbstractFactory& SList<AbstractFactory>::ConstIterator::operator*() const
	{
		if (_owner == nullptr || _node == nullptr)
		{
			throw std::runtime_error("De referencing null pointer");

		}
		return (_node->data);
	}


	template<typename AbstractFactory>
	inline bool SList<AbstractFactory>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		if (_owner != other._owner)
		{
			return true;
		}
		else
		{
			return !(_node == other._node);
		}
	}

	template<typename AbstractFactory>
	inline bool SList<AbstractFactory>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !operator!=(other);
	}
	template<typename AbstractFactory>
	typename inline SList<AbstractFactory>::ConstIterator& SList<AbstractFactory>::ConstIterator::operator++()
	{
		if (_owner == nullptr || _node == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		else
		{
			_node = _node->next;

		}
		return *this;
	}

	template<typename AbstractFactory>
	typename inline SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::ConstIterator::operator++(int)
	{
		ConstIterator copy = *this;
		operator++();
		return copy;
	}

	template<typename AbstractFactory>
	SList<AbstractFactory>::ConstIterator::ConstIterator(const Iterator& other) : _owner(other._owner), _node(other._node)
	{
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::Iterator SList<AbstractFactory>::Find(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor)
	{
		Iterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
			{
				break;
			}
		}
		return it;
	}

	template<typename AbstractFactory>
	typename SList<AbstractFactory>::ConstIterator SList<AbstractFactory>::Find(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor) const
	{
		ConstIterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
			{
				break;
			}
		}
		return it;
	}
	template<typename AbstractFactory>
	void SList<AbstractFactory>::InsertAfter(const Iterator& it, const AbstractFactory& value)
	{
		if (it._owner != this)
		{
			throw std::runtime_error("Wrong iterator passed, points to a different list");
		}
		if (_size == 0 || (it._node == _back))
		{
			PushBack(value);
		}

		else
		{
			Node* dataToAdd = new Node(value, nullptr);
			Node* temp;
			temp = it._node->next;
			it._node->next = dataToAdd;
			dataToAdd->next = temp;
			_size++;
		}


	}

	template <typename AbstractFactory>
	void SList<AbstractFactory>::Remove(const AbstractFactory& value, std::function<bool(const AbstractFactory&, const AbstractFactory&)> equalityFunctor)
	{
		Iterator it = Find(value);

		if (it._node == nullptr)
		{
			return;
		}
		else
		{
			if (it == begin())
			{
				PopFront();
			}
			else if (it._node == _back)
			{
				PopBack();
			}
			else
			{
				Iterator it1;
				Node* temp = it._node->next;
				for (it1 = begin(); it1 != end(); ++it1)
				{
					if (equalityFunctor(it1._node->next->data, value))
					{
						break;
					}
				}
				it1._node->next = temp;
				delete(it._node);
				_size--;
			}

		}
	}

	template<typename AbstractFactory>
	inline bool SList<AbstractFactory>::IsEmpty() const
	{
		return _size == 0;
	}


}
