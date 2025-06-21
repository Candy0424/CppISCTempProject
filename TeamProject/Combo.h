#pragma once
#include "Defines.h"

class Combo
{
public:
	static Combo* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Combo;
		}
		return instance;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);

	}
private:
	Combo();
	static Combo* instance;

	int currentCombo = 0;
	
};

