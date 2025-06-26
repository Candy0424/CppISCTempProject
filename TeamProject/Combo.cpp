#include "Combo.h"
void Combo::ClearCombo()
{
	while (currentCombo >= 10)
	{
		currentClearNum++;
		currentCombo /= 10;
	}


	currentCombo = 0;
}

void Combo::ClearNum()
{
	currentClearNum = 0;
}

void Combo::AddCombo(unsigned int combo)
{
	currentCombo += combo;
	fiverCombo += combo;
}

bool Combo::GetFiver()
{
	return isFiver;
}

void Combo::SetFiver(bool value)
{
	isFiver = value;
}

void Combo::FiverCheck()
{
	if (isFiver) return;

	isFiver = fiverCombo >= 20;
}
