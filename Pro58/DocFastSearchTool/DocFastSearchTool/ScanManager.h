#pragma once

#include"DataManager.h"

class ScanManager
{
public:
	void ScanDirection(const string &path);
private:
	DataManager m_dm;
};