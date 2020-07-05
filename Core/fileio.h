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
	ifstream in(rpath);  //�����ļ�
	regex pat_regex("[[:digit:]]+");  //ƥ��ԭ���������һ����������
	while (getline(in, line)) {  //���ж�ȡ
		for (sregex_iterator it(line.begin(), line.end(), pat_regex), end_it; it != end_it; ++it) {  //���ʽƥ�䣬ƥ��һ�������������������ַ�
			temp_line.push_back(stoi(it->str()));  //������ת��Ϊint�Ͳ�����һάvector��
		}
		Vec_Dti.push_back(temp_line);  //������������
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