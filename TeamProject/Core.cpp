#include "Core.h"
#include "Console.h"

void Core::Run()
{
	Init();
	while (true)
	{
		Update();
		Render();
		FrameSync(60);
	}
}

void Core::Init()
{
	SetConsoleSettings(800, 500, false, L"È¾ ½ºÅ©·Ñ ¸®µë°ÔÀÓ");
	SetCursorVisual(true, 1);
	
}

void Core::Update()
{
	currentTime += 0.016f;
	nodeScroll->Update(currentTime);
}

void Core::Render()
{
	system("cls");
	nodeScroll->Render();
}

Core::Core()
{
	nodeScroll = new NodeManager(100, 4, 0, 32);
	nodeScroll->LoadChart("Chart.txt");
	currentTime = 0.0f;
}

Core::~Core()
{
	delete nodeScroll;
}
