#include "Score.h"

void Score::AddScore(unsigned int addScore)
{
	currentScore += addScore;
}

void Score::RecordJudge(JudgeResult& jr)
{
	scoreContainer[jr]++;
}

void Score::CalculateRate()
{
}
