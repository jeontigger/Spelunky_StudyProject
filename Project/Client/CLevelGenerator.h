#pragma once

constexpr int StageCnt = 4;
class CLevelGenerator
{
private:
	static class CLevel* m_pTempLevel;
	static class CLevel* m_arrStages[StageCnt];

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

};

