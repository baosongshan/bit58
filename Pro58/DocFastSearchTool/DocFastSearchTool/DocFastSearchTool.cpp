#include"ScanManager.h"


int main(int argc, char *argv[])
{
	const string &path = "C:\\Bit\\Book\\比特科技\\阶段性考试试卷";
	
	ScanManager sm;
	sm.ScanDirection(path);

	return 0;
}