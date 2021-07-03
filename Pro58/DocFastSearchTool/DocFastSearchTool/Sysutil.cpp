#include"Sysutil.h"

//扫描目录
void DirectionList(const string &path, vector<string> &subfile, vector<string> &subdir)
{
	string _path = path;
	_path += "\\*.*";

	_finddata_t file;
	//句柄
	long handle = _findfirst(_path.c_str(), &file);
	if(handle == -1)
	{
		cout<<"扫描目录出错......"<<endl;
		return;
	}

	do
	{
		if(file.name[0] == '.')
			continue;
		if(file.attrib &  _A_SUBDIR)
			subdir.push_back(file.name);
		else
			subfile.push_back(file.name);
		
	}while(_findnext(handle, &file) == 0);

	_findclose(handle);
}

/*
//遍历目录
void DirectionList(const string &path)
{
	//C:\Bit\Book\比特科技\阶段性考试试卷
	string _path = path;

	//C:\\Bit\\Book\\比特科技\\阶段性考试试卷\\*.*
	_path += "\\*.*";

	_finddata_t file;
	//句柄
	long handle = _findfirst(_path.c_str(), &file);
	if(handle == -1)
	{
		cout<<"扫描目录出错......"<<endl;
		return;
	}

	do
	{
		if(file.name[0] == '.')
			continue;
		cout<<file.name<<endl;
		if(file.attrib & _A_SUBDIR)
		{
			//C:\Bit\Book\比特科技\阶段性考试试卷
			string tmp_path = path;
			//C:\Bit\Book\比特科技\阶段性考试试卷\\ 
			tmp_path += "\\";
			//C:\Bit\Book\比特科技\阶段性考试试卷\\C语言
			tmp_path += file.name;
			DirectionList(tmp_path);
		}
		
	}while(_findnext(handle, &file) == 0);

	_findclose(handle);
}
*/