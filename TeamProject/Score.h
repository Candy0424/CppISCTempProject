#pragma once
#include <unordered_map>
#include "Enums.h"

class Score
{
	std::unordered_map<JudgeResult, unsigned int> scoreContainer;
private:
	unsigned int currentScore = 0;
public:
	unsigned int GetCurrentScore() { return currentScore; }
	void AddScore(const JudgeResult& jr);
	void RecordJudge(JudgeResult& jr);
	double CalculateRate();
};

