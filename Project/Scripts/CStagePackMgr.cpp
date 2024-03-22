#include "pch.h"
#include "CStagePackMgr.h"

#include <Engine/utils.h>

#include "CStagePack.h"

CStagePackMgr::CStagePackMgr()
	: m_arrPacks{}
{
	for (int i = 0; i < (int)StagePackList::END; i++) {
		string path = ToString(CPathMgr::GetContentPath()) + "stage\\";
		path += StagePackListString[i];
		ifstream fin(path);
		if (fin.is_open()) {
			CStagePack* sp = new CStagePack;
			fin >> *sp;
			m_arrPacks[i] = sp;
		}
	}
}

CStagePackMgr::~CStagePackMgr()
{
	Delete_Array(m_arrPacks);
}
