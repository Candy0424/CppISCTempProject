#include "Combo.h"
void Combo::ClearCombo()
{
	currentCombo = 0;
}

void Combo::AddCombo(unsigned int combo)
{
	currentCombo += combo;
}
