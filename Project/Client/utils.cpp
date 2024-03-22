#include "pch.h"

int Utils::StringToEnum(const vector<string>& _strings, const string& _target)
{
	int idx = 0;
	for (const string& str : _strings) {
		if (str == _target) {
			return idx;
		}
		idx++;
	}

	return -1;
}

#include <filesystem>
void Utils::LoadAllPath(string _strDirectoryPath, vector<string>& vec)
{
	string path = ToString(CPathMgr::GetContentPath());
	path += _strDirectoryPath;

	namespace fs = std::filesystem;

	for (const auto& entry : fs::directory_iterator(path)) {
		string str = entry.path().string();
		str = str.substr(str.find(_strDirectoryPath));
		vec.push_back(str);
	}
}
