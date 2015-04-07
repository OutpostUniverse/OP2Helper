

#include "../Outpost2DLL/Outpost2DLL.h"	// Main Outpost 2 header to interface with the game


// Returns true if and only if the weapon if Eden specific
bool IsEdenOnlyWeapon(map_id weaponType)
{
	// Use switch case fallthrough (no break statement)
	switch(weaponType)
	{
	case mapLaser:
	case mapRailGun:
	case mapThorsHammer:
	case mapAcidCloud:
		return true;	// Yep
	}

	return false;	// Nope
}

// Returns true if and only if the weapon if Plymouth specific
bool IsPlymouthOnlyWeapon(map_id weaponType)
{
	// Use switch case fallthrough (no break statement)
	switch(weaponType)
	{
	case mapMicrowave:
	case mapStickyfoam:
	case mapRPG:
	case mapESG:
	case mapSupernova:
	case mapSupernova2:
	case mapEnergyCannon:
		return true;	// Yep
	}

	return false;	// Nope
}

// Returns true if weapon can be built by both colonies
bool IsCommonWeapon(map_id weaponType)
{
	// Use switch case fallthrough (no break statement)
	switch(weaponType)
	{
	case mapEMP:
	case mapStarflare:
	case mapStarflare2:
	case mapNormalUnitExplosion:
		return true;	// Yep
	}

	return false;	// Nope
}

// Returns true if Eden can build this weapon
bool IsEdenWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsEdenOnlyWeapon(weaponType));
}

// Returns true if Plymouth can build this weapon
bool IsPlymouthWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsPlymouthOnlyWeapon(weaponType));
}
