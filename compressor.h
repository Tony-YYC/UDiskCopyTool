#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
void compress(string dirlocation,string& srclocation,string &zipname) {
	string exelocation = dirlocation + "\\7z.exe";
	string command1 = "\"" 
		+ exelocation 
		+ "\"" + "a" 
		+ "\"" + zipname 
		+ "\"" + "-sdel -pDrLisaSu -mhe -v4g -r -y" 
		+ "\"" + srclocation + "\"";
	system(command1.c_str());
}

void compressAllDir(string dirlocation,string ParentDir, string TargetDir) {
	fs::path from = ParentDir;
	fs::path to = TargetDir;
	for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator(from)) {
		string compressDir = x.path().string();
		string filename = (TargetDir/x.path().filename()).string() + ".7z";
		string dirlocation1 = dirlocation;
		compress(dirlocation1,compressDir ,filename);
		cout << compressDir << "ÒÑ³É¹¦Ñ¹Ëõ" << endl;
	}
}