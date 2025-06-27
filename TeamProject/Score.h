#pragma once
#include <unordered_map>
#include "Enums.h"
#include <iomanip>

class Score
{
	std::unordered_map<JudgeResult, unsigned int> scoreContainer;
private:
	double currentScore = 0;
public:
	void Init();
	double GetCurrentScore() { return currentScore; }
	unsigned int GetJudgeCount(const JudgeResult& jr) {return scoreContainer[jr];}

	void AddScore(const JudgeResult& jr);
	void RecordJudge(JudgeResult& jr);
	double CalculateRate();
	bool PerfectCheck();
	bool FullComboCheck();
};

