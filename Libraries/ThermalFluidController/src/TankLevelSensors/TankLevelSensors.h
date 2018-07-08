#ifndef THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h
#define THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h

#include "NewPing.h"

class TankLevelSensors
{
private:
	NewPing sensor_1;
	NewPing sensor_2;
public:
	ThermalFluidController();

};

#endif