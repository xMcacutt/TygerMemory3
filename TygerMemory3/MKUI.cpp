#include "MKUI.h"

uintptr_t MKUI::GetBaseUI()
{
    uintptr_t address = Core::moduleBase + 0x4c6024;
    return address;
}

UIElementStruct* MKUI::GetMainMenu()
{
    uintptr_t uiManager = *(uintptr_t*)(GetBaseUI());
    UIElementStruct* mainMenu = *(UIElementStruct**)(uiManager + 0x4FC);
    return mainMenu;
}

UIElementStruct* MKUI::FindChildElementByName(UIElementStruct* parent, const char* childTypeName)
{
    if (parent == nullptr || childTypeName == nullptr || parent->firstChildUiElement == nullptr) {
        return nullptr;
    }
    UIElementStruct* currentChild = parent->firstChildUiElement;

    for (int i = 0; i < parent->numChildElements; ++i) {
        if (currentChild != nullptr && currentChild->TypeName != nullptr) {
            if (strcmp(currentChild->TypeName, childTypeName) == 0) {
                return currentChild;
            }
        }
        currentChild = currentChild->nextUiElementInList;
    }

    // Not found
    return nullptr;
}
