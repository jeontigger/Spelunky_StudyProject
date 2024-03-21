#pragma once
namespace Utils {
	int StringToEnum(const vector<string>& _strings, const string& _target) {
		int idx = 0;
		for (const string& str : _strings) {
			if (str == _target) {
				return idx;
			}
			idx++;
		}

		return -1;
	}
}