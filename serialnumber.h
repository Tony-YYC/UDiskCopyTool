#pragma once
#include   <iostream>
#include <string>
#include <atlconv.h>
#include <windows.h>
using namespace std;
DWORD serialnum(char *volumesym)
{
    DWORD VolumeSerialNumber;
	int i;
	wchar_t wth[50];
	for (i = 0; volumesym[i]; i++)
		wth[i] = volumesym[i];
	wth[i] = '\0';
	LPCTSTR str = wth;
    GetVolumeInformation(str, NULL, 12, &VolumeSerialNumber, NULL, NULL, NULL, 10);
    return  VolumeSerialNumber;
}