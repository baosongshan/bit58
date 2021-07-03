#include"Sysutil.h"

//ɨ��Ŀ¼
void DirectionList(const string &path, vector<string> &subfile, vector<string> &subdir)
{
	string _path = path;
	_path += "\\*.*";

	_finddata_t file;
	//���
	long handle = _findfirst(_path.c_str(), &file);
	if(handle == -1)
	{
		cout<<"ɨ��Ŀ¼����......"<<endl;
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
//����Ŀ¼
void DirectionList(const string &path)
{
	//C:\Bit\Book\���ؿƼ�\�׶��Կ����Ծ�
	string _path = path;

	//C:\\Bit\\Book\\���ؿƼ�\\�׶��Կ����Ծ�\\*.*
	_path += "\\*.*";

	_finddata_t file;
	//���
	long handle = _findfirst(_path.c_str(), &file);
	if(handle == -1)
	{
		cout<<"ɨ��Ŀ¼����......"<<endl;
		return;
	}

	do
	{
		if(file.name[0] == '.')
			continue;
		cout<<file.name<<endl;
		if(file.attrib & _A_SUBDIR)
		{
			//C:\Bit\Book\���ؿƼ�\�׶��Կ����Ծ�
			string tmp_path = path;
			//C:\Bit\Book\���ؿƼ�\�׶��Կ����Ծ�\\ 
			tmp_path += "\\";
			//C:\Bit\Book\���ؿƼ�\�׶��Կ����Ծ�\\C����
			tmp_path += file.name;
			DirectionList(tmp_path);
		}
		
	}while(_findnext(handle, &file) == 0);

	_findclose(handle);
}
*/