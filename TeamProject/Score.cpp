#include "Score.h"

void Score::Init()
{
	currentScore = 0;
}

void Score::AddScore(const JudgeResult& jr)
{
	switch (jr)
	{
	case JudgeResult::PERFECT:
		currentScore += 10000;
		break;
	case JudgeResult::GOOD:
		currentScore += 7000;
		break;
	case JudgeResult::BAD:
		currentScore += 2000;
		break;
	default:
		break;
	}
}

void Score::RecordJudge(JudgeResult& jr)
{
	scoreContainer[jr]++;
}

double Score::CalculateRate()
{
	double maxScore = 0;
	double rate = 0;

	for (auto item : scoreContainer)
		maxScore += item.second;

	maxScore *= 10000;

	if (maxScore > 0)
		rate = (currentScore / maxScore) * 100;

	return rate;
}
