#ifndef THERMALFLUIDCONTROLLER_THERMALFLUIDCONTROLLER_H
#define THERMALFLUIDCONTROLLER_THERMALFLUIDCONTROLLER_H

#include "TankLevelSensors/TankLevelSensors.h"
#include "PinDefinitions.h"

enum PumpStates
{
	kPumpOn,
	kPumpOff
};

class ThermalFluidController
{
private:
	PumpStates pump_state;
	TankLevelSensors tank_level_sensors;
public:
	ThermalFluidController(TankLevelSensorsConfig tank_level_sensors_config);
	void Run();
};


#endif