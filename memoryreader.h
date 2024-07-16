#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <fstream>
#include "d3d9.h"

DWORD_PTR GetModuleBaseAddress(const wchar_t* moduleName);
DWORD ReadMemory(DWORD_PTR addressToRead);
float ReadFloat(DWORD_PTR addressToRead);