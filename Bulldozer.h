#pragma once

#include "Outpost2DLL\Outpost2DLL.h"

// Checks if a LOCATION on the map can be bulldozed.
bool IsDozeable(const LOCATION& loc);

// Dozes a LOCATION only if LOCATION is valid to doze.
void Doze(const LOCATION& loc);

// Dozes all LOCATIONs contained in MAP_RECT that are valid to doze.
void Doze(const MAP_RECT& mapRect);
