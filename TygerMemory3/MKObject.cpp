#include "MKObject.h"

uintptr_t MKObject::GetMKObject(int id) {
    uintptr_t result = 0;
    uintptr_t(*getObjPtr)(int) = reinterpret_cast<uintptr_t(*)(int)>(Core::moduleBase + 0x2E5200);
    __asm {
        push id
        call getObjPtr
        add esp, 0x4
        mov result, eax
    }
    return result;
}