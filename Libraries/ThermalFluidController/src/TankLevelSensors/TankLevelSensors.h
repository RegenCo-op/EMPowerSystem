#ifndef THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h
#define THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_h

#include "NewPing.h"
#include "PinDefinitions.h"

class TankLevelSensors
{
private:
	NewPing sensor_1_;
	NewPing sensor_2_;
	int sensor_1_level_;
	int sensor_2_level_;
	int level_;
	bool half_fail_ = true;
	bool full_fail_ = true;

	int plausible_level_;
	int level_diff_spec_range_;
	int full_level_pump_off_;
	int tank_level_max_error_;

public:
	TankLevelSensors(int plausible_tank_level, int level_diff_spec_range, int full_level_pump_off, int tank_level_max_error);
};

#endif