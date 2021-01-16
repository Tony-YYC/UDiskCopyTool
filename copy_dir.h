#pragma once
#include <iostream>
#include <filesystem> // C++17 standard header file name
#include <fstream>
#include <regex>

namespace fs = std::filesystem;
using namespace std;
regex target("(.*)(.pptx)");
void copySubDir(const fs::path& from,const fs::path& to) {
    for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator(from)) {
        fstream fs("logs.txt", fstream::out | ios_base::trunc);
        if (x.is_directory()) {
            cout << "enter directory" << x.path().filename() << endl << endl;
            fs::create_directory(to/x.path().filename());
            fs << "the last directory:" << x.path() << endl;
            fs.close();
            copySubDir(x.path(),to/x.path().filename());
        }
        else {
            try {
                cout << "file copied successfully" << endl;
                cout << "from"<< x.path()<<"to"<< to/x.path().filename() << endl << endl;
                fs << "the last file:" << "from" << x.path() << "to" << to / x.path().filename() << endl;
                if (regex_match(x.path().filename().string(), target)) {
                    fs::copy_file(x.path(), to / x.path().filename(), fs::copy_options::update_existing);
                }
                fs.close();
                
            }
            catch (fs::filesystem_error& ec) {
                cout << "Error:" << ec.what() << endl;
            }
        }
    }
    
}
int copyDir(string src, string des) {
    cout << "start copying ..." << endl;
    fs::path srcPath = src;
    fs::path desPath = des;
    try {
        //fs::copy(srcPath, desPath, fs::copy_options::update_existing | fs::copy_options::recursive);
        copySubDir(srcPath, desPath);
    }
    catch (fs::filesystem_error& ec) {
        cout << "Error:" << ec.what() << endl;
    }
    return 0;
}