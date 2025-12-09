#include "MKUI.h"

uintptr_t MKUI::GetBaseUI()
{
    uintptr_t address = Core::moduleBase + 0x4c6024;
    address = *(uintptr_t*)(address + 0x64);
    return address;
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

UIElementStruct* MKUI::FindElementByName(const char* elementName)
{
    uintptr_t baseUI = GetBaseUI();
    return FindElementRecursive(reinterpret_cast<UIElementStruct*>(baseUI), elementName);
}

UIElementStruct* MKUI::FindElementRecursive(UIElementStruct* element, const char* name)
{
    if (element == nullptr || name == nullptr)
        return nullptr;

    if (element->TypeName && strcmp(element->TypeName, name) == 0)
        return element;

    UIElementStruct* child = element->firstChildUiElement;

    for (int i = 0; i < element->numChildElements && child != nullptr; ++i)
    {
        UIElementStruct* found = FindElementRecursive(child, name);
        if (found)
            return found;
        child = child->nextUiElementInList;
    }

    return nullptr;
}

std::string MKUI::GetUITreeString()
{
    uintptr_t baseUI = GetBaseUI();
    UIElementStruct* root = reinterpret_cast<UIElementStruct*>(baseUI);

    std::string result;
    BuildUITreeString(root, result, 0);
    return result;
}

void MKUI::BuildUITreeString(UIElementStruct* element, std::string& out, int depth)
{
    if (!element)
        return;
    out.append(std::string(depth * 2, ' '));
    if (element->TypeName)
        out.append(element->TypeName);
    else
        out.append("<null>");
    out.append("\n");
    UIElementStruct* child = element->firstChildUiElement;
    for (int i = 0; i < element->numChildElements && child != nullptr; ++i)
    {
        BuildUITreeString(child, out, depth + 1);
        child = child->nextUiElementInList;
    }
}