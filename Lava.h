#pragma once


// Note: This file contains code to emulate how official Sierra maps seem to be built.
// These structs are used to define data about where lava can expand on the map.


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
