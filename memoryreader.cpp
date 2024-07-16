#include "memoryreader.h"


DWORD_PTR GetModuleBaseAddress(const wchar_t* moduleName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId());
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Failed to create snapshot. Error code: " << GetLastError() << std::endl;
        return 0;
    }

    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(moduleEntry);

    if (!Module32First(hSnapshot, &moduleEntry)) {
        CloseHandle(hSnapshot);
        std::cerr << "Error: Module32First failed. Error code: " << GetLastError() << std::endl;
        return 0;
    }

    do {
        if (wcscmp(moduleEntry.szModule, moduleName) == 0) {
            CloseHandle(hSnapshot);
            return (DWORD_PTR)moduleEntry.modBaseAddr;
        }
    } while (Module32Next(hSnapshot, &moduleEntry));

    CloseHandle(hSnapshot);
    std::cerr << "Error: Module not found." << std::endl;
    return 0;
}
DWORD ReadMemory(DWORD_PTR addressToRead) {
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    if (hProcess == NULL) {
        std::cerr << "Error: Failed to open process. Error code: " << GetLastError() << std::endl;
        return 0;
    }

    DWORD value = 0;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)addressToRead, &value, sizeof(DWORD), &bytesRead)) {
        std::cerr << "Error: Failed to read process memory. Error code: " << GetLastError() << std::endl;
    }
    else {
        std::cout << "Read value at address " << std::hex << addressToRead << ": " << value << std::endl;
    }

    CloseHandle(hProcess);
    return value;
}
float ReadFloat(DWORD_PTR addressToRead) {
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    if (hProcess == NULL) {
        MessageBox(0, L"Couldnt open process", L":(", 0);
        return 0.0f;
    }

    float value = 5.0f;
    SIZE_T bytesRead = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)addressToRead, &value, sizeof(float), &bytesRead)) {
        MessageBox(0, L"Failed to read value", L":(", 0);
    }

    CloseHandle(hProcess);
    return value;
}