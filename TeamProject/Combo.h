#pragma once
#include "Defines.h"

class Combo
{
private:
	unsigned int currentCombo = 0;
	unsigned int currentClearNum = 0;
	bool isFiver;
	unsigned int fiverCombo = 0;

public:
	unsigned int GetCurrentCombo() { return currentCombo; }
	unsigned int GetCrrentClearNum() { return currentClearNum; }
	void ClearCombo();
	void ClearNum();
	void AddCombo(unsigned int combo);
	bool GetFiver() { return isFiver; }
	void SetFiver(bool value);
	void FiverCheck();
};