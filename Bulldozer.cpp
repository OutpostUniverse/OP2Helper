#include "Bulldozer.h"

const int lastMudTileIndex = 438;
const int lastRockTileIndex = 1205;

const int dozedMudTileIndex = 414;
const int dozedRockTileIndex = 921;
const int dozedSandTileIndex = 1670;

bool IsDozeable(const LOCATION &location)
{
	int currentCellType = GameMap::GetCellType(location);

	return
		currentCellType == CellTypes::cellFastPassible1 ||
		currentCellType == CellTypes::cellFastPassible2 ||
		currentCellType == CellTypes::cellMediumPassible1 ||
		currentCellType == CellTypes::cellMediumPassible2 ||
		currentCellType == CellTypes::cellSlowPassible1 ||
		currentCellType == CellTypes::cellSlowPassible2;
}

void Doze(const LOCATION& loc)
{
	if (!IsDozeable(loc)) {
		return;
	}

	int originalTileIndex = GameMap::GetTile(loc);

	if (originalTileIndex <= lastMudTileIndex)
	{
		GameMap::SetTile(loc, dozedMudTileIndex);
	}
	else if (originalTileIndex <= lastRockTileIndex)
	{
		GameMap::SetTile(loc, dozedRockTileIndex);
	}
	else
	{
		GameMap::SetTile(loc, dozedSandTileIndex);
	}

	GameMap::SetCellType(loc, CellTypes::cellDozedArea);
}

void Doze(const MAP_RECT &mapRect)
{
	for (int y = 0; y < mapRect.Height(); ++y)
	{
		for (int x = 0; x < mapRect.Width(); ++x)
		{
			LOCATION dozeLoc(mapRect.x1 + x, mapRect.y1 + y);
			Doze(dozeLoc);
		}
	}
}
