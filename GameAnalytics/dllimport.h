#pragma once
#ifdef _WINDLL
#define DLL_EXP _declspec(dllexport)
#else
#define DLL_EXP
#endif