#pragma once

#include <cstddef>
#include <string>

namespace GameEngine
{
	class RTTI
	{
	public:
		using IdType = std::size_t;

		RTTI() = default;
		RTTI(const RTTI&) = default;
		RTTI& operator=(const RTTI&) = default;
		RTTI(RTTI&&) noexcept = default;
		RTTI& operator=(RTTI&&) noexcept = default;
		virtual ~RTTI() = default;

		virtual IdType TypeIdInstance() const = 0;
		virtual bool Is(IdType) const;

		template <typename AbstractFactory>
		AbstractFactory* As();

		template <typename AbstractFactory>
		const AbstractFactory* As() const;

		virtual std::string ToString() const;
		virtual bool Equals(const RTTI* rhs) const;
	};
}

#define RTTI_DECLARATIONS(Type)																							\
	public:																												\
		static GameEngine::RTTI::IdType TypeIdClass();																\
		GameEngine::RTTI::IdType TypeIdInstance() const override;													\
		bool Is(GameEngine::RTTI::IdType id) const override;														\
	private:																											\
		static const GameEngine::RTTI::IdType _typeId

#define RTTI_DEFINITIONS(Type, ParentType)																				\
	GameEngine::RTTI::IdType Type::TypeIdClass() { return _typeId; }												\
	GameEngine::RTTI::IdType Type::TypeIdInstance() const { return TypeIdClass(); }									\
	bool Type::Is(GameEngine::RTTI::IdType id) const { return (id == _typeId ? true : ParentType::Is(id)); }		\
	const GameEngine::RTTI::IdType Type::_typeId = reinterpret_cast<GameEngine::RTTI::IdType>(&Type::_typeId);	\

#include "RTTI.inl"