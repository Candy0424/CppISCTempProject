#include "GameOverScene.h"
#include "Console.h"
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
void GameOverScene::Init()
{
	EnterAnimation();
}

void GameOverScene::Update(Scene& currentScene)
{
	bool isSelect = SelectInput();

	if (isSelect)
	{
		switch (nextData)
		{
		case 1:
			currentScene = Scene::QUIT;
			break;
		case 2:
			currentScene = Scene::SONG_SELECT;
			break;
		}
	}
	
	
}

void GameOverScene::Render()
{
	if (endAnimation)
	{
		GameOverText();
		SelectText();
	}
}

void GameOverScene::EnterAnimation()
{
	COORD res = GetConsoleResolution();
	IsGotoxy(0, 0);
	int previous = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = res.Y - 1; i >= 0; --i)
	{
		Gotoxy(0, i);
		for (int j = 0; j < res.X; ++j)
		{
			wcout << L"█";
		}
		Sleep(15);
	}
	_setmode(_fileno(stdout), previous);
	system("cls");
	endAnimation = true;
}

bool GameOverScene::SelectInput()
{
	bool left = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	bool select = GetAsyncKeyState(VK_RETURN) & 0x8000;

	COORD res = GetConsoleResolution();
	if (left || right)
	{
		IsGotoxy(previousPos.x, previousPos.y);
		cout << ' ';
		if (left)
		{
		
			IsGotoxy(res.X / 4 - 3, res.Y / 2 + 6);
			cout << "> ";
			previousPos.x = res.X / 4 - 3;
			previousPos.y = res.Y / 2 + 6;
			nextData = 1;
		}
		else if (right)
		{
			IsGotoxy(res.X / 4 + 40 - 3, res.Y / 2 + 6);
			cout << "> ";
			previousPos.x = res.X / 4 + 40 - 3;
			previousPos.y = res.Y / 2 + 6;
			nextData = 2;
		}
	}
	if (select)
	{
		return true;
	}
	return false;

}

void GameOverScene::GameOverText()
{
	wstring gameOver[5]
	{
		L" ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████\n",
		L"██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██\n",
		L"██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████\n",
		L"██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██\n",
		L" ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██\n",
	};

	COORD res = GetConsoleResolution();

	
	int previous = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 5; ++i)
	{
		IsGotoxy(res.X / 7, res.Y / 2 - 3 + i);
		wcout << gameOver[i];
	}
	_setmode(_fileno(stdout), previous);
}

void GameOverScene::SelectText()
{
	string menuStr[2]
	{
		"종료",
		"메뉴 이동",
	};

	COORD res = GetConsoleResolution();

	for (int i = 0; i < 2; ++i)
	{
		IsGotoxy(res.X / 4 + (i * 40), res.Y / 2 + 6);
		cout << menuStr[i];
	}
}

