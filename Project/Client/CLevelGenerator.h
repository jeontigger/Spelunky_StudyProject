#pragma once
class CLevelGenerator
{
private:
	static class CLevel* m_pTempLevel;
	static class CStage* m_arrStages[4];

public:
	static void Init();
	static CStage* LoadLevels(int _level);
	static void LoadTempLevel();

public:
	CLevelGenerator();
	~CLevelGenerator();
};

