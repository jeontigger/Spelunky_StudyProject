#pragma once

constexpr int StageCnt = 4;
class CLevelGenerator
{
private:
	static class CLevel* m_pTempLevel;
	static class CStage* m_arrStages[StageCnt];

public:
	static void Init();
	static void MakeStages();
	static CStage* GetLevel(int _level);
	static void DestroyStages();
	static void Destroy();

};

