#pragma once
#include <Windows.h>
#include <string>
#include <typeconversion.h>

// 目录是否存在的检查：
using namespace std;
BOOL CheckFolderExist(const string& strPath)
{
    WIN32_FIND_DATA  FindFileData;
    BOOL bValue = false;
    LPCWSTR lpcwstrPath = stringToLPCWSTR(strPath);
    HANDLE hFind = FindFirstFile(lpcwstrPath, &FindFileData);
    if ((hFind != INVALID_HANDLE_VALUE) && ( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        bValue = TRUE;
    }
    FindClose(hFind);
    return bValue;
}