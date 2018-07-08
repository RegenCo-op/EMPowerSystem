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
public:
	ThermalFluidController(int plausible_tank_level, int level_diff_spec_range, int full_level_pump_off, int tank_level_max_error);
	void Run();
};


#endif