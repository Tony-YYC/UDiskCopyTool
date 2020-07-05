#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <errno.h>

//判断是否是".."目录和"."目录
static bool IsSpecialDir(const char* path)
{
	return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
}

//判断文件属性是目录还是文件
static bool IsDir(int attrib)
{
	return attrib == 16 || attrib == 18 || attrib == 20;
}

//显示删除失败原因
static void ShowError(const char* file_name = NULL)
{
	errno_t err;
	_get_errno(&err);
	switch (err)
	{
	case ENOTEMPTY:
		printf("Given path is not a directory, the directory is not empty, or the directory is either the current working directory or the root directory.\n");
		break;
	case ENOENT:
		printf("Path is invalid.\n");
		break;
	case EACCES:
		printf("%s had been opend by some application, can't delete.\n", file_name);
		break;
	}
}

static void GetFilePath(const char* path, const char* file_name, char* file_path)
{
	strcpy_s(file_path, sizeof(char) * _MAX_PATH, path);
	file_path[strlen(file_path) - 1] = '\0';
	strcat_s(file_path, sizeof(char) * _MAX_PATH, file_name);
}

//递归搜索目录中文件并删除
static void DeleteAFile(const char* path)
{
	char pcSearchPath[_MAX_PATH];
	sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); //pcSearchPath 为搜索路径，* 代表通配符

	_finddata_t DirInfo; //文件夹信息
	_finddata_t FileInfo; //文件信息
	intptr_t f_handle; //查找句柄

	char pcTempPath[_MAX_PATH];
	if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
	{
		while (_findnext(f_handle, &FileInfo) == 0)
		{
			if (IsSpecialDir(FileInfo.name))
				continue;
			if (FileInfo.attrib & _A_SUBDIR)//如果是目录，生成完整的路径
			{
				GetFilePath(pcSearchPath, FileInfo.name, pcTempPath);
				DeleteAFile(pcTempPath); //开始递归删除目录中的内容
				if (FileInfo.attrib == 20)
					printf("This is system file, can't delete!\n");
				else
				{
					//删除空目录，必须在递归返回前调用_findclose,否则无法删除目录
					if (_rmdir(pcTempPath) == -1)
					{
						ShowError();//目录非空则会显示出错原因
					}
				}
			}
			else
			{
				strcpy_s(pcTempPath, pcSearchPath);
				pcTempPath[strlen(pcTempPath) - 1] = '\0';
				strcat_s(pcTempPath, FileInfo.name);//生成完整的文件路径

				if (remove(pcTempPath) == -1)
				{
					ShowError(FileInfo.name);
				}

			}
		}
		_findclose(f_handle);//关闭打开的文件句柄，并释放关联资源，否则无法删除空目录
	}
	else
	{
		ShowError();//若路径不存在，显示错误信息
	}
}

void DeleteAllFile(const char* pcPath)
{
	DeleteAFile(pcPath); //删除该文件夹里的所有文件

	if (_rmdir(pcPath) == -1) //删除此文件夹
	{
		ShowError();
	}
}