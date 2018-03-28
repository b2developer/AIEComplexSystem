#pragma once
#ifdef _WINDLL
#define DLL_EXP _declspec(dllexport)
#pragma message("DLL")
#else
#define DLL_EXP
#pragma message("Static")
#endif