#pragma once

// Main Outpost 2 header to interface with the game
#include <Outpost2DLL/Outpost2DLL.h>

// Include other helper header files
#include "BuildingBaysEnum.h"
#include "EnumTechID.h"
#include "EnumSoundID.h"
#include "BaseBuilder.h"
#include "ColonyType.h"
#include "Lava.h"
#include "Bulldozer.h"

// Useful macros
#define MkXY(x,y) (LOCATION(x+31,y-1))
#define MkRect(x1,y1,x2,y2) (MAP_RECT(LOCATION(x1+31,y1-1),LOCATION(x2+31,y2-1)))
#define XYPos(x,y) x+31,y-1
#define RectPos(x1,y1,x2,y2) x1+31,y1-1,x2+31,y2-1

// X and Y offset consts
const int X_ = 31;	// +32-1
const int Y_ = -1;	// -1

struct Resources
{
	int workers;
	int scientists;
	int kids;
	int food;
	int commonOre;
	int rareOre;
};
struct ResourceSet
{
	Resources level[3];		// Easy, Medium, Hard
};
extern const ResourceSet CES1ResourceSet;

// Global Operator overloads for LOCATION structure
LOCATION& operator+= (LOCATION& loc1, const LOCATION& loc2);
LOCATION& operator-= (LOCATION& loc1, const LOCATION& loc2);
LOCATION operator+ (LOCATION loc1, const LOCATION &loc2);
LOCATION operator- (LOCATION loc1, const LOCATION &loc2);
bool operator== (const LOCATION& loc1, const LOCATION &loc2);
bool operator!= (const LOCATION& loc1, const LOCATION &loc2);

// *************************************************
// Note: The following are general purpose functions
//		 to help you implement your map.

// Starting Resources
void InitPlayerResources(int playerNum, const ResourceSet& resourceSet = CES1ResourceSet);


// Create wall or tubes in a straight line or L pattern
// L patterns draw counter - clockwise between the two points
void CreateTubeLine(LOCATION loc1, LOCATION loc2);
void CreateWallLine(LOCATION loc1, LOCATION loc2);
void CreateLavaWallLine(LOCATION loc1, LOCATION loc2);
void CreateMicrobeWallLine(LOCATION loc1, LOCATION loc2);

// Record line of tubes or walls to a BuildingGroup in a straight line or L pattern
// L patterns draw counter - clockwise between the two points
void RecordTubeLine(BuildingGroup& buildingGroup, LOCATION loc1, LOCATION loc2);
void RecordWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2);
void RecordLavaWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2);
void RecordMicrobeWallLine(BuildingGroup& buildingGroup, const LOCATION& loc1, const LOCATION& loc2);

[[deprecated("CreateTubeOrWallLine is deprecated. Use CreateTubeLine or Create[Lava|Microbe]WallLine instead.")]]
void CreateTubeOrWallLine(int x1, int y1, int x2, int y2, map_id type);


// Victory Conditions
void CreateStarshipVictoryCondition();
void CreateLastOneStandingVictoryCondition();
void CreateNoCommandCenterFailureCondition(int playerNum = 0);


// Randomizing Lists
// Note: This function creates a random permutation of a given list.
//		 All permutations are equally likely to be generated.
// Note: Using these functions requires having a preset list of possible
//		 values or locations. This allows more control than having things
//		 spread all over the map completely random but still allows things
//		 to vary each time the level is played.
// Note: Uses TethysGame::GetRand();
template <class ListItemType>
void RandomizeList(int numItems, ListItemType list[])
{
	int next;
	ListItemType temp;

	// Randomly reorder the list (backwards)
	for (numItems--; numItems; numItems--)
	{
		// Determine which of the remaining locations to place next in the list
		next = TethysGame::GetRand(numItems+1);
		// Swap current item with next item
		temp = list[numItems];
		list[numItems] = list[next];
		list[next] = temp;
	}
}


// Centers the local player's screen on their CC, if they have one.
void CenterViewOnPlayerCC();
// Overload taking a location object
void CenterViewOn(enum PlayerNum playerNum, const LOCATION& location);

// To send message to all players, Set toPlayerNum to -1. 
// Default sound effect is phone ringing (sending text message to other player)
void AddMapMessage(const char* message, const Unit& sourceUnit, int soundIndex = SoundID::sndMessage2, int toPlayerNum = PlayerNum::PlayerAll);
void AddMapMessage(const char* message, const LOCATION& location, int soundIndex = SoundID::sndMessage2, int toPlayerNum = PlayerNum::PlayerAll);
void AddMapMessage(const char* message, int pixelX, int pixelY, int soundIndex = SoundID::sndMessage2, int toPlayerNum = PlayerNum::PlayerAll);
// Game message not tied to a map location (always full volume)
void AddGameMessage(const char* message, int soundIndex = SoundID::sndMessage2, int toPlayerNum = PlayerNum::PlayerAll);
