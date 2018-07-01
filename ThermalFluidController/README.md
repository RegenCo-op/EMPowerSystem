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

**Storage Tank Fluid Level:**  
The Storage Tank Fluid Level is monitored by ultrasonic distance sensors measuring the distance from the sensor to the fluid.  
Storage Tank Fluid Level Sensors 1 and 2 are both located at the same hight in the storage tank.   
Two sensors are used because this condition is critical to safe and reliable operation.

**Storage Tank Temperature:**   
The Storage Tank Temperature is monitored by three temperature sensors.  
Storage Tank Temperature Sensor 1 and 2 monitor the Storage Tank Temperature at the top of the tank where if the tank is stratified it would be hottest.  
If using a multi-tank system they would be located in the tank directly receiving flow from the collector.   
Two sensors are used because this condition is critical to safe and reliable operation.
The third sensor is located in the bottom of the tank where if the tank is stratified it would be coldest.
If using a multi-tank system it would be located in the tank directly feeding flow to the collector.
This sensor isn't used in the control of the system but is necessary for analyzing the performance of the system.

**Collector Temperature:**  
The Collector Temperature is monitored by two temperature sensors embedded in the collector midway between fluid passages.  
Collector Temperature Sensor 1 is located in the middle of one halve of the collector.  
Collector Temperature sensor 2 is located in the middle of the other half of the collector.  
This is to get the best average temperature of the collector.  
Two sensors are used  because this condition is critical to safe and reliable operation. 

**Collector Output Temperature:**   
The Collector Output Temperature is monitored by two temperature sensors embedded in the fluid flowing from the Collector.  
Collector Output Temperature Sensor 1 is located as close to the Collector outlet as possible but in the shade and not influenced by heat radiating from the outside.  
Collector Output Temperature Sensor 2 is located as close to the Storage Tank inlet as possible but in the shade and not influenced by heat radiating from the outside.  
Two sensors are used because this condition is critical to safe and reliable operation.  

**Pump Flow:**
The Pump Flow is monitored by two fluid flow sensors in line with the fluid flow.  
Pump Flow Sensor 1 is located at the outlet of the Storage Tank.  
Pump Flow Sensor 2 is located at the inlet of the Storage Tank.
This arrangement can check for multiple system faults.  
Two sensors are used because this condition is critical to safe and reliable operation.

### Operation of System:

Step 1. Check the Storage Tank Fluid Level.  
   i. Check to make sure Storage Tank Fluid Level Sensors 1 and 2 are in agreement.  
      * If not set alarm and fault code and continue to ii.
      * If in agreement continue to iii. 
        
   ii. Check to see if at least one of them is in normal range,  
       * If both out of normal range set alarm and fault code and DO NOT continue, conditions do not support safe and reliable operation.  
       * If at least one is in normal range continue to iv.  

   iii. Average Storage Tank Fluid Level Sensors 1 and 2 readings to define the Storage Tank Fluid Level and continue to Step 2.  
   iv. Use the reading of the of the sensor within normal range to define the Storage Tank Fluid Level and continue to Step 2.              
  




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