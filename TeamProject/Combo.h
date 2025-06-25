#pragma once
#include "Defines.h"

class Combo
{
private:
	unsigned int currentCombo = 0;

public:
	unsigned int GetCurrentCombo() { return currentCombo;	}
	void ClearCombo();
	void AddCombo(unsigned int combo);
};