#include "OP2Helper.h"


// Note: Uses TethysGame::GetRand();
void RandomizeResources(int numItems, struct BeaconInfo resources[])
{
	int i;
	int next;
	struct BeaconInfo temp;

	// Randomly reorder the list (backwards)
	for (i = numItems-1; i; i--)
	{
		// Determine which item to place next in list
		next = TethysGame::GetRand(i+1);
		// Swap the 'next' item into place
		temp = resources[i];
		resources[i] = resources[next];
		resources[next] = temp;
	}
}

// Note: Uses TethysGame::GetRand();
void RandomizeStartingLocations(int numLocations, struct StartLocation location[])
{
	int i;
	int next;
	struct StartLocation temp;

	// Randomly reorder the list (backwards)
	for (i = numLocations-1; i; i--)
	{
		// Determine which of the remaining locations to place next in the list
		next = TethysGame::GetRand(i+1);
		// Swap with next list item
		temp = location[i];
		location[i] = location[next];
		location[next] = temp;
	}
}


void CreateBase(int player, int x, int y, struct BaseInfo &baseInfo)
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
		unit.DoSetLights(1);
	}
}

void CreateBeacons(int numBeacons, struct BeaconInfo beacon[])
{
	int i;

	for (i = 0; i < numBeacons; i++)
	{
		TethysGame::CreateBeacon(beacon[i].type, beacon[i].x, beacon[i].y, 
						beacon[i].rare, beacon[i].bar, beacon[i].variant);
	}
}

