#pragma once

#pragma once
#ifdef TYGERMEM3_EXPORTS
#define TYGERMEM3 __declspec(dllexport)
#else
#define TYGERMEM3 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"
#include <optional>

struct ItemStruct {
	uintptr_t vftable;
	int unk4;
	int unk8;
	int unkc;

	char padding[0x10];

	int itemId;
	int titleId;
	int descId;
	int unk2c;

	uintptr_t iconStringPtr; // not used in shop
	int baseCost;
	int numPurchased;
	int maxNumPurchased;

	int unk48;
	int unk4c;
	int currencyType;

	uintptr_t shopIconNamePtr;
	long unk58;
};

struct ShopStruct {
	uintptr_t vftable;
	int unk4;
	int unk8;
	int unkc;

	char padding[0x10];

	int shopId;
	char Padding24[0x10];

	ItemStruct** items;
	int itemCount;

	int unk3c;
	long unk40;
};

enum MissionState {
	UNAVAILABLE = 0,
	AVAILABLE = 2,
	ACTIVE = 3,
	REPLAYABLE = 5,
	COMPLETE = 8
};

struct MissionStruct {
	uintptr_t vftable;

	MissionStruct** precondMissions;
	int precondMissionCount;
	int unkPrecondMissionValue;

	ItemStruct** precondItems;
	int precondItemCount;
	int unkPrecondItemValue;

	MissionState missionState;
	int missionId;
	int titleId;
	int descId;
	int initialStatus;

	char boringStuff[0x150];

	union {
		struct {
			unsigned char rescue : 1; // 1
			unsigned char elective : 1; // 2
			unsigned char unkFlag1 : 1; // 4
			unsigned char allowRetry : 1; // 8
			unsigned char unkFlag2 : 1; // 16
			unsigned char unkFlag3 : 1; // 32
			unsigned char saveActiveAlways : 1; // 64
			unsigned char unkFlag4 : 1; // 128
		};
		unsigned char typeFlags;
	};
	char flagPadding[0x3];
	int unk184;
	int priority;
	int unk18c;
	int rewardFirstPass;
	int rewardRetry;
	int timeLimit;
};

struct SaveDataStruct {
	int percentComplete;
	float playtime; //seconds
	int opalCount1;
	int unkC; // 3
	int gameMode; // 2 for hardcore

	char padding14[0x6c];

	float tysViewInvertX;
	float tysViewInvertY;
	float tysViewSpeed;
	int tysViewDirection; // 1 for body 0 for camera
	float cameraInvertX;
	float cameraInvertY;
	float cameraSpeed;
	bool cameraAutoCenter;
	bool cameraMoveWithJump;
	bool unkSettingsFlag1;
	bool unkSettingsFlag2;
	float cameraZoom;
	int unkSettingsFlag3;
	int unkSettingsFlag4;
	float unkSettingsFloat1; // 0.04
	float unkSettingsFloat2; // 0.5
	float unkSettingsFloat3; // 0.5
	char paddingb8[0x4];
	int damageTakenGlobal;

	int unkc0;
	int unkc4;
	int unkc8;
	int unkcc;

	int unkd0;
	int unkd4;
	int unkd8;
	int enemiesKilledGlobal;

	float unke0; // 11.0
	float unke4; // 1.0
	char paddinge8[0xc];

	char hashBlock1[0x200]; // 512

	int damageTaken;
	int currentRangSave;
	int currentRangLive;
	int opalCount2;
	int opalsCollectedTotal;

	int unk308; // important
	int unk30c; // maybe padding
	int unk310; // 1?
	int unk314; // 1?
	int unk318; // 2?
	int unk31c; // 2?
	char padding320[0x20];

	int availableParkingPads; // very unsure
	uintptr_t unk344;
	uintptr_t currentChunkPtr;
	uintptr_t previousChunkPtr;

	bool unk350;
	bool resetSave; // it true, resets the save file when making a new game
	bool unk352;
	bool unk353;

	int unk354;
	int missionCount; // 48
	int itemCount;    // 136
	int shopCount;    // 8

	MissionStruct** missions;
	ItemStruct** items;
	ShopStruct** shops;
	MissionStruct* targettedMission;
	int mission1Id;

	uintptr_t berriesBitArray;
	int berriesTotal;
	int berriesCollected;
	int berriesSpent;
	int berriesUnknown;
	uintptr_t bilbiesBitArray;
	int bilbiesTotal;
	int bilbiesCollected;
	int bilbiesSpent;
	int bilbiesUnknown;
	uintptr_t framesBitArray;
	int framesTotal;
	int framesCollected;
	int framesSpent;
	int framesunknown;
	uintptr_t orbsBitArray;
	int orbsTotal;
	int orbsCollected;
	int orbsSpent;
	int orbsunknown;
	uintptr_t stevesBitArray;
	int stevesTotal;
	int stevesCollected;
	int stevesSpent;
	int stevesunknown;
	uintptr_t unusedBitArray;
	int unusedTotal;
	int unusedCollected;
	char unusedSpent;
	int unusedUnknown;
	uintptr_t stonesBitArray;
	int stonesTotal;
	int stonesCollected;
	int stonesSpent;
	int stonesUnknown;
};

class TYGERMEM3 SaveData {

protected:
	uintptr_t baseAddress;
	static SaveDataStruct* Data;
public:
	static SaveDataStruct* GetData();
};