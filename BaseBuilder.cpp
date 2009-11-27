#include "OP2Helper.h"


void CreateBase(int player, const StartLocation& startLocation)
{
	// Center the player's view on the center of the base
	Player[player].CenterViewOn(startLocation.x, startLocation.y);
	// Make sure a base was specified
	if (startLocation.baseInfo != 0)
	{
		// Create the player's base
		CreateBase(player, startLocation.x, startLocation.y, *startLocation.baseInfo);
	}
}


void CreateBase(int player, int x, int y, const BaseInfo& baseInfo)
{
	int i;
	int curX, curY;
	int curX2, curY2;
	Unit unit;

	// Create the base beacon set
	for (i = 0; i < baseInfo.numBeacons; i++)
	{
		BeaconInfo &curBeacon = baseInfo.beaconInfo[i];
		curX = x + curBeacon.x;
		curY = y + curBeacon.y;
		TethysGame::CreateBeacon(curBeacon.type, curX, curY, curBeacon.rare,
						curBeacon.bar, curBeacon.variant);
	}

	// Create the buildings
	for (i = 0; i < baseInfo.numBuilding; i++)
	{
		BuildingInfo &curItem = baseInfo.bldnInfo[i];
		curX = x + curItem.x;
		curY = y + curItem.y;
		TethysGame::CreateUnit(unit, curItem.type, LOCATION(curX, curY), 
						player, mapNone, 0);
	}

	// Create the tube lines
	for (i = 0; i < baseInfo.numTubeLine; i++)
	{
		TubeWallInfo &curItem = baseInfo.tubeInfo[i];
		curX = x + curItem.fromX;
		curY = y + curItem.fromY;
		curX2 = x + curItem.toX;
		curY2 = y + curItem.toY;
		CreateTubeOrWallLine(curX, curY, curX2, curY2, mapTube);
	}

	// Create the wall lines
	for (i = 0; i < baseInfo.numWallLine; i++)
	{
		TubeWallInfo &curItem = baseInfo.wallInfo[i];
		curX = x + curItem.fromX;
		curY = y + curItem.fromY;
		curX2 = x + curItem.toX;
		curY2 = y + curItem.toY;
		CreateTubeOrWallLine(curX, curY, curX2, curY2, mapWall);
	}

	// Create the vehicles
	for (i = 0; i < baseInfo.numVehicle; i++)
	{
		VehicleInfo &curItem = baseInfo.vehicleInfo[i];
		curX = x + curItem.x;
		curY = y + curItem.y;
		TethysGame::CreateUnit(unit, curItem.type, LOCATION(curX, curY), 
						player, curItem.weaponCargo, curItem.dir);
		unit.DoSetLights(true);
	}
}

void CreateBeacons(int numBeacons, const BeaconInfo beacon[])
{
	int i;

	for (i = 0; i < numBeacons; i++)
	{
		TethysGame::CreateBeacon(beacon[i].type, beacon[i].x, beacon[i].y, 
						beacon[i].rare, beacon[i].bar, beacon[i].variant);
	}
}

void CreateInitialCombatUnits(int playerNum, int x, int y)
{
	Unit unit;
	int numUnits = TethysGame::InitialUnits();		// Number of combat units to start with
	map_id weaponType = (Player[playerNum].IsEden() == 0) ? mapMicrowave : mapLaser;	// Set weapon based on colony type

	for (; numUnits > 0; --numUnits)
	{
		// Create the unit
		TethysGame::CreateUnit(unit, mapLynx, LOCATION(x, y), playerNum, weaponType, 0);
		// Turn on it's lights
		unit.DoSetLights(true);
	}
}
