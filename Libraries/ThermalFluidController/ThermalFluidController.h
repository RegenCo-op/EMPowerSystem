#ifndef THERMALFLUIDCONTROLLER_THERMALFLUIDCONTROLLER_h
#define THERMALFLUIDCONTROLLER_THERMALFLUIDCONTROLLER_h

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
	void TankLevelSensorCheck();
public:
	ThermalFluidController();
	Run();
};


#endif