#include "pch.h"


extern vector<string> TileBlockTypeStrings =
{ "NONE", "Entrance", "Entrance_Fall", "Exit", "Exit_Drop", "Normal", "Fall", "Drop", "Fall_Drop", "Side", "NeverCrash"};

extern string StagePackListString[(int)StagePackList::END] = {"Dwelling.sp"};


extern int nrow[] = { 0, 1, 0, -1 };
extern int ncol[] = { 1, 0, -1, 0 };