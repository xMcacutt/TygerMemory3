
#include "savedata.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) {
        uintptr_t address = Core::moduleBase + 0x4C2EF8;
        Data = reinterpret_cast<SaveDataStruct*>(reinterpret_cast<int*>(address));
    }
    return Data;
}

ItemStruct* SaveData::FindItemById(int itemId)
{
    int index = 0;
	while (index < SaveData::GetData()->itemCount)
	{
		ItemStruct* currentItem = SaveData::GetData()->items[index];
		if (currentItem && currentItem->itemId == itemId)
			return currentItem;
		index++;
	}
    return nullptr;
}

MissionStruct* SaveData::FindMissionById(int missionId)
{
	int index = 0;
	while (index < SaveData::GetData()->missionCount)
	{
		MissionStruct* currentMission = SaveData::GetData()->missions[index];
		if (currentMission && currentMission->missionId == missionId)
			return currentMission;
		index++;
	}
    return nullptr;
}

ShopStruct* SaveData::FindShopById(int shopId)
{
	int index = 0;
	while (index < SaveData::GetData()->shopCount)
	{
		ShopStruct* currentShop = SaveData::GetData()->shops[index];
		if (currentShop && currentShop->shopId == shopId)
			return currentShop;
		index++;
	}
    return nullptr;
}

std::string SaveData::GetText(int textId) {
	using GetTextFunc = const char* (__cdecl*)(int);
	GetTextFunc getText = reinterpret_cast<GetTextFunc>(Core::moduleBase + 0x313940);
	const char* result = getText(textId);
	if (result != nullptr)
		return std::string(result);
	return "";
}