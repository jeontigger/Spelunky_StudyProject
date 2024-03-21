#pragma once
namespace Utils {
	static int StringToEnum(const vector<string>& _strings, const string& _target) {
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