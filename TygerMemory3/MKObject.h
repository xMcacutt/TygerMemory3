#pragma once
#ifdef TYGERMEM3_EXPORTS
#define TYGERMEM3 __declspec(dllexport)
#else
#define TYGERMEM3 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"

struct ObjectHeaderStruct {
	int unk;
	int unk2;
	uintptr_t objectType;
};

struct MKObjectStruct {
	uintptr_t vtable;
	int unk;
	ObjectHeaderStruct* ObjectHeader;
};

class TYGERMEM3 MKObject {
public:
	static uintptr_t GetMKObject(int id);
};