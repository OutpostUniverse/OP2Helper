#pragma once


// Details of map_id enum are not needed here so just forward declare it
// This way we don't need to include Outpost2DLL.h (which speeds up the compile)
enum map_id;


bool IsEdenOnlyWeapon(map_id weaponType);
bool IsPlymouthOnlyWeapon(map_id weaponType);
bool IsCommonWeapon(map_id weaponType);

bool IsEdenWeapon(map_id weaponType);
bool IsPlymouthWeapon(map_id weaponType);
