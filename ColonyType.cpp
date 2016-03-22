#include "ColonyType.h"
//#include <Outpost2DLL/Outpost2DLL.h>	// Main Outpost 2 header to interface with the game

// Returns true only if the weapon is Eden specific
bool IsEdenOnlyWeapon(map_id weaponType)
{
	// Use switch case fallthrough (no break statement)
	switch(weaponType)
	{
	case mapLaser:
	case mapRailGun:
	case mapThorsHammer:
	case mapAcidCloud:
		return true;
	}

	return false;
}

// Returns true only if the weapon is Plymouth specific
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
		return true;
	}

	return false;
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
		return true;
	}

	return false;
}

// Returns true if Eden can build the weapon
bool IsEdenWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsEdenOnlyWeapon(weaponType));
}

// Returns true if Plymouth can build the weapon
bool IsPlymouthWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsPlymouthOnlyWeapon(weaponType));
}

// Returns true if the map_id is a building.
bool IsBuilding(map_id mapType)
{
	return std::find(BuildingTypes.begin(), BuildingTypes.end(), mapType) != BuildingTypes.end();
}

// Returns true if the building is a vehicle.
bool IsVehicle(map_id mapType)
{
	return std::find(VehicleTypes.begin(), VehicleTypes.end(), mapType) != VehicleTypes.end();
}

// Returns true if the map_id is either a vehicle or a building.
bool IsUnit(map_id mapType)
{
	return IsBuilding(mapType) || IsVehicle(mapType);
}

std::array<map_id, 38> BuildingTypes{
	mapCommonOreMine,
	mapRareOreMine,
	mapGuardPost,
	mapLightTower,
	mapCommonStorage,
	mapRareStorage,
	mapForum,
	mapCommandCenter,
	mapMHDGenerator,
	mapResidence,
	mapRobotCommand,
	mapTradeCenter,
	mapBasicLab,
	mapMedicalCenter,
	mapNursery, mapSolarPowerArray,
	mapRecreationFacility,
	mapUniversity,
	mapAgridome,
	mapDIRT,
	mapGarage,
	mapMagmaWell,
	mapMeteorDefense,
	mapGeothermalPlant,
	mapArachnidFactory,
	mapConsumerFactory,
	mapStructureFactory,
	mapVehicleFactory,
	mapStandardLab,
	mapAdvancedLab,
	mapObservatory,
	mapReinforcedResidence,
	mapAdvancedResidence,
	mapCommonOreSmelter,
	mapSpaceport,
	mapRareOreSmelter,
	mapGORF,
	mapTokamak
};

std::array<map_id, 15> VehicleTypes{
	mapCargoTruck,
	mapConVec,
	mapSpider,
	mapScorpion,
	mapLynx,
	mapPanther,
	mapTiger,
	mapRoboSurveyor,
	mapRoboMiner,
	mapGeoCon,
	mapScout,
	mapRoboDozer,
	mapEvacuationTransport,
	mapRepairVehicle,
	mapEarthworker
};