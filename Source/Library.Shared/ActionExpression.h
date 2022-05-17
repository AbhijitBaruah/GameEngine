#pragma once
#include "ActionList.h"
namespace GameEngine
{
	class ActionExpression :public ActionList
	{
		RTTI_DECLARATIONS(ActionExpression);
	public:
		ActionExpression();
		void Update(const GameTime&)override;

		Vector<std::string> TokenizeString(std::string& stringToTokenize);
		std::string expression;
		static Vector<Signature> Signatures();
		Vector<std::string> ConvertRPN(std::string algebraicExpression);
		double Evaluate(Vector<std::string> infixExpr);
		bool IsNumber(const std::string& token);
		bool IsOperator(const std::string& token);
		bool IsOpenBracket(const std::string& token);
		bool IsClosedBracket(const std::string& token);
		bool IsBracket(const std::string& token);
	private:
		bool _parentFound{ false };
		Scope* _parentScope{ this };
		enum  class OrderOfEvaluation { LeftToRight, RightToLeft };
		HashMap<std::string, std::pair<std::int32_t, OrderOfEvaluation>> _operatorsPrecedenceMap;



	};


	ConcreteFactory(ActionExpression, Scope)

}
