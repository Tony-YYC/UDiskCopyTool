#pragma once
#include   <windows.h>
#include   <iostream>
#include <string>
using namespace std;
int volumesize(char* volumesym) {
    DWORD dwTotalClusters;//总的簇
    DWORD dwFreeClusters;//可用的簇
    DWORD dwSectPerClust;//每个簇有多少个扇区
    DWORD dwBytesPerSect;//每个扇区有多少个字节
    BOOL bResult = GetDiskFreeSpace(TEXT("C:"), &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
    int volumesize = (dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect - dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect) / 1024;
    return volumesize;
}