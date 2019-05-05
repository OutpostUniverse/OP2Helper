#include "OP2Helper.h"
#include <utility>
#include <functional>


// (Workers, Scientists, Kids, Food, Common Ore, [Rare Ore])  (Zero-fill to end if list is short)
const ResourceSet CES1ResourceSet = {
	{
		{ 28, 13, 15, 3000, 5000 },		// Easy
		{ 26, 13, 15, 2000, 4000 },		// Medium
		{ 23, 13, 15, 1000, 3000 },		// Hard
	}
};
const ResourceSet MultiResourceSet = {
	{
		{ 27, 18, 22, 3000, 6000 },		// Easy
		{ 24, 15, 20, 2000, 4000 },		// Medium
		{ 20, 12, 18, 1000, 2000 },		// Hard
	}
};

// Perform function discretely along a line or L shape
void ExecuteAcrossLine(LOCATION loc1, LOCATION loc2, const std::function <void(int x, int y)>& function);

// Assuming loc1 and loc2 form a rectangle:
//  Set loc1 to the top left
//  Set loc2 to the bottom right
void SwapLocations(LOCATION& loc1, LOCATION& loc2);

// Initializes player starting resources including:
//  Workers, Scientists, Children, Food Stored, Common Ore, Rare Ore
void InitPlayerResources(int playerNum, const ResourceSet& resourceSet)
{
	// Cache a reference to the specified Player
	_Player &player = Player[playerNum];
	// Cache a reference to the resource settings for Player's difficulty level
	const Resources& resources = resourceSet.level[player.Difficulty()];

	// Set the player's resources
	player.SetWorkers(resources.workers);
	player.SetScientists(resources.scientists);
	player.SetKids(resources.kids);
	player.SetFoodStored(resources.food);
	player.SetOre(resources.commonOre);
	player.SetRareOre(resources.rareOre);
}


void CreateTubeLine(LOCATION loc1, LOCATION loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[](int x, int y) { TethysGame::CreateWallOrTube(x, y, 0, map_id::mapTube); }
	);
}

void CreateWallLine(LOCATION loc1, LOCATION loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[](int x, int y) { TethysGame::CreateWallOrTube(x, y, 0, map_id::mapWall); }
	);
}

void CreateLavaWallLine(LOCATION loc1, LOCATION loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[](int x, int y) { TethysGame::CreateWallOrTube(x, y, 0, map_id::mapLavaWall); }
	);
}

void CreateMicrobeWallLine(LOCATION loc1, LOCATION loc2)
{
	ExecuteAcrossLine(loc1, loc2, 
		[](int x, int y) { TethysGame::CreateWallOrTube(x, y, 0, map_id::mapMicrobeWall); }
	);
}

void RecordTubeLine(BuildingGroup& buildingGroup, LOCATION loc1, LOCATION loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[ &buildingGroup ] (int x, int y) { LOCATION location(x, y); buildingGroup.RecordTube(location); }
	);
}

void RecordWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[ &buildingGroup ] (int x, int y) { LOCATION location(x, y); buildingGroup.RecordWall(location, map_id::mapWall); }
	);
}

void RecordLavaWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[ &buildingGroup ] (int x, int y) { LOCATION location(x, y); buildingGroup.RecordWall(location, map_id::mapLavaWall); }
	);
}

void RecordMicrobeWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2)
{
	ExecuteAcrossLine(loc1, loc2,
		[ &buildingGroup ] (int x, int y) { LOCATION location(x, y); buildingGroup.RecordWall(location, map_id::mapMicrobeWall); }
	);
}

void ExecuteAcrossLine(LOCATION loc1, LOCATION loc2, const std::function <void(int x, int y)>& function)
{
	// Determine edges to record along
	const int vertEdge = loc2.x;
	const int horizEdge = loc1.y;
	SwapLocations(loc1, loc2);

	// Record horizontal section
	for (int x = loc1.x; x <= loc2.x; ++x) {
		function(x, horizEdge);
	}
	// Record vertical section
	for (int y = loc1.y; y <= loc2.y; ++y) {
		function(vertEdge, y);
	}
}

void SwapLocations(LOCATION& loc1, LOCATION& loc2)
{
	// Make sure (x1 <= x2) and (y1 <= y2)
	if (loc1.x > loc2.x) {
		std::swap(loc1.x, loc2.x);
	}
	if (loc1.y > loc2.y) {
		std::swap(loc1.y, loc2.y);
	}
}

// Create a line of wall or tube
// Draws along the horizontal first:
//  If coordinates represent a bent wall/tube then it draws
//  horizontal between x1 and x2 (along y1) and then
//  vertical between y1 and y2 (along x2)
void CreateTubeOrWallLine(int x1, int y1, int x2, int y2, map_id type)
{
	const LOCATION loc1(x1, y1);
	const LOCATION loc2(x2, y2);

	switch (type)
	{
	case mapTube: {
		CreateTubeLine(loc1, loc2);
		return;
	}
	case mapWall: {
		CreateWallLine(loc1, loc2);
		return;
	}
	case mapLavaWall: {
		CreateLavaWallLine(loc1, loc2);
		return;
	}
	case mapMicrobeWall: {
		CreateMicrobeWallLine(loc1, loc2);
		return;
	}
	}
}


void CreateStarshipVictoryCondition()
{
	Trigger trigger;

	// Create victory conditions for - Colony, Starship
	trigger = CreateCountTrigger(1, 1, -1, mapEvacuationModule, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trigger, "Evacuate 200 colonists to spacecraft");
	trigger = CreateCountTrigger(1, 1, -1, mapFoodCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trigger, "Evacuate 10000 units of food to spacecraft");
	trigger = CreateCountTrigger(1, 1, -1, mapCommonMetalsCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trigger, "Evacuate 10000 units of Commom Metals to spacecraft");
	trigger = CreateCountTrigger(1, 1, -1, mapRareMetalsCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trigger, "Evacuate 10000 units of Rare Metals to spacecraft");
}


// For use in multiplayer. Note: Computer controlled opponents do not count towards this.
// You win when there is only one human opponent left or all surviving human players are allied.
// This also creates corresponding failure conditions
void CreateLastOneStandingVictoryCondition()
{
	Trigger trigger = CreateOnePlayerLeftTrigger(1, 1, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trigger, "Eliminate your opponents.");
}


// Fail if the number of active Command Centers becomes equal to 0.
void CreateNoCommandCenterFailureCondition(int playerNum)
{
	Trigger trigger = CreateOperationalTrigger(1, 1, playerNum, mapCommandCenter, 0, cmpEqual, "NoResponseToTrigger");
	CreateFailureCondition(1, 1, trigger, "");
}


LOCATION& operator+= (LOCATION& loc1, const LOCATION& loc2) {
	loc1.x += loc2.x;
	loc1.y += loc2.y;

	return loc1;
}

LOCATION& operator-= (LOCATION& loc1, const LOCATION& loc2) {
	loc1.x -= loc2.x;
	loc1.y -= loc2.y;

	return loc1;
}

LOCATION operator+ (LOCATION loc1, const LOCATION &loc2) {
	return loc1 += loc2;
}

LOCATION operator- (LOCATION loc1, const LOCATION &loc2) {
	return loc1 -= loc2;
}

bool operator== (const LOCATION& loc1, const LOCATION &loc2) {
	return (loc1.x == loc2.x && loc1.y == loc2.y);
}

bool operator!= (const LOCATION& loc1, const LOCATION &loc2) {
	return !(loc1 == loc2);
}

// Centers the local player's view on their CommandCenter, if they have one.
void CenterViewOnPlayerCC() {
	Unit commandCenter;
	int localPlayer = TethysGame::LocalPlayer();
	PlayerBuildingEnum commandCenterEnum(localPlayer, mapCommandCenter);

	// Find first Command Center (if one exists)
	if (commandCenterEnum.GetNext(commandCenter)) {
		LOCATION commandCenterLoc = commandCenter.Location();
		Player[localPlayer].CenterViewOn(commandCenterLoc.x, commandCenterLoc.y);
	}
}

void AddMapMessage(const char* message, const Unit& sourceUnit, int soundIndex, int toPlayerNum) {
	// Message is not modified by Outpost 2, but was not declared as const. Cast to avoid warnings/errors.
	TethysGame::AddMessage(sourceUnit, const_cast<char*>(message), toPlayerNum, soundIndex);
}

void AddMapMessage(const char* message, const LOCATION& location, int soundIndex, int toPlayerNum)
{
	// Convert location from tiles to pixels
	AddMapMessage(message, location.x * 32 + 16, location.y * 32 + 16, soundIndex, toPlayerNum);
}

void AddMapMessage(const char* message, int pixelX, int pixelY, int soundIndex, int toPlayerNum)
{
	// Message is not modified by Outpost 2, but was not declared as const. Cast to avoid warnings/errors.
	TethysGame::AddMessage(pixelX, pixelY, const_cast<char*>(message), toPlayerNum, soundIndex);
}

void AddGameMessage(const char* message, int soundIndex, int toPlayerNum)
{
	AddMapMessage(message, -1, -1, soundIndex, toPlayerNum);
}
