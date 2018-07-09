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

bool TankLevelSensors::CheckTankLevelPlausibility()
{
	sensor_1_is_plausible_ = false;
	sensor_2_is_plausible_ = false;

	ReadSensor1Level_();
	ReadSensor2Level_();

	if (sensor_1_level_ > plausible_level_) //plausible level is only the min value, since ping_cm returns 0 if reading > max distance
	{
		sensor_1_is_plausible_ = true;
		//TODO: set dtc
	}

	if (sensor_2_level_ > plausible_level_)
	{
		sensor_2_is_plausible_ = true;
		//TODO: set dtc
	}

	if(!sensor_1_is_plausible_ && !sensor_2_is_plausible_)
	{
		//TODO: set dtc for both failing and exit check
		return false;
	}

	//TODO: maybe increment failure counter
	return true;
}

bool TankLevelSensors::CheckTankLevelSensorDifferential()
{
	int diff = sensor_1_level_ - sensor_2_level_;
	if (abs(diff) > level_diff_spec_range_)
	{
		//differential is too large
		//TODO: set dtc
		//TODO: maybe increment failure counter
		return false;
	}
	else
	{
		return true;
	}
}

bool TankLevelSensors::CheckTankLevel(bool pump_on)
{
	//set calibration level depending on pump state
	int calibration_level;
	if (pump_on)
	{
		//compare tank level with the calibrated level with the pump on
		calibration_level = full_level_pump_on_;
	}
	else
	{
		//compare tank level with the calibrated level with the pump off
		calibration_level = full_level_pump_off_;
	}

	//compare tank level to calibrated level
	int diff = tank_level_ - calibration_level;
	if (abs(diff) > tank_level_max_error_)
	{
		//differential is too large
		//TODO: set dtc
		//TODO: maybe increment failure counter
		return false;
	}
	else
	{
		return true;
	}
}

bool TankLevelSensors::CheckTankLevelSensors(bool pump_on)
{
	if (!CheckTankLevelPlausibility())
	{
		//Both sensors were implausible, don't continue checking
		return false;
	}

	//Get tank level
	if (sensor_1_is_plausible_ && sensor_2_is_plausible_)
	{
		//both sensors plausible
		if (CheckTankLevelSensorDifferential())
		{
			//differential is within limits
			tank_level_ = (sensor_1_level_ + sensor_2_level_) / 2;
		}
		else
		{
			//differential is out of limits, use lower level sensor
			if (sensor_1_level_ < sensor_2_level_)
			{
				tank_level_ = sensor_1_level_;
			}
			else
			{
				tank_level_ = sensor_2_level_;
			}
		}
	}
	else //One of the sensor readings are not plausible
	{
		//TODO: maybe increment failure counter
		//Set tank level to be the one plausible sensor level
		if (sensor_1_is_plausible_)
		{
			tank_level_ = sensor_1_level_;
		}
		else
		{
			tank_level_ = sensor_2_level_;
		}
	}

	//compare tank level to calibrated level
	return CheckTankLevel(pump_on);
}