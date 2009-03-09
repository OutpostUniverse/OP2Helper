
// ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING **
// *******************************************************************************
// *******************************************************************************
// **NOTE**: This feature is still incomplete! Please do not try to use this file!
// *******************************************************************************
// *******************************************************************************
// ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING ** WARNING **



// Redefinition error protection
#ifndef BaseBuilderV2_H
#define BaseBuilderV2_H


#include "..\Outpost2DLL\Outpost2Dll.h"



// -----------------------------------------
// ------------ Interface class ------------
// -----------------------------------------


// Common Interface class
class IBaseComponent
{
public:
	virtual void Create(int playerNum, int x, int y) = 0;
};


// -----------------------------------------
// ------------ Derived classes ------------
// -----------------------------------------


// Building
class BuildingComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
		Unit unit;
		TethysGame::CreateUnit(unit, buildingType, LOCATION(x + xOffset, y + yOffset), playerNum, mapNone, 0);
	}

	// Constructor
	BuildingComponent(int xOffset, int yOffset, map_id buildingType)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->buildingType = buildingType;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
	map_id buildingType;
};


// Guard Posts
class GuardPostComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
		Unit unit;
		TethysGame::CreateUnit(unit, mapGuardPost, LOCATION(x + xOffset, y + yOffset), playerNum, turretType, 0);
	}

	// Constructor
	GuardPostComponent(int xOffset, int yOffset, map_id turretType)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->turretType = turretType;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
	map_id turretType;
};


// Structure Factory (holding non-GP kits)
class StructureFactoryComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
		Unit unit;
		TethysGame::CreateUnit(unit, mapStructureFactory, LOCATION(x + xOffset, y + yOffset), playerNum, mapNone, 0);

		int i;
		for (i = 0; i < 6; i++)
			unit.SetFactoryCargo(i, kitType[i], mapNone);
	}

	// Constructor (for non-GP kits)
	StructureFactoryComponent(int xOffset, int yOffset, map_id kitType1 = mapNone, map_id kitType2 = mapNone, map_id kitType3 = mapNone, map_id kitType4 = mapNone, map_id kitType5 = mapNone, map_id kitType6 = mapNone)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->kitType[0] = kitType1;
		this->kitType[1] = kitType2;
		this->kitType[2] = kitType3;
		this->kitType[3] = kitType4;
		this->kitType[4] = kitType5;
		this->kitType[5] = kitType6;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
	map_id kitType[6];
};

// Garage **


// Vehicle
class VehicleComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
		Unit unit;
		TethysGame::CreateUnit(unit, vehicleType, LOCATION(x + xOffset, y + yOffset), playerNum, cargoType, 0);
		unit.DoSetLights(bLightsOn);
	}

	// Constructor
	VehicleComponent(int xOffset, int yOffset, map_id vehicleType, map_id cargoType = mapNone, int direction = 0, bool bLightsOn = true)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->vehicleType = vehicleType;
		this->cargoType = cargoType;
		this->direction = direction;
		this->bLightsOn = bLightsOn;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
	map_id vehicleType;
	map_id cargoType;
	int direction;
	bool bLightsOn;
};


// Cargo Truck
class CargoTruckComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
		Unit unit;
		TethysGame::CreateUnit(unit, mapCargoTruck, LOCATION(x + xOffset, y + yOffset), playerNum, mapNone, 0);
		unit.DoSetLights(bLightsOn);
		unit.SetTruckCargo(cargoType, amount);
	}

	// Constructor
	CargoTruckComponent(int xOffset, int yOffset, Truck_Cargo cargoType, int amount, int direction = 0, bool bLightsOn = true)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->cargoType = cargoType;
		this->amount = amount;
		this->direction = direction;
		this->bLightsOn = bLightsOn;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
	Truck_Cargo cargoType;
	int amount;
	int direction;
	bool bLightsOn;
};


// Tube
class TubeComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
// **		CreateTubeOrWallLine(x + x1, y + y1, x + x2, y + y2, mapTube);
	}

	// Constructor
	TubeComponent(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	};

private:
	// Member variables
	int x1, y1, x2, y2;
};


// Wall
class WallComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
// **		CreateTubeOrWallLine(x + x1, y + y1, x + x2, y + y2, wallType);
	}

	// Constructor
	WallComponent(int x1, int y1, int x2, int y2, map_id wallType = mapWall)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->wallType = wallType;
	};

private:
	// Member variables
	int x1, y1, x2, y2;
	map_id wallType;
};


// Group
class GroupComponent : public IBaseComponent
{
public:
	// Inherited virtual function
	void Create(int playerNum, int x, int y)	// Final
	{
	}

	// Constructor
	GroupComponent(int xOffset, int yOffset, ...)
	{
		this->xOffset = xOffset;
		this->yOffset = yOffset;
	};

private:
	// Member variables
	int xOffset;
	int yOffset;
};


#endif	// End Refefinition error protection
