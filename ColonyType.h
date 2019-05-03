#pragma once

#include <Outpost2DLL/Outpost2DLL.h>


// Returns true if the map_id is a weapon native only to Eden
bool IsEdenOnlyWeapon(map_id weaponType);

// Returns true if the map_id is a weapon native only to Plymouth
bool IsPlymouthOnlyWeapon(map_id weaponType);

// Returns true if the map_id is a weapon that is native to both colonies
bool IsCommonWeapon(map_id weaponType);

// Returns true if the map_id is a weapon that can be built by Eden
bool IsEdenWeapon(map_id weaponType);

// Returns true if the map_id is a weapon that can be built by Plymouth
bool IsPlymouthWeapon(map_id weaponType);

// Returns true if the map_id is a weapon
bool IsWeapon(map_id mapID);

// Returns true if the map_id is a building that is native only to Eden
bool IsEdenOnlyBuilding(map_id buildingType);

// Returns true if the map_id is a building that is native only to Plymouth
bool IsPlymouthOnlyBuilding(map_id buildingType);

// Returns true if the map_id is a building that Eden can construct
bool IsEdenBuilding(map_id buildingType);

// Returns true if the map_id is a building that Plymouth can construct
bool IsPlymouthBuilding(map_id buildingType);

// Returns true if the map_id is a building that is native to both colonies
bool IsCommonBuilding(map_id buildingType);

// Returns true if the map_id is a vehicle that is native to Eden only
bool IsEdenOnlyVehicle(map_id vehicleType);

// Returns true if the map_id is a vehicle that is native to Plymouth only
bool IsPlymouthOnlyVehicle(map_id vehicleType);

// Returns true if the map_id is a vehicle that can be built by Eden
bool IsEdenVehicle(map_id vehicleType);

// Returns true if the map_id is a vehicle that can be built by Plymouth
bool IsPlymouthVehicle(map_id vehicleType);

// Returns true if the map_id is a vehicle that is native to both colonies
bool IsCommonVehicle(map_id vehicleType);

// Returns true if the map_id is a building
bool IsBuilding(map_id mapID);

// Returns true if the map_id is a vehicle
bool IsVehicle(map_id mapID);

// Returns true if the map_id is either a vehicle or a building
bool IsUnit(map_id mapID);

// Returns true if the map_id is any form of tube or wall
bool IsTubeOrWall(map_id mapID);
