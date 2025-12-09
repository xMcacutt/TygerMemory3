#pragma once
#ifdef TYGERMEM3_EXPORTS
#define TYGERMEM3 __declspec(dllexport)
#else
#define TYGERMEM3 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"
#include "SaveData.h"

class TYGERMEM3 Missions {
public:
	static void UpdateMissionState(MissionStruct* mission, int state, char unk);
};