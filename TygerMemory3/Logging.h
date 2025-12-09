#pragma once
#ifdef TYGERMEM3_EXPORTS
#define TYGERMEM3 __declspec(dllexport)
#else
#define TYGERMEM3 __declspec(dllimport)
#endif
#include <string>
#include <fstream>
#include "framework.h"

class Logging {
public:
    static void del();
    static void log(const std::string& message);
};