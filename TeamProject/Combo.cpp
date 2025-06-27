#include "Combo.h"

void Combo::InitCombo()
{
	currentCombo = 0;
	currentClearNum = 0;
	maxCombo = 0;
	fiverCombo = 0;
	fiverStartTime = .0f;
	isFiver = false;
}

void Combo::ClearCombo()
{
	if (currentCombo > maxCombo)
	{
		maxCombo = currentCombo;
	}

	while (currentCombo >= 10)
	{
		currentClearNum++;
		currentCombo /= 10;
	}


	currentCombo = 0;
	fiverCombo = 0;
}

void Combo::ClearNum()
{
	currentClearNum = 0;
}

void Combo::AddCombo(unsigned int combo)
{

	currentCombo += combo;

	if (!isFiver)
		fiverCombo += combo;

	if (currentCombo > maxCombo)
	{
		maxCombo = currentCombo;
	}
}

void Combo::SetFiver(bool value)
{
	isFiver = value;
}

void Combo::FiverCheck(float& startTime)
{
	if (isFiver)
	{
		fiverCombo = 0;
		return;
	}

	isFiver = fiverCombo >= fiverGage;
	fiverStartTime = startTime;
}

void Combo::FiverCool(float& curTime)
{
	if (fiverStartTime + fiverDuration < curTime)
		isFiver = false;
}
