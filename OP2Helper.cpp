#include "OP2Helper.h"


// Initializes player starting resources including:
//  Common Ore, Food Stored, Workers, Scientists, Children
void InitPlayerResources(int playerNum)
{
	_Player &player = Player[playerNum];

	switch(player.Difficulty())
	{
	case 0:		// Easy
		player.SetOre(5000);
		player.SetFoodStored(3000);
		player.SetWorkers(28);
		player.SetScientists(13);
		player.SetKids(15);
		break;
	case 1:		// Normal
		player.SetOre(4000);
		player.SetFoodStored(2000);
		player.SetWorkers(26);
		player.SetScientists(13);
		player.SetKids(15);
		break;
	case 2:		// Hard
		player.SetOre(3000);
		player.SetFoodStored(1000);
		player.SetWorkers(23);
		player.SetScientists(13);
		player.SetKids(15);
	}
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

	// Make sure (x1 < x2) and (y1 < y2)
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
	Trigger trig;

	trig = CreateOnePlayerLeftTrigger(1, 1, "NoResponseToTrigger");
	CreateVictoryCondition(1, 1, trig, "Eliminate your opponents.");
}


// (Player 0) fails if the number of active Command Centers becomes equal to 0.
void CreateNoCommandCenterFailureCondition()
{
	Trigger trig;

	trig = CreateOperationalTrigger(1, 1, 0, mapCommandCenter, 0, cmpEqual, "NoResponseToTrigger");
	CreateFailureCondition(1, 1, trig, "");
}



// Note: Uses TethysGame::GetRand();
void RandomizeList(int numItems, int list[])
{
	int i;
	int next;
	int temp;

	// Randomly reorder the list (backwards)
	for (i = numItems-1; i; i--)
	{
		// Determine which item to place next in list
		next = TethysGame::GetRand(i+1);
		// Swap the 'next' item into place
		temp = list[i];
		list[i] = list[next];
		list[next] = temp;
	}
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
