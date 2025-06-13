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
	static Player* GetInstance(int& life)
	{
		if (instance == nullptr)
		{
			instance = new Player();
			instance->InitPlayer(life);
		}
		return instance;
	}
    static void DestroyInstance()
    {
		SAFE_DELETE(instance);
    }
    POS nodeOnePosition;
	POS nodeTwoPosition;

    int life;
    bool isDie;
    void InitPlayer(int& life);

private:
    static Player* instance;
};

