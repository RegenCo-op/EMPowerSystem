#include "TankLevelSensors.h"

TankLevelSensors::TankLevelSensors(int plausible_tank_level, int level_diff_spec_range, int full_level_pump_off, int tank_level_max_error) :
	sensor_1_(kTankLevelSensor1TriggerPin, kTankLevelSensor1EchoPin), sensor_2_(kTankLevelSensor2TriggerPin, kTankLevelSensor2EchoPin)
{
	plausible_level_ = plausible_tank_level;
	level_diff_spec_range_ = level_diff_spec_range;
	full_level_pump_off_ = full_level_pump_off;
	tank_level_max_error_ = tank_level_max_error;
}
