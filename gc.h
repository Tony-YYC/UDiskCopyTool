#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <compressor.h>
#include <DeleteFile.h>
using namespace std;

void GarbageCollection(string compressorPath,string transpath,string zippath,string password) {
	time_t current = time(&current);
	char buff[26];
	ctime_s(buff, sizeof buff, &current);
	string buff_str = buff;
	string filename2 = zippath + "GC " + buff_str + ".7z";
	filename2.erase(remove(filename2.begin(), filename2.end(), '\n'), filename2.end());
	filename2.erase(remove(filename2.begin(), filename2.end(), '\t'), filename2.end());
	filename2.erase(remove(filename2.begin(), filename2.end(), '\0'), filename2.end());
	compress(compressorPath , transpath , filename2 , password);
	DeleteAllFile(transpath.c_str());
	string remakedir = "mkdir " + transpath;
	system((char*)remakedir.c_str());
}