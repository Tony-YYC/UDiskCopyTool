#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

void vectorTxt(vector<vector<int>> write,string &wpath){
    ofstream fout;
    fout.open(wpath,ios_base::out);
    if (fout.is_open())
    {
        vector<vector<int>>::iterator it;
        for (it = write.begin(); it != write.end(); ++it) {
            for (size_t i = 0; i < (*it).size(); ++i)
                fout << (*it)[i] << " ";
            fout << endl;
        }
    }
    fout.close();
}

vector<vector<int>> txtVector(string& rpath) {
	vector<int> temp_line;
	vector<vector<int>> Vec_Dti;
	string line;
	ifstream in(rpath);  //读入文件
	regex pat_regex("[[:digit:]]+");  //匹配原则，这里代表一个或多个数字
	while (getline(in, line)) {  //按行读取
		for (sregex_iterator it(line.begin(), line.end(), pat_regex), end_it; it != end_it; ++it) {  //表达式匹配，匹配一行中所有满足条件的字符
			temp_line.push_back(stoi(it->str()));  //将数据转化为int型并存入一维vector中
		}
		Vec_Dti.push_back(temp_line);  //保存所有数据
		temp_line.clear();
	}
	return Vec_Dti;
}

void vectorPrint(vector<vector<int>> &write) {
    vector<vector<int>>::iterator it;
    for (it = write.begin(); it != write.end(); ++it) {
        for (size_t i = 0; i < (*it).size(); ++i)
            cout << (*it)[i] << " ";
        cout << endl;
    }
}