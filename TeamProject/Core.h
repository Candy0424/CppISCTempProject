#pragma once
#include"NodeScroll.h"
class Core
{
public:
	void Run();

	Core();
	~Core();
private:
	void Init();
	void Update();
	void Render();

	NodeManager* nodeScroll;
	float currentTime;
};
