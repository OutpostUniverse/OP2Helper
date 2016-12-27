#include "Bulldozer.h"

const int FirstRockTileIndex = 439;
const int FirstSandTileIndex = 1206;

const int DozedMudTileIndex = 414;
const int DozedRockTileIndex = 921;
const int DozedSandTileIndex = 1670;

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

void Doze(const LOCATION &loc)
{
	if (!IsDozeable(loc))
	{
		return;
	}

	int originalTileIndex = GameMap::GetTile(loc);

	if (originalTileIndex < FirstRockTileIndex)
	{
		GameMap::SetTile(loc, DozedMudTileIndex);
	}
	else if (originalTileIndex < FirstSandTileIndex)
	{
		GameMap::SetTile(loc, DozedRockTileIndex);
	}
	else
	{
		GameMap::SetTile(loc, DozedSandTileIndex);
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