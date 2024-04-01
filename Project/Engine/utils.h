#pragma once
class CCollider2D;
namespace Utils {
	int StringToEnum(const vector<string>& _strings, const string& _target);

	void LoadAllPath(string _strDirectoryPath, vector<string>& vec);

	CollisionDir ColliderOverThan(CCollider2D* _isover, CCollider2D* _than);
}