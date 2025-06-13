#pragma once
#include "Defines.h"

typedef struct _pos
{
    int x;
    int y;
    bool operator == (const _pos& _other) const
    {
        return (x == _other.x && y == _other.y);
    }
}POS, * PPOS;

class Player
{
private:
    Player();
public:
	static Player* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Player();
			instance->InitPlayer();
		}
		return instance;
	}
    static void DestroyInstance()
    {
		SAFE_DELETE(instance);
    }
    POS position;
    int life;
    bool isDie;
    void InitPlayer();

private:
    static Player* instance;
};

