#pragma once
#include   <windows.h>
#include   <iostream>
#include <string>
using namespace std;
int volumesize(char* volumesym) {
    DWORD dwTotalClusters;//�ܵĴ�
    DWORD dwFreeClusters;//���õĴ�
    DWORD dwSectPerClust;//ÿ�����ж��ٸ�����
    DWORD dwBytesPerSect;//ÿ�������ж��ٸ��ֽ�
    BOOL bResult = GetDiskFreeSpace(TEXT("C:"), &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
    int volumesize = (dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect - dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect) / 1024;
    return volumesize;
}