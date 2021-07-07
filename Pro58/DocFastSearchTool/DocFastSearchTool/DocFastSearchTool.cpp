#include"ScanManager.h"
#include"Sysutil.h"


int main(int argc, char *argv[])
{
	//const string &path = "C:\\Bit\\Book\\���ؿƼ�\\�׶��Կ����Ծ�";
	const string &path = "C:\\Bit\\Code\\bit58\\bit58\\Pro58\\Test_Doc";
	
	//����ɨ�����
	ScanManager &sm = ScanManager::CreateScanManagerObj(path);
	//sm.ScanDirection(path);

	//������������
	DataManager &dm = DataManager::GetDataManagerObj();
	string key;
	vector<pair<string,string>> doc_path;
	while(1)
	{
		cout<<"������Ҫ�����Ĺؼ���:>";
		cin>>key;

		dm.Search(key, doc_path);
		printf("%-15s%-50s\n", "����","·��");
		for(const auto &e : doc_path)
		{
			printf("%-15s%-50s\n", e.first.c_str(), e.second.c_str());
		}
		doc_path.clear();
	}

	return 0;
}
