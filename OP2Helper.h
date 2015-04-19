#pragma once

#include <Outpost2DLL/Outpost2DLL.h>	// Main Outpost 2 header to interface with the game

// Include other helper header files
#include "EnumTechID.h"
#include "EnumSoundID.h"
#include "BaseBuilder.h"
#include "BaseBuilderV2.h"
#include "ColonyType.h"
#include "Lava.h"

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


// *************************************************
// Note: The following are general purpose functions
//		 to help you implement your map.

// Starting Resources
void InitPlayerResources(int playerNum, const ResourceSet& resourceSet = CES1ResourceSet);

// Constructing Tubes/Walls
void CreateTubeOrWallLine(int x1, int y1, int x2, int y2, map_id type);

// Victory Conditions
void CreateStarshipVictoryCondition();
void CreateLastOneStandingVictoryCondition();
void CreateNoCommandCenterFailureCondition();


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
