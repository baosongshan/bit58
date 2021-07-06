#include"ScanManager.h"
#include"Sysutil.h"

void ScanManager::ScanDirection(const string &path)
{
	//ɨ�豾���ļ�
	vector<string> local_files;
	vector<string> local_dirs;
	DirectionList(path, local_files, local_dirs);
	multiset<string> local_set;
	local_set.insert(local_files.begin(), local_files.end());
	local_set.insert(local_dirs.begin(), local_dirs.end());

	//ɨ�����ݿ��ļ�
	multiset<string> db_set;
	m_dm.GetDocs(path, db_set);

	//ͬ�����ݿ�
	auto local_it = local_set.begin();
	auto db_it = db_set.begin();
	while(local_it!=local_set.end() && db_it!=db_set.end())
	{
		
		if(*local_it < *db_it)
		{
			//�������ļ������ݿ�û�У���������
			m_dm.InsertDoc(path, *local_it);
			++local_it;
		}
		else if(*local_it > *db_it)
		{
			//����û���ļ������ݿ��У�ɾ������
			m_dm.DeleteDoc(path, *db_it);
			++db_it;
		}
		else
		{
			++local_it;
			++db_it;
		}
	}

	while(local_it != local_set.end())
	{
		m_dm.InsertDoc(path, *local_it);
		++local_it;
	}
	while(db_it != db_set.end())
	{
		m_dm.DeleteDoc(path, *db_it);
		++db_it;
	}

	//ɨ����Ŀ¼
	for(const auto &dir : local_dirs)
	{
		string dir_path = path;
		dir_path += "\\";
		dir_path += dir;
		ScanDirection(dir_path);
	}
}