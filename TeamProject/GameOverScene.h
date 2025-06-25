#pragma once
#include "Player.h"
class GameOverScene
{
private:
	bool endAnimation = false;

	void EnterAnimation();
	bool SelectInput();
	void GameOverText();
	void SelectText();

	POS previousPos;
	int nextData = 0;

public:
	void Init();
	void Update(Scene& currentScene);
	void Render();
};

