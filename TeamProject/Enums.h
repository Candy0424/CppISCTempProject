#pragma once

enum class Scene
{
	TITLE, SONG_SELECT, GAME, SETTING, QUIT, GAME_OVER , END
};


enum class Tile
{
	NODE, ROAD, INPUT_NODE, OUTPUT_NODE, SPACE
};

enum class JudgeResult
{
	NONE, PERFECT, GOOD, BAD, MISS
};

enum class NodeSymbolType
{
	CLASSIC,
	ALTERNATIVE
};

enum class PlayerNodeInstrument
{
	MIC = 0,    // 🎤
	PIANO,  // 🎹
	VIOLIN, // 🎻
	GUITAR, // 🎸
	TRUMPET,// 🎺
	DRUM    // 🥁
};