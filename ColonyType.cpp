#include "ColonyType.h"

// The following functions use switch case fallthrough (no break statement).

bool IsEdenOnlyWeapon(map_id weaponType)
{
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

bool IsPlymouthOnlyWeapon(map_id weaponType)
{
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

bool IsCommonWeapon(map_id weaponType)
{
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

bool IsEdenWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsEdenOnlyWeapon(weaponType));
}

bool IsPlymouthWeapon(map_id weaponType)
{
	return (IsCommonWeapon(weaponType) || IsPlymouthOnlyWeapon(weaponType));
}

bool IsEdenOnlyBuilding(map_id buildingType)
{
	switch (buildingType)
	{
	case mapMagmaWell:
	case mapMeteorDefense:
	case mapGeothermalPlant:
	case mapConsumerFactory:
	case mapObservatory:
	case mapAdvancedResidence:
		return true;
	}

	return false;
}

bool IsPlymouthOnlyBuilding(map_id buildingType)
{
	switch (buildingType)
	{
	case mapForum:
	case mapMHDGenerator:
	case mapArachnidFactory:
	case mapReinforcedResidence:
		return true;
	}

	return false;
}

bool IsEdenBuilding(map_id buildingType)
{
	return IsBuilding(buildingType) && !IsPlymouthOnlyBuilding(buildingType);
}

bool IsPlymouthBuilding(map_id buildingType)
{
	return IsBuilding(buildingType) && !IsEdenOnlyBuilding(buildingType);
}

bool IsCommonBuilding(map_id buildingType)
{
	return IsBuilding(buildingType) && !IsEdenOnlyBuilding(buildingType) && !IsPlymouthOnlyBuilding(buildingType);
}

bool IsEdenOnlyVehicle(map_id vehicleType)
{
	switch (vehicleType)
	{
	case mapGeoCon:
	case mapRepairVehicle:
		return true;
	}

	return false;
}

bool IsPlymouthOnlyVehicle(map_id vehicleType)
{
	switch (vehicleType)
	{
	case mapSpider:
	case mapScorpion:
		return true;
	}

	return false;
}

bool IsEdenVehicle(map_id vehicleType)
{
	return IsVehicle(vehicleType) && !IsPlymouthOnlyVehicle(vehicleType);
}

bool IsPlymouthVehicle(map_id vehicleType)
{
	return IsVehicle(vehicleType) && !IsEdenOnlyVehicle(vehicleType);
}

bool IsCommonVehicle(map_id vehicleType)
{
	return IsVehicle(vehicleType) && !IsEdenOnlyVehicle(vehicleType) && !IsPlymouthOnlyVehicle(vehicleType);
}

bool IsBuilding(map_id buildingType)
{
	// mapCommonOreMine and mapTokamak are respectively the first and last building indices
	return ((buildingType >= map_id::mapCommonOreMine && buildingType <= map_id::mapTokamak));
}

bool IsVehicle(map_id vehicleType)
{
	// mapCargoTruck and mapEarthworker are respectively the first and last building indices
	return ((vehicleType >= map_id::mapCargoTruck) && (vehicleType <= map_id::mapEarthworker));
}

bool IsUnit(map_id unitType)
{
	return IsBuilding(unitType) || IsVehicle(unitType);
}