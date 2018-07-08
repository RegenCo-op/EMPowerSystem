#ifndef THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h
#define THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h

#include "NewPing.h"
#include "PinDefinitions.h"

class TankLevelSensors
{
private:
	NewPing sensor_1;
	NewPing sensor_2;
public:
	TankLevelSensors();
};

#endif