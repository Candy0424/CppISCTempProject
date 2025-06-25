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
	void AddScore(unsigned int addScore);
	void RecordJudge(JudgeResult& jr);
	void CalculateRate();
};

