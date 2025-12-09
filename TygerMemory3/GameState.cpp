#include "GameState.h"

void GameState::ForceMainMenu()
{
	*(int*)(Core::moduleBase + 0x4AC7B8) = 0;
}

void GameState::ForceLoad()
{
	*(int*)(Core::moduleBase + 0x4AC7B8) = 4;
}

bool GameState::IsInGame()
{
	return *(int*)(Core::moduleBase + 0x4C466C) == 1;
}
