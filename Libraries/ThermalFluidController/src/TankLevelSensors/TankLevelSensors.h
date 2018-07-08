#ifndef THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_H
#define THERMALFLUIDCONTROLLER_TANKLEVELSENSORS_H

#include "NewPing.h"
#include "PinDefinitions.h"

struct TankLevelSensorsConfig
{
	int plausible_tank_level_min;
	int plausible_tank_level_max;
	int level_diff_spec_range;
	int full_level_pump_off;
	int tank_level_max_error;
};

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

	int ReadSensor1Level_();
	int ReadSensor2Level_();

public:
	TankLevelSensors(TankLevelSensorsConfig tank_level_sensors_config);

};

#endif