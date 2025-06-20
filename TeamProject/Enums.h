#pragma once

enum class Key
{
	D, F, J, K
};

enum class Scene
{
	TITLE, GAME, SETTING, QUIT, END
};

enum class Tile
{
	NODE, ROAD, INPUT_NODE, OUTPUT_NODE, SPACE
};

enum class JudgeResult
{
	NONE, PERFECT, GOOD, MISS
};