#pragma once

#include <fstream>
using std::ofstream;

extern vector<wstring> g_vecScriptNames;
extern vector<wstring> g_vecStateNames;
extern vector<string> g_vecFileNames;

extern vector<string> g_vecLevelNames;
extern vector<string> g_vecFxNames;
extern vector<string> g_vecSndNames;
extern vector<string> g_vecTexNames;
extern vector<string> g_vecMtrlNames;
extern vector<string> g_vecPrefNames;
extern vector<string> g_vecAnimNames;
extern vector<string> g_vecTxtNames;
void ScriptNameInput();
void MakeScriptMgrHeader();
void MakeScriptMgrCPP();

void MakeStateMgrHeader();
void MakeStateMgrCPP();


void GetAllContents();

void FindAllFiles(const wstring& path);

void SortExtention(const string& path, const string& extention);

void MakeStrHeader(const string& path, const string& symbol, const vector<string>& vec);

void MakeStateHeader(const string& path, const string& symbol, const vector<wstring>& vec);

void MakeStrHeaderFX();