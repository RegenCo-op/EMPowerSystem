## Thermal Collector and  Storage Controller, Solar, Drainback

### System Discription:
#### **Goal**: Safely and reliably achieve desired storage temperature while minimizing pump power usage.  
A solar thermal fluid system uses a fluid to collect and store thermal energy from sunlight.  

**The main components consist of:**  
* a fluid for absorbing, transporting and storing thermal energy. 
* a collector to absorb the thermal energy and transfer it to the fluid. 
*  a storage tank to store the fluid and thus the thermal energy.  
*  a pump to circulate the fluid through the collector and storage tank.
  
#### **Method:** Maximize the highest temperature differential between the collector and the fluid stream. 
To maintain this temperature differential the pump speed must be precisely regulated. 
Precise regulation is achieved by pulsed width modulation or PWM of the power for the pump.
To achieve this precise regulation and provide operational safety of the system several conditions must be reliably monitored.

**Conditions that need to be monitored:**  
* Storage Tank Fluid Level
* Storage Tank Temperature
* Collector Temperature
* Collector Output Temperature
* Pump Flow  

#### Components that Monitor the Conditions:

**Storage Tank Fluid Level (STFL):**  
The Storage Tank Fluid Level is monitored by ultrasonic distance sensors measuring the distance from the sensor to the fluid.  
STFL Sensors 1 and 2 are both located at the same hight in the storage tank.   
Two sensors are used because this condition is critical to safe and reliable operation.

**Storage Tank Temperature (STT):**   
The Storage Tank Temperature is monitored by three temperature sensors.  
SST Sensor 1 and SST Sensor 2 monitor the Storage Tank Temperature at the top of the tank where if the tank is stratified it would be hottest.  
If using a multi-tank system they would be located in the tank directly receiving flow from the collector.   
Two sensors are used because this condition is critical to safe and reliable operation.
The third sensor is located in the bottom of the tank where if the tank is stratified it would be coldest.
If using a multi-tank system it would be located in the tank directly feeding flow to the collector.
This sensor isn't used in the control of the system but is necessary for analyzing the performance of the system.

**Collector Temperature (CT):**  
The Collector Temperature is monitored by two temperature sensors embedded in the collector midway between fluid passages.  
CT Sensor 1 is located in the middle of one halve of the collector.  
CT sensor 2 is located in the middle of the other half of the collector.  
This is to get the best average temperature of the collector.  
Two sensors are used  because this condition is critical to safe and reliable operation. 

**Collector Output Temperature (COT):**   
The Collector Output Temperature is monitored by two temperature sensors embedded in the fluid flowing from the Collector.  
Sensor One is located as close to the Collector outlet as possible but in the shade and not influenced by heat radiating from the outside.  
The other is located as close to the Storage Tank inlet as possible but in the shade and not influenced by heat radiating from the outside.  
Two sensors are used because this condition is critical to safe and reliable operation.  

**Pump Flow (PF)**
The Pump Flow is monitored by two fluid flow sensors in line with the fluid flow.  
PF Sensor 1 is located at the outlet of the Storage Tank.  
PF Sensor 2 is located at the inlet of the Storage Tank.
This arrangement can check for multiple system faults.  
Two sensors are used because this condition is critical to safe and reliable operation.

#### The controller must monitor sensors to generate the following variables  
* tank_level_pump_off  // the amount of fluid below full in the storage tank with the pump off in millimeters
* tank_level_pump_on  //  the amount of fluid below full in the storage tank with the pump on in millimeters  
  // with a drain back system these would be set different, non drain back they would be set the same
* tank_level // this is the current level of the fluid in the tank relative negative to the calibration variable `full_level_pump_off`_
* hotter_temp  // the temperature of the hotter tank in degrees C in a two tank system or the top of the tank in a stratified system
* colder_temp  //  the temperature of the colder tank in degrees C in a two tank system or the bottom of the tank in a stratified system
* collector_temp //  the temperature in degrees C of the collector heat exchanger
* output_temp // the temperature in degrees C of the fluid exiting the collector
* pump_flow // the amount of fluid the pump is pumping in liters per minute

#### The system must be set up initially and the following variables must be input:


* `max_temp` // the desired maximum temperature in degrees C of the fluid in the storage tank
* `on_buffer_temp`  // the temperature of the collector_temp above the hotter_temp temperature to turn the pump_on
* `off_buffer_temp` // the temperature of the collector_temp above the hotter_temp temperature to turn the pump_off
* `full_level_pump_off`  //  the calibration of the storage tank full level with the pump off, sets parameter to zero millimeters
* `full_level_pump_on`  //  the calibration of the storage tank full level with the pump on, will be negative value relative to full_level_pump_on in a drain back system  
 	**NOTE:**  with a drain back system these would be set different, non drain back they would be set the same
* `max_pump_flow`  //  the calibration of the pump flow in liters per minute at maximum power
*  `min_pump_PWM`  //  the calibration of the minimum PWM that the pump can reliably run at
*  `min_pump_flow` // the calibration of the pump flow in liters per minute at minimum power
* `proportional_gain` // the gain for the proportional part of the PID 
*  `integral_gain`  //  the gain for the integral part of the PID
*  `derivative_gain`  //  the gain for the derivative part of the PID 
* `over_temp_warning`  //  the temperature in degrees C of the storage tank over the max_temp to activate warning 
* `below_full_warning`  // the level of the storage tank in millimeters below full to activate warning
* `above_full_warning`  // the level of the storage tank in millimeters above full to activate warning
* `pump_flow_warning`  //  the measured flow in liters per minute below pump_flowcheck to activate warning  
*  `fill_time`  //  when the pump is turned on the time in milliseconds it takes for fluid level in tank  to change from full_level_pump_off to full_level_pump_on
*  `drain_time`  //  when the pump is turned off the time in milliseconds it takes for fluid level in tank  to change from full_level_pump_on to full_level_pump_off  
   **NOTE:**  for a non-drain back system these can be set at the minimum value to allow for pump_flowcheck to be performed
#### The basic on/off control of the pump and initial diagnostic checks of the tank level and pump is based upon the following:
```
TankLevelCheck()
    start monitoring tank_level
    if (tank_level <= full_level_pump_off - below_full_warning):  
        set Alarm, set DTC and do nothing else
    if (tank_level >= full_level_pump_off + above_full_warning):  
        set Alarm, set DTC and do nothing else
    if (tank_level >= full_level_pump_off - below_full_warning):  
        continue

start monitoring collector_temp
start monitoring hotter_temp_

if (collector_temp >= (on_buffer_temp + hotter_temp)):  
    turn pump_on
    set pump_PWM to 100%
    start counter for fill_time_check  
    start monitoring current_pump_flow  
    wait a short bit for pump flow to stabilize
    is current_pump_flow <= max_pump_flow - pump_flow_warning

    when fill time reached is current_tank_level <= full_level_pump_on + below


if (collector_temp <= (off_buffer_temp + hotter_temp)):
    turn pump_off;  
    set pump_PWM to 0%;
```


### The control of the pump is done with a PID controller or Proportional, Integral, Derivative controller

#### From the input variables the following variables will be calculated:
    
    desired_output_temp  // this is calculated by (collector_temp + hotter_temp) / 2 = desired_output_temp thus its an average of collector_temp and hotter_temp
    // This establishes the set point of the PID
    output_temp_error  //  This is calculated by desired_output_temp - output_temp = output_temp_error
    // This calculates the amount of error or difference between what the desired_output_temp is and what the output_temp is
    previous_output_temp_error  //  this is the error from the previous PID loop

The PID also must keep track of time and used the following variables to do so:
        
    current_time // this is the current time in milliseconds 
    previous_time // this is the time from previous update of PID loop

For the Proportional part:

    proportional = output_temp_error * proportional_gain

For the Integral part:
        
    integral = integral_gain * output_temp_error * (current_time - previous_time) + integral

For the Derivative part:
        
    derivative = (output_temp_error - previous_output_temp_error) / (current_time - previous_time) * derivative_gain

The output is the amount to adjust the PWM of the power to the pump and is found by:

    pump_PWM_adjust = proportional + integral + derivative 

The pump_PWM is then adjusted by:

    pump_PWM = pump_PWM + pump_PWM_adjust

The pump_PWM is limited by:

    if (pump_PWM <= min_pump_PWM):
		pump_PWM = min_pump_PWM
	else if (pump_PWM > max_pump_PWM):
		pump_PWM = max_pump_PWM