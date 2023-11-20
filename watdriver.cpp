#include <windows.h>
#include <psapi.h>
#include <iostream>

int main() {
    LPVOID aDrivers[1024];
    DWORD cbNeeded;
    unsigned int i;

    // Enumerate all drivers
    if (!EnumDeviceDrivers(aDrivers, sizeof(aDrivers), &cbNeeded)) {
        std::cerr << "EnumDeviceDrivers failed; error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Calculate how many driver addresses were returned
    unsigned int cDrivers = cbNeeded / sizeof(LPVOID);

    // Print the name and path of each driver
    for (i = 0; i < cDrivers; i++) {
        char szDriverName[MAX_PATH];
        if (GetDeviceDriverBaseNameA(aDrivers[i], szDriverName, sizeof(szDriverName) / sizeof(char))) {
            std::cout << "Driver Name: " << szDriverName << std::endl;
            char szDriverPath[MAX_PATH];
            if (GetDeviceDriverFileNameA(aDrivers[i], szDriverPath, sizeof(szDriverPath) / sizeof(char))) {
                std::cout << "Driver Path: " << szDriverPath << std::endl;
            }
        }
    }

    return 0;
}
