#pragma once

enum class LevelType {
	TITLE,
	STAGE1,
	END,
};

class CLevelGenerator
{
private:
	static class CLevel* m_pTempLevel;
	static class CLevel* m_arrStages[(UINT)LevelType::END];

public:
	static UINT32 GetSeed();

	static void Init();
	static void TitleLevel();
	static void MakeStages();
	static CLevel* GetLevel(int _level);
	static CLevel* GetTempLevel() { return m_pTempLevel; }
	static void LoadTempLevel();
	static void DestroyStages();
	static void Destroy();


	static void ChangeLevelToPlay();
};

