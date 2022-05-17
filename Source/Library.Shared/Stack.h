#pragma once
#include "SList.h"

namespace GameEngine
{
	template <typename AbstractFactory>
	class Stack final
	{
	public:
	
		void Push(AbstractFactory&& value);
		void Pop();
		AbstractFactory& Top();
		const AbstractFactory& Top() const;

		std::size_t Size() const;
		bool IsEmpty() const;

		void Clear();

	private:
		SList<AbstractFactory> _list;
	};
}

#include "Stack.inl"