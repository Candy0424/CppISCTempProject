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
		//�׽�Ʈ�Դϴ�.
	}
}

void Core::Init()
{
	SetConsoleSettings(800, 500, false, L"Ⱦ ��ũ�� �������");
}

void Core::Update()
{
}

void Core::Render()
{
}
