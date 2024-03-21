#pragma once
#include "macro.h"
#include "strings.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include <Engine/global.h>
#include <Scripts/global.h>
#include <string.h>
using std::string;
using std::wstring;


#include <fstream>
using std::endl;
using std::ifstream;
using std::ofstream;


#include <Engine/CAssetMgr.h>
#define ASSET_LOAD(type, RelPath) CAssetMgr::GetInst()->Load<type>(RelPath, RelPath)

#include "utils.h"