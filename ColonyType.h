#pragma once

#include <Outpost2DLL/Outpost2DLL.h>
#include <array>

// Details of map_id enum are not needed here so just forward declare it
// This way we don't need to include Outpost2DLL.h (which speeds up the compile)
//enum map_id;


bool IsEdenOnlyWeapon(map_id weaponType);
bool IsPlymouthOnlyWeapon(map_id weaponType);
bool IsCommonWeapon(map_id weaponType);

bool IsEdenWeapon(map_id weaponType);
bool IsPlymouthWeapon(map_id weaponType);

bool IsBuilding(map_id mapID);
bool IsVehicle(map_id mapID);
bool IsUnit(map_id mapID);

extern std::array<map_id, 38> BuildingTypes;
extern std::array<map_id, 15> VehicleTypes;