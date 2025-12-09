
#include "savedata.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) {
        uintptr_t address = Core::moduleBase + 0x4C2EF8;
        Data = reinterpret_cast<SaveDataStruct*>(reinterpret_cast<int*>(address));
    }
    return Data;
}