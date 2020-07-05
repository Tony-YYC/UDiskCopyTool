#include <iostream>
#include <copy_dir.h>
#include <fstream>
int main()
{
	string des;
	string src;
	cout << "enter destination" << endl;
	cin >> des;
	cout << "enter source" << endl;
	cin >> src;
	//copyDir("C:\\Users\\yuyic\\Desktop\\Temp\\语文作文", "C:\\Users\\yuyic\\Desktop\\Temp\\chemistry23");
	//fs::path from = "C:\\Users\\yuyic\\Desktop\\Temp\\语文作文";
	fs::path from = src;
	cout << "files in source" << endl;
	for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator(from)) {
		fstream fs("logs.txt", fstream::out | ios_base::out);
		cout << x.path() << endl;
		fs << "the last file:" <<x.path() << endl;
		fs.close();
	}
	copyDir(src, des);
	fs::path to = des;
	cout << "files in destination" << endl;
	for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator(to)) {
		cout << x.path() << endl;
	}
	
}