#include "Lava.h"

void SetLavaPossibleRegion(const MAP_RECT& mapRect)
{
	for (int x = mapRect.x1; x <= mapRect.x2; ++x)
	{
		for (int y = mapRect.y1; y <= mapRect.y2; ++y)
		{
			GameMap::SetLavaPossible(LOCATION(x, y), true);
		}
	}
}

void SetLavaPossibleAllSlowCells(const MAP_RECT& mapRect)
{
	int cellType;
	LOCATION location;

	for (int y = mapRect.y1; y <= mapRect.y2; ++y)
	{
		for (int x = mapRect.x1; x <= mapRect.x2; ++x)
		{
			location = LOCATION(x, y);
			cellType = GameMap::GetCellType(location);

			if (cellType == CellTypes::cellSlowPassible1 ||
				cellType == CellTypes::cellSlowPassible2)
			{
				GameMap::SetLavaPossible(location, true);
			}
		}
	}
}


void AnimateFlowSW(const LOCATION& loc)
{
	GameMap::SetTile(loc + LOCATION(1, 0), 0x453);
	GameMap::SetTile(loc, 0x447);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x45E);
	GameMap::SetTile(loc + LOCATION(1, 1), 0x469);
}

void AnimateFlowS(const LOCATION& loc)
{
	GameMap::SetTile(loc, 0x474);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x47E);
}

void AnimateFlowSE(const LOCATION& loc)
{
	GameMap::SetTile(loc, 0x489);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x4A0);
	GameMap::SetTile(loc + LOCATION(1, 1), 0x4AB);
	GameMap::SetTile(loc + LOCATION(1, 0), 0x494);
}


void FreezeFlowSW(const LOCATION& loc)
{
	GameMap::SetTile(loc + LOCATION(1, 0), 0x45A);
	GameMap::SetTile(loc, 0x44F);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x465);
	GameMap::SetTile(loc + LOCATION(1, 1), 0x470);
}

void FreezeFlowS(const LOCATION& loc)
{
	GameMap::SetTile(loc, 0x47B);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x486);
}

void FreezeFlowSE(const LOCATION& loc)
{
	GameMap::SetTile(loc, 0x490);
	GameMap::SetTile(loc + LOCATION(0, 1), 0x4A8);
	GameMap::SetTile(loc + LOCATION(1, 1), 0x4B2);
	GameMap::SetTile(loc + LOCATION(1, 0), 0x49C);
}