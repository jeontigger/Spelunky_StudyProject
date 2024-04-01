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

	namespace fs = filesystem;

	for (const auto& entry : fs::directory_iterator(path)) {
		string str = entry.path().string();
		str = str.substr(str.find(_strDirectoryPath));
		vec.push_back(str);
	}
}

#include "CCollider2D.h"
CollisionDir Utils::ColliderOverThan(CCollider2D* _isover, CCollider2D*_than)
{
	auto overmat = _isover->GetColliderWorldMat();
	auto thanmat = _than->GetColliderWorldMat();

	Vec2 overUnderPoint(overmat._41, overmat._42 - abs(overmat._22) / 2.f);
	Vec2 thanPoint(thanmat._41, thanmat._42);
	
	Vec2 vec = overUnderPoint - thanPoint;
	Vec2 normal(0, 1);
	vec.Normalize();
	float angle = acos(normal.Dot(vec));
	XMConvertToDegrees(angle);
	if (XMConvertToDegrees(angle)  < XMConvertToDegrees(XM_PI / 4.f) + 20.f) {
		return CollisionDir::Top;
	}
	return CollisionDir::Side;
}
