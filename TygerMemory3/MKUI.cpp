#include "MKUI.h"

uintptr_t MKUI::GetBaseUI()
{
    uintptr_t address = *(uintptr_t*)(Core::moduleBase + 0x4c6024);
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
    if (!element || !name)
        return nullptr;
    if (element->TypeName && strcmp(element->TypeName, name) == 0)
        return element;
    if (element->numChildElements >= 0 && element->numChildElements < 1000)
    {
        UIElementStruct* child = element->firstChildUiElement;
        for (int i = 0; i < element->numChildElements && child; ++i)
        {
            UIElementStruct* found = FindElementRecursive(child, name);
            if (found)
                return found;
            child = child->nextUiElementInList;
        }
    }
    return FindElementRecursive(element->nextUiElementInList, name);
}

std::string MKUI::GetUITreeString()
{
    uintptr_t baseUI = GetBaseUI();
    if (!baseUI)
        return "Error: Base UI is null.";

    UIElementStruct* root = reinterpret_cast<UIElementStruct*>(baseUI);
    if (!root)
        return "Error: Root element is null.";

    std::string tree;
    BuildUITreeString(root, tree, 0);
    return tree;
}

void MKUI::BuildUITreeString(UIElementStruct* element, std::string& out, int depth)
{
    while (element)
    {
        out.append(std::string(depth * 2, ' '));
        out.append(element->TypeName ? element->TypeName : "<null>");
        out.append("\n");
        if (element->numChildElements >= 0 && element->numChildElements < 1000)
        {
            UIElementStruct* child = element->firstChildUiElement;

            for (int i = 0; i < element->numChildElements && child; i++)
            {
                BuildUITreeString(child, out, depth + 1);
                child = child->nextUiElementInList;
            }
        }
        element = element->nextUiElementInList;
    }
}

UIElementStruct* MKUI::FindElementByPath(const char* path)
{
    if (!path)
        return nullptr;

    uintptr_t baseUI = GetBaseUI();
    UIElementStruct* current = reinterpret_cast<UIElementStruct*>(baseUI);
    if (!current)
        return nullptr;

    const char* start = path;
    const char* end = path;

    while (*end != '\0')
    {
        if (*start == '/')
        {
            start++;
            end = start;
            continue;
        }

        while (*end != '\0' && *end != '/')
            end++;

        int len = end - start;
        if (len <= 0)
        {
            if (*end == '/')
                end++;
            start = end;
            continue;
        }

        char segment[256];
        if (len >= sizeof(segment))
            return nullptr;

        memcpy(segment, start, len);
        segment[len] = '\0';

        current = FindChildElementByName(current, segment);
        if (!current)
            return nullptr;

        start = (*end == '/') ? end + 1 : end;
        end = start;
    }

    return current;
}