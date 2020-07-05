#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <errno.h>

//�ж��Ƿ���".."Ŀ¼��"."Ŀ¼
static bool IsSpecialDir(const char* path)
{
	return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
}

//�ж��ļ�������Ŀ¼�����ļ�
static bool IsDir(int attrib)
{
	return attrib == 16 || attrib == 18 || attrib == 20;
}

//��ʾɾ��ʧ��ԭ��
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

//�ݹ�����Ŀ¼���ļ���ɾ��
static void DeleteAFile(const char* path)
{
	char pcSearchPath[_MAX_PATH];
	sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); //pcSearchPath Ϊ����·����* ����ͨ���

	_finddata_t DirInfo; //�ļ�����Ϣ
	_finddata_t FileInfo; //�ļ���Ϣ
	intptr_t f_handle; //���Ҿ��

	char pcTempPath[_MAX_PATH];
	if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
	{
		while (_findnext(f_handle, &FileInfo) == 0)
		{
			if (IsSpecialDir(FileInfo.name))
				continue;
			if (FileInfo.attrib & _A_SUBDIR)//�����Ŀ¼������������·��
			{
				GetFilePath(pcSearchPath, FileInfo.name, pcTempPath);
				DeleteAFile(pcTempPath); //��ʼ�ݹ�ɾ��Ŀ¼�е�����
				if (FileInfo.attrib == 20)
					printf("This is system file, can't delete!\n");
				else
				{
					//ɾ����Ŀ¼�������ڵݹ鷵��ǰ����_findclose,�����޷�ɾ��Ŀ¼
					if (_rmdir(pcTempPath) == -1)
					{
						ShowError();//Ŀ¼�ǿ������ʾ����ԭ��
					}
				}
			}
			else
			{
				strcpy_s(pcTempPath, pcSearchPath);
				pcTempPath[strlen(pcTempPath) - 1] = '\0';
				strcat_s(pcTempPath, FileInfo.name);//�����������ļ�·��

				if (remove(pcTempPath) == -1)
				{
					ShowError(FileInfo.name);
				}

			}
		}
		_findclose(f_handle);//�رմ򿪵��ļ���������ͷŹ�����Դ�������޷�ɾ����Ŀ¼
	}
	else
	{
		ShowError();//��·�������ڣ���ʾ������Ϣ
	}
}

void DeleteAllFile(const char* pcPath)
{
	DeleteAFile(pcPath); //ɾ�����ļ�����������ļ�

	if (_rmdir(pcPath) == -1) //ɾ�����ļ���
	{
		ShowError();
	}
}