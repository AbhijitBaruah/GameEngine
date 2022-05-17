#include "pch.h"
#include "TypeRegistry.h"
namespace GameEngine
{

	TypeRegistry* TypeRegistry::_instance = 0;

	TypeRegistry* TypeRegistry::getInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new TypeRegistry();
		}
		return _instance;
	}
}