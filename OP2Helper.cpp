#include "OP2Helper.h"


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



// Create a line of wall or tube
// Draws along the horizontal first:
//  If coordinates represent a bent wall/tube then it draws
//  horizontal between x1 and x2 (along y1) and then
//  vertical between y1 and y2 (along x2)
void CreateTubeOrWallLine(int x1, int y1, int x2, int y2, map_id type)
{
	// Determine which edges to draw along
	const int vert = x2;
	const int horz = y1;

	// Make sure (x1 <= x2) and (y1 <= y2)
	if (x1 > x2) { 
		x1 ^= x2; x2 ^= x1; x1 ^= x2;
	}
	if (y1 > y2) { 
		y1 ^= y2; y2 ^= y1; y1 ^= y2;
	}

	// Create horizontal section
	for (int i = x1; i <= x2; ++i) {
		TethysGame::CreateWallOrTube(i, horz, 0, type);
	}
	// Create vertical section
	for (int i = y1; i <= y2; ++i) {
		TethysGame::CreateWallOrTube(vert, i, 0, type);
	}
}


void CreateStarshipVictoryCondition()
{
	Trigger trig;

	// Create victory conditions for - Colony, Starship
	trig = CreateCountTrigger(1, 1, -1, mapEvacuationModule, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Evacuate 200 colonists to spacecraft");
	trig = CreateCountTrigger(1, 1, -1, mapFoodCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Evacuate 10000 units of food to spacecraft");
	trig = CreateCountTrigger(1, 1, -1, mapCommonMetalsCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Evacuate 10000 units of Commom Metals to spacecraft");
	trig = CreateCountTrigger(1, 1, -1, mapRareMetalsCargo, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Evacuate 10000 units of Rare Metals to spacecraft");
}


// For use in multiplayer. Note: Computer controlled opponents do not count towards this.
// You win when there is only one human opponent left or all surviving human players are allied.
// This also creates corresponding failure conditions
void CreateLastOneStandingVictoryCondition()
{
	Trigger trig = CreateOnePlayerLeftTrigger(1, 1, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Eliminate your opponents.");
}


// Fail if the number of active Command Centers becomes equal to 0.
void CreateNoCommandCenterFailureCondition(int playerNum)
{
	Trigger trig = CreateOperationalTrigger(1, 1, playerNum, mapCommandCenter, 0, cmpEqual, "NoResponseToTrigger");
	CreateFailureCondition(1, 1, trig, "");
}


LOCATION operator+ (const LOCATION &loc1, const LOCATION &loc2) {
	return LOCATION(loc1.x + loc2.x, loc1.y + loc2.y);
}

LOCATION operator- (const LOCATION &loc1, const LOCATION &loc2) {
	return LOCATION(loc1.x - loc2.x, loc1.y - loc2.y);
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
