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
	int i;
	int vert;
	int horz;

	// Determine which edges to draw along
	vert = x2;
	horz = y1;

	// Make sure (x1 <= x2) and (y1 <= y2)
	if (x1 > x2){ x1 ^= x2; x2 ^= x1; x1 ^= x2;	}
	if (y1 > y2){ y1 ^= y2; y2 ^= y1; y1 ^= y2;	}

	// Create horizontal section
	for (i = x1; i <= x2; i++)
		TethysGame::CreateWallOrTube(i, horz, 0, type);
	// Create vertical section
	for (i = y1; i <= y2; i++)
		TethysGame::CreateWallOrTube(vert, i, 0, type);
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
	Trigger& trig = CreateOnePlayerLeftTrigger(1, 1, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Eliminate your opponents.");
}


// Fail if the number of active Command Centers becomes equal to 0.
void CreateNoCommandCenterFailureCondition(int playerNum)
{
	Trigger& trig = CreateOperationalTrigger(1, 1, playerNum, mapCommandCenter, 0, cmpEqual, "NoResponseToTrigger");
	CreateFailureCondition(1, 1, trig, "");
}
