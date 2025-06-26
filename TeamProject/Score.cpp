#include "Score.h"

void Score::AddScore(const JudgeResult& jr)
{
	switch (jr)
	{
	case JudgeResult::PERFECT:
		currentScore += 10000;
		break;
	case JudgeResult::GOOD:
		currentScore += 5000;
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
	return 1.2;
}
