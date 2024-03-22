#pragma once

#define TILEBLOCKSIZEX 10
#define TILEBLOCKSIZEY 8

#define STAGETILEROW 4
#define STAGETILECOL 4


enum class StagePackList {
    Dwelling,
    END,
};

extern string StagePackListString[(int)StagePackList::END];