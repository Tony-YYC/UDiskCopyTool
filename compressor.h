#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <shellapi.h>
using namespace std;
void compress(string compressor1 ,string dir_from1/*= _T("E:\\")*/, string dir_to1 ,string password1/*= _T("123")*/)
{
    CString compressor(compressor1.c_str());
    CString dir_from(dir_from1.c_str());
    CString dir_to(dir_to1.c_str());
    CString password(password1.c_str());
    CString param;
    param.Format(_T("a -p%s -mhe \"%s\" \"%s\""), password, dir_to, dir_from);
    CString str;
    str.Format(_T("%s.zip"), dir_to);
    if (PathFileExists(str))//防止追加文件生成*zip.tmp*文件
    {
        DeleteFile(str);
    }
    HINSTANCE hRet = ShellExecute(NULL, _T("open"), compressor , param, NULL, SW_HIDE);//SW_SHOW显示对话框
    if (!hRet)
    {
        OutputDebugString(_T("Compression failure!"));
    }
    else
    {
        OutputDebugString(_T("Compression Success!"));
    }
}