#include "pch.h"
#include "CBlackboard.h"

#include "CGameObject.h"

void (*CBlackboard::SaveGameObject)(CGameObject* _Obj, ofstream& fout) = nullptr;
CGameObject* (*CBlackboard::LoadGameObject)(ifstream& fin) = nullptr;

void CBlackboard::Copy(CBlackboard& _bb) const
{
	for (auto iter =m_mapBBData.begin(); iter != m_mapBBData.end(); ++iter) {

		switch (iter->second.Type)
		{
		case BB_DATA::INT:
		{
			int temp = *((int*)iter->second.pData);
			_bb.AddBlackboardData(iter->first, iter->second.Type, &temp);
		}
		break;
		case BB_DATA::FLOAT:
		{
			float temp = *((float*)iter->second.pData);
			_bb.AddBlackboardData(iter->first, iter->second.Type, &temp);
		}
		break;
		case BB_DATA::VEC2:
		{
			Vec2 temp = *((Vec2*)iter->second.pData);
			_bb.AddBlackboardData(iter->first, iter->second.Type, &temp);
		}
		break;
		case BB_DATA::VEC3:
		{
			Vec3 temp = *((Vec3*)iter->second.pData);
			_bb.AddBlackboardData(iter->first, iter->second.Type, &temp);
		}
		break;
		case BB_DATA::VEC4:
		{
			Vec4 temp = *((Vec4*)iter->second.pData);
			_bb.AddBlackboardData(iter->first, iter->second.Type, &temp);
		}
		break;
		case BB_DATA::OBJECT:
		{
			CGameObject* obj = (CGameObject*)iter->second.pData;
			_bb.AddBlackboardData(iter->first, iter->second.Type, obj);
		}
		break;
		default:
			break;
		}
	}
}

CBlackboard::CBlackboard()
{
}

CBlackboard::CBlackboard(const CBlackboard& _board)
	: CEntity(_board)
	, m_mapBBData()
{

}

CBlackboard::~CBlackboard()
{
}

void CBlackboard::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	assert(iter == m_mapBBData.end());

	m_mapBBData.insert(make_pair(_strKey, tBlackboardData{ _Type , _Data }));
}

void* CBlackboard::GetBlackboardData(const wstring& _strKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	if (iter == m_mapBBData.end())
		return nullptr;

	return iter->second.pData;
}

void CBlackboard::Save(ofstream& fout)
{
	fout << m_mapBBData.size() << endl;
	for (auto iter = m_mapBBData.begin(); iter != m_mapBBData.end(); ++iter) {
		fout << ToString(iter->first) << endl;
		auto data = iter->second;
		fout << (int)data.Type << endl;
		switch (data.Type)
		{
		case BB_DATA::INT:
			fout << *((int*)data.pData) << endl;
			break;
		case BB_DATA::FLOAT:
			fout << *((float*)data.pData) << endl;
			break;
		case BB_DATA::VEC2:
			fout << *((Vec2*)data.pData) << endl;
			break;
		case BB_DATA::VEC3:
			fout << *((Vec3*)data.pData) << endl;
			break;
		case BB_DATA::VEC4:
			fout << *((Vec4*)data.pData) << endl;
			break;
		case BB_DATA::OBJECT:
				SaveGameObject((CGameObject*)data.pData, fout);
			break;
		default:
			break;
		}

	}
}

void CBlackboard::Load(ifstream& fin)
{
	int num;
	fin >> num;

	for (int i = 0; i < num; i++) {
		string str;
		fin >> str;

		int type;
		fin >> type;
		switch ((BB_DATA)type)
		{
		case BB_DATA::INT:
		{
			int inum;
			fin >> inum;
			AddBlackboardData(ToWString(str), (BB_DATA)type, &inum);
		}
			break;
		case BB_DATA::FLOAT:
		{
			float fnum;
			fin >> fnum;
			AddBlackboardData(ToWString(str), (BB_DATA)type, &fnum);
		}
			break;
		case BB_DATA::VEC2:
		{
			Vec2 v2;
			fin >> v2;
			AddBlackboardData(ToWString(str), (BB_DATA)type, &v2);
		}
			break;
		case BB_DATA::VEC3:
		{
			Vec3 v3;
			fin >> v3;
			AddBlackboardData(ToWString(str), (BB_DATA)type, &v3);
		}
			break;
		case BB_DATA::VEC4:
		{
			Vec4 v4;
			fin >> v4;
			AddBlackboardData(ToWString(str), (BB_DATA)type, &v4);
		}
			break;
		case BB_DATA::OBJECT:
		{
			CGameObject* obj = LoadGameObject(fin);
			AddBlackboardData(ToWString(str), (BB_DATA)type, obj);
		}
			break;
		default:
			break;
		}
	}

}
