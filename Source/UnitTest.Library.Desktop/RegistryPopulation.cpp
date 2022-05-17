#include "pch.h"
#include "Scope.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "TypeRegistry.h"
#include "Attribute.h"
#include "AttributedFoo.h"
#include "ChildAttributedFoo.h"
#include "FooFailClass.h"
#include "GameObject.h"
#include "Avatar.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionRemoveAction.h"
#include "ActionIncrement.h"
#include "ActionListIf.h"
#include "ActionExpression.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
		TEST_MODULE_INITIALIZE(RegistryPopulationTestsa)
		{
			TypeRegistry::getInstance()->RegisterClass<AttributedFoo, Attributed>();
			TypeRegistry::getInstance()->RegisterClass<ChildAttributedFoo, AttributedFoo>();
			TypeRegistry::getInstance()->RegisterClass<FooFailClass, AttributedFoo>();
			TypeRegistry::getInstance()->RegisterClass<GameObject, Attributed>();
			TypeRegistry::getInstance()->RegisterClass<Avatar, GameObject>();
			TypeRegistry::getInstance()->RegisterClass<Action, Attributed>();
			TypeRegistry::getInstance()->RegisterClass<ActionList, Action > ();
			TypeRegistry::getInstance()->RegisterClass<ActionCreateAction, Action>();
			TypeRegistry::getInstance()->RegisterClass<ActionRemoveAction, Action>();
			TypeRegistry::getInstance()->RegisterClass<ActionIncrement, Action>();
			TypeRegistry::getInstance()->RegisterClass<ActionListIf, ActionList>();
			TypeRegistry::getInstance()->RegisterClass<ActionExpression, ActionList>();
		}
		


		
		TEST_MODULE_CLEANUP(RegistryPopulationCleanupas)
		{

		}


}