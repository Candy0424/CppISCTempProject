#include "Core.h"
#include "Console.h"

void Core::Run()
{
	Init();
	while (true)
	{
		Update();
		Render();
		// FrameSync
		//테스트입니다.
	}
}

void Core::Init()
{
	SetConsoleSettings(800, 500, false, L"횡 스크롤 리듬게임");
}

void Core::Update()
{
}

void Core::Render()
{
}
