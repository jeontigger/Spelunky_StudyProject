#pragma once
namespace Utils {
	int StringToEnum(const vector<string>& _strings, const string& _target);

	void LoadAllPath(string _strDirectoryPath, vector<string>& vec);
}