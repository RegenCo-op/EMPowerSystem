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
	int full_level_pump_on;
	int tank_level_max_error;
};

class TankLevelSensors
{
private:
	NewPing sensor_1_;
	NewPing sensor_2_;
	int sensor_1_level_;
	int sensor_2_level_;
	int tank_level_;

	int plausible_level_;
	int level_diff_spec_range_;
	int full_level_pump_off_;
	int full_level_pump_on_;
	int tank_level_max_error_;

	bool sensor_1_is_plausible_;
	bool sensor_2_is_plausible_;

	int ReadSensor1Level_();
	int ReadSensor2Level_();


	bool CheckTankLevelPlausibility();
	bool CheckTankLevelSensorDifferential();
	bool CheckTankLevel(bool pump_on);

public:
	TankLevelSensors(TankLevelSensorsConfig tank_level_sensors_config);

	//Checks tank level using the ultrasonic sensors.
	//Checks if the sensors are plausible, if both implausible
	//returns false. If only one plausible, uses plausible sensor
	//for tank level. If both plausible, compares
	//sensors to see if they are reading close to the same
	//level. If they are close averages the two values for the tank level,
	//otherwise uses the lower reading to set the tank level.
	//Checks to see if tank level is correct for operating conditions.
	//If correct returns true, otherwise returns false.
	bool CheckTankLevelSensors(bool pump_on);
};

#endif