#pragma once

#include <Outpost2DLL/Outpost2DLL.h>
#include "OP2Helper.h"

// Sets all tiles in a MAP_RECT to lava-possible.
void SetLavaPossibleRegion(const MAP_RECT& mapRect);

// Sets all S1 and S2 Celltypes in a MAP_RECT to lava-possible
void SetLavaPossibleAllSlowCells(const MAP_RECT& mapRect);

//Functions to start the lava flow animation on the side of a volcano
void AnimateFlowSW(const LOCATION& TopLeftMostTile);
void AnimateFlowS(const LOCATION& TopLeftMostTile);
void AnimateFlowSE(const LOCATION& TopLeftMostTile);

//Functions to stop the lava flow animation on the side of a volcano
void FreezeFlowSW(const LOCATION& TopLeftMostTile);
void FreezeFlowS(const LOCATION& TopLeftMostTile);
void FreezeFlowSE(const LOCATION& TopLeftMostTile);


// Note: The structs Range and LavaPossibleInfo emulate how official Sierra maps
//       define data about where lava can expand on the map.

// Size: 0x8
struct Range
{
	int start;
	int end;
};

// Size: 0x1C  [0x1C = 28, or 7 dwords]
struct LavaPossibleInfo
{
	int x;
	Range y1;
	Range y2;
	Range y3;
};
