#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	BACKGROUNDSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	TILE,
	CAMERAMOVEMENT,
	TILEBOUNDARY,
	SNAKESCRIPT,
	DETECTCOLLIDER,
	MONSTERHITCOLLIDER,
	GROUNDCOLLIDER,
	WALLCOLLIDER,
	PLAYERHITCOLLIDER,
	CEILCOLLIDER,
	ROCK,
	PLAYERSCRIPT,
	WHIP,
	UI,
	BOMB,
	ANIMATIONLOOP,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
