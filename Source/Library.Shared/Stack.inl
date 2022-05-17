
namespace GameEngine
{

	template <typename AbstractFactory>
	inline void Stack<AbstractFactory>::Push(AbstractFactory&& value)
	{
		_list.PushFront(std::move(value));
	}

	template <typename AbstractFactory>
	inline void Stack<AbstractFactory>::Pop()
	{
		_list.PopFront();
	}

	template <typename AbstractFactory>
	inline AbstractFactory& Stack<AbstractFactory>::Top()
	{
		return _list.Front();
	}

	template <typename AbstractFactory>
	inline const AbstractFactory& Stack<AbstractFactory>::Top() const
	{
		return _list.Front();
	}

	template <typename AbstractFactory>
	inline std::size_t Stack<AbstractFactory>::Size() const
	{
		return _list.Size();
	}

	template <typename AbstractFactory>
	inline bool Stack<AbstractFactory>::IsEmpty() const
	{
		return _list.IsEmpty();
	}

	template <typename AbstractFactory>
	inline void Stack<AbstractFactory>::Clear()
	{
		return _list.Clear();
	}
}
