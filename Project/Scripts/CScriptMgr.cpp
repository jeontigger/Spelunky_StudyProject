#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CTile.h"
#include "CCameraMovement.h"
#include "CTileBoundary.h"
#include "CPlayerScript.h"
#include "CSnakeScript.h"
#include "CMonsterHitCollider.h"
#include "CMonsterDetectTileCollider.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CTile");
	_vec.push_back(L"CCameraMovement");
	_vec.push_back(L"CTileBoundary");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CSnakeScript");
	_vec.push_back(L"CMonsterHitCollider");
	_vec.push_back(L"CMonsterDetectTileCollider");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CTile" == _strScriptName)
		return new CTile;
	if (L"CCameraMovement" == _strScriptName)
		return new CCameraMovement;
	if (L"CTileBoundary" == _strScriptName)
		return new CTileBoundary;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CSnakeScript" == _strScriptName)
		return new CSnakeScript;
	if (L"CMonsterHitCollider" == _strScriptName)
		return new CMonsterHitCollider;
	if (L"CMonsterDetectTileCollider" == _strScriptName)
		return new CMonsterDetectTileCollider;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::TILE:
		return new CTile;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVEMENT:
		return new CCameraMovement;
		break;
	case (UINT)SCRIPT_TYPE::TILEBOUNDARY:
		return new CTileBoundary;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SNAKESCRIPT:
		return new CSnakeScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHITCOLLIDER:
		return new CMonsterHitCollider;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERDETECTTILECOLLIDER:
		return new CMonsterDetectTileCollider;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::TILE:
		return L"CTile";
		break;

	case SCRIPT_TYPE::CAMERAMOVEMENT:
		return L"CCameraMovement";
		break;

	case SCRIPT_TYPE::TILEBOUNDARY:
		return L"CTileBoundary";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::SNAKESCRIPT:
		return L"CSnakeScript";
		break;

	case SCRIPT_TYPE::MONSTERHITCOLLIDER:
		return L"CMonsterHitCollider";
		break;

	case SCRIPT_TYPE::MONSTERDETECTTILECOLLIDER:
		return L"CMonsterDetectTileCollider";
		break;

	}
	return nullptr;
}