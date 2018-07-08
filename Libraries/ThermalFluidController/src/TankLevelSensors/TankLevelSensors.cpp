#include "TankLevelSensors.h"

TankLevelSensors::TankLevelSensors() :
	sensor_1(kTankLevelSensor1TriggerPin, kTankLevelSensor1EchoPin), sensor_2(kTankLevelSensor2TriggerPin, kTankLevelSensor2EchoPin)
{

}
