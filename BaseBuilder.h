#pragma once

#include "OP2Helper.h"


// Note: The following structures are used to 
//		 define resource and base layouts.

struct BeaconInfo
{
	int x;
	int y;
	enum map_id type;
	int rare;
	int bar;
	int variant;
};

struct BuildingInfo
{
	int x;
	int y;
	enum map_id type;
};

struct VehicleInfo
{
	int x;
	int y;
	enum map_id type;
	enum map_id weaponCargo;
	int dir;
};

struct TubeWallInfo
{
	int fromX;
	int fromY;
	int toX;
	int toY;
};

struct BaseInfo
{
	int numBeacons;
	struct BeaconInfo *beaconInfo;
	int numBuilding;
	struct BuildingInfo *bldnInfo;
	int numTubeLine;
	struct TubeWallInfo *tubeInfo;
	int numWallLine;
	struct TubeWallInfo *wallInfo;
	int numVehicle;
	struct VehicleInfo *vehicleInfo;
};

struct StartLocation
{
	int x;
	int y;
	BaseInfo *baseInfo;
};


// Used to make autosizing the arrays easier
#define NumberOf(array) (sizeof(array)/sizeof(array[0]))
// Used to make specifying the size of the array and the array easier
#define AutoSize(array) NumberOf(array), array
// Used to quickly fill BaseInfo structs
#define MakeBaseInfo(beacons, buildings, tubes, walls, vehicles) \
	{ AutoSize(beacons), AutoSize(buildings), AutoSize(tubes), AutoSize(walls), AutoSize(vehicles) }

// Deprecated
// ** Don't define these, as they'll cause redefinition errors here with old code **
//#define numof(array) (sizeof(array)/sizeof(array[0]))
//#define autosize(array) NumberOf(array), array


// Note: These are very useful for randomizing player start locations and
//		 beacon starting locations, among other things.
// Note: If used for placing beacons, it would be wise to have a seperate
//		 list for each starting location so not all the beacons end up
//		 appearing in a single player's base, and so you don't get only a
//		 single resource type placed on the map.
// Note: These functions are based off of RandomizeList and is used to
//		 generate a random permutation of the given list.

//void RandomizeResources(int numItems, struct BeaconInfo resources[]);
//void RandomizeStartingLocations(int numLocations, struct StartLocation location[]);

#define RandomizeResources RandomizeList
#define RandomizeStartingLocations RandomizeList

// Base/Resource Placement
void CreateBase(int player, const StartLocation& startLocation);
void CreateBase(int player, int x, int y, const BaseInfo &baseInfo);
void CreateBeacons(int numBeacons, const BeaconInfo beacon[]);
void CreateInitialCombatUnits(int playerNum, int x, int y);
