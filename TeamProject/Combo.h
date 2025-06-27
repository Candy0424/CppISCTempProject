#pragma once
#include "Defines.h"

class Combo
{
private:
	unsigned int currentCombo = 0;
	unsigned int maxCombo = 0;
	unsigned int currentClearNum = 0;
	bool isFiver;
	unsigned int fiverCombo = 0;
	unsigned int fiverGage = 30;
	float fiverDuration = 10.0f;
	float fiverStartTime = .0f;
	

public:
	unsigned int GetCurrentCombo() { return currentCombo; }
	unsigned int GetMaxCombo() { return maxCombo; }
	unsigned int GetCrrentClearNum() { return currentClearNum; }
	unsigned int GetMaxFiverGage() { return fiverGage; }
	unsigned int GetCurrentFiverGage() { return fiverCombo; }
	void ClearCombo();
	void ClearNum();
	void AddCombo(unsigned int combo);
	bool GetFiver() { return isFiver; }
	void SetFiver(bool value);
	void FiverCheck(float& startTime);
	void FiverCool(float& curTime);
};