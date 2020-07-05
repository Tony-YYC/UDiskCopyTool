#include <iostream>
#include<Windows.h>
#include <direct.h>
#include <tlhelp32.h>
#include <comdef.h>

using namespace std;
DWORD GetProcessidFromName(LPCTSTR name) //判断进程是否存在
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
		return 0;
	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;
		_bstr_t tempFile(pe.szExeFile);
		if (strcmp(tempFile, (const char*)name) == 0)
		{
			id = pe.th32ProcessID;

			break;
		}
	}
	CloseHandle(hSnapshot);
	return id;
}

int main() {
	int process_exist;//放回的进程id
	
	HWND hWnd = GetForegroundWindow(); //获取当前的前置窗口
	ShowWindow(hWnd, SW_HIDE); //隐藏了获取的窗口

	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	string exepath = buffer;          //识别当前exe所在路径

	int error_time = 0;

	while (true)
	{
		process_exist = GetProcessidFromName((LPCTSTR)"Core.exe");//判断example.exe进程是否存在
		//cout << process_exist << endl;
		if (process_exist == 0) {
			system(("echo normal|\"" + exepath + "\\Core.exe" + "\"").c_str());
		}
		Sleep(60000);
		cout << endl;

		error_time ++;
		if (error_time >= 4) {
			break;
		}
	}
	return 0;
	//MessageBoxA(NULL, "不要乱搞!!!", "", MB_OK);
}
