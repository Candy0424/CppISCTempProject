#include "Score.h"

void Score::Init()
{
	currentScore = 0;
	scoreContainer.clear();
}

void Score::AddScore(const JudgeResult& jr)
{
	switch (jr)
	{
	case JudgeResult::PERFECT:
		currentScore += 10000;
		break;
	case JudgeResult::GOOD:
		currentScore += 8000;
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
	if (jr != JudgeResult::NONE)
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

bool Score::PerfectCheck()
{
	bool perfect = true;
	for (auto item : scoreContainer)
	{
		if (item.second != 0 && item.first != JudgeResult::PERFECT)
			perfect = false;
	}

	return perfect;
}

bool Score::FullComboCheck()
{
	bool fullCombo = true;

	for (auto item : scoreContainer)
	{
		if (item.second != 0 && ((item.first != JudgeResult::PERFECT) && (item.first != JudgeResult::GOOD)))
			fullCombo = false;
	}

	return fullCombo;
}
