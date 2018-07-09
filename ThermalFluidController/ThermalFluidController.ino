#include "Arduino.h"
#include "ThermalFluidController.h"


TankLevelSensorsConfig tank_level_sensors_config = { 0,0,0,0,0,0 };

void setup()
{
	ThermalFluidController test(tank_level_sensors_config);

}


void loop()
{


}
