#include "TankLevelSensors.h"

TankLevelSensors::TankLevelSensors(TankLevelSensorsConfig tank_level_sensors_config) :
	sensor_1_(kTankLevelSensor1TriggerPin, kTankLevelSensor1EchoPin, tank_level_sensors_config.plausible_tank_level_max), 
	sensor_2_(kTankLevelSensor2TriggerPin, kTankLevelSensor2EchoPin, tank_level_sensors_config.plausible_tank_level_max)
{
	plausible_level_ = tank_level_sensors_config.plausible_tank_level_min;
	level_diff_spec_range_ = tank_level_sensors_config.level_diff_spec_range;
	full_level_pump_off_ = tank_level_sensors_config.full_level_pump_off;
	tank_level_max_error_ = tank_level_sensors_config.tank_level_max_error;
}

int TankLevelSensors::ReadSensor1Level_()
{
	//TODO: adjust value 
	sensor_1_level_ = sensor_1_.ping_cm();
	return sensor_1_level_;
}

int TankLevelSensors::ReadSensor2Level_()
{
	//TODO: adjust value 
	sensor_2_level_ = sensor_2_.ping_cm();
	return sensor_2_level_;
}


