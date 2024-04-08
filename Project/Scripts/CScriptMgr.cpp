#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CTile.h"
#include "CCameraMovement.h"
#include "CTileBoundary.h"
#include "CSnakeScript.h"
#include "CDetectCollider.h"
#include "CMonsterHitCollider.h"
#include "CGroundCollider.h"
#include "CWallCollider.h"
#include "CPlayerHitCollider.h"
#include "CCeilCollider.h"
#include "CRock.h"
#include "CPlayerScript.h"
#include "CWhip.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CTile");
	_vec.push_back(L"CCameraMovement");
	_vec.push_back(L"CTileBoundary");
	_vec.push_back(L"CSnakeScript");
	_vec.push_back(L"CDetectCollider");
	_vec.push_back(L"CMonsterHitCollider");
	_vec.push_back(L"CGroundCollider");
	_vec.push_back(L"CWallCollider");
	_vec.push_back(L"CPlayerHitCollider");
	_vec.push_back(L"CCeilCollider");
	_vec.push_back(L"CRock");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CWhip");
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
	if (L"CSnakeScript" == _strScriptName)
		return new CSnakeScript;
	if (L"CDetectCollider" == _strScriptName)
		return new CDetectCollider;
	if (L"CMonsterHitCollider" == _strScriptName)
		return new CMonsterHitCollider;
	if (L"CGroundCollider" == _strScriptName)
		return new CGroundCollider;
	if (L"CWallCollider" == _strScriptName)
		return new CWallCollider;
	if (L"CPlayerHitCollider" == _strScriptName)
		return new CPlayerHitCollider;
	if (L"CCeilCollider" == _strScriptName)
		return new CCeilCollider;
	if (L"CRock" == _strScriptName)
		return new CRock;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CWhip" == _strScriptName)
		return new CWhip;
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
	case (UINT)SCRIPT_TYPE::SNAKESCRIPT:
		return new CSnakeScript;
		break;
	case (UINT)SCRIPT_TYPE::DETECTCOLLIDER:
		return new CDetectCollider;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHITCOLLIDER:
		return new CMonsterHitCollider;
		break;
	case (UINT)SCRIPT_TYPE::GROUNDCOLLIDER:
		return new CGroundCollider;
		break;
	case (UINT)SCRIPT_TYPE::WALLCOLLIDER:
		return new CWallCollider;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHITCOLLIDER:
		return new CPlayerHitCollider;
		break;
	case (UINT)SCRIPT_TYPE::CEILCOLLIDER:
		return new CCeilCollider;
		break;
	case (UINT)SCRIPT_TYPE::ROCK:
		return new CRock;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::WHIP:
		return new CWhip;
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

	case SCRIPT_TYPE::SNAKESCRIPT:
		return L"CSnakeScript";
		break;

	case SCRIPT_TYPE::DETECTCOLLIDER:
		return L"CDetectCollider";
		break;

	case SCRIPT_TYPE::MONSTERHITCOLLIDER:
		return L"CMonsterHitCollider";
		break;

	case SCRIPT_TYPE::GROUNDCOLLIDER:
		return L"CGroundCollider";
		break;

	case SCRIPT_TYPE::WALLCOLLIDER:
		return L"CWallCollider";
		break;

	case SCRIPT_TYPE::PLAYERHITCOLLIDER:
		return L"CPlayerHitCollider";
		break;

	case SCRIPT_TYPE::CEILCOLLIDER:
		return L"CCeilCollider";
		break;

	case SCRIPT_TYPE::ROCK:
		return L"CRock";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::WHIP:
		return L"CWhip";
		break;

	}
	return nullptr;
}