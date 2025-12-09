#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"

struct UIElementStruct {
	uintptr_t vtable;
	char* TypeName;
	uintptr_t anotherVtable;
	UIElementStruct* parentUiElement;

	UIElementStruct* nextUiElementInList;
	bool drawn;
	bool enabled;
	bool currentlySelected;
	bool interactable;
	int unk18;
	int unk1c;

	float Blue;
	float Red;
	float Green;
	float Alpha;

	char unk30[0xC];
	float unk3C;

	char unk40[0x10];
	float size;
	char unk54[0xC];

	char unk60[4];
	UIElementStruct* firstChildUiElement;
	int numChildElements;
};

class TYGERMEM2 MKUI {
private:
	static UIElementStruct* FindElementRecursive(UIElementStruct* element, const char* name);
	static void BuildUITreeString(UIElementStruct* element, std::string& out, int depth);
public:
	static uintptr_t GetBaseUI();
	static UIElementStruct* FindElementByName(const char* elementName);
	static UIElementStruct* FindChildElementByName(UIElementStruct* parent, const char* childname);
	static std::string GetUITreeString();
};