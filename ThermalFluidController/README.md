## Solar Thermal Fluid Controller and Performance Analyzer

Goal: Achieve desired temperature while minimizing pump power usage.
A thermal fluid system uses a fluid to collect and store thermal energy.
The components consist of a collector to absorb the thermal energy, a storage tank to store the thermal energy and a pump to circulate the fluid from the collector and storage tank
Collector efficiency is maximized by maintaining the highest temperature differential between the collector and the fluid stream. 
To maintain this temperature differential the pump speed must be precisely regulated. 
Precise regulation is achieved by pulsed width modulation or PWM of the power for the pump.

For the system to work many inputs are required.

#### The controller must monitor sensors to generate the following variables
    
    tank_level_pump_off  // the amount of fluid below full in the storage tank with the pump off in millimeters
    tank_level_pump_on  //  the amount of fluid below full in the storage tank with the pump on in millimeters
		// with a drain back system these would be set different, non drain back they would be set the same
    hotter_temp  // the temperature of the hotter tank in degrees C in a two tank system or the top of the tank in a stratified system
    colder_temp  //  the temperature of the colder tank in degrees C in a two tank system or the bottom of the tank in a stratified system
    collector_temp //  the temperature in degrees C of the collector heat exchanger
    output_temp // the temperature in degrees C of the fluid exiting the collector
    pump_flow // the amount of fluid the pump is pumping in liters per minute

#### The system must be set up initially and the following variables must be input:

	max_temp // the desired maximum temperature in degrees C of the fluid in the storage tank
	on_buffer_temp  // the temperature of the collector_temp above the hotter_temp temperature to turn the pumpon
	off_buffer_temp // the temperature of the collector_temp above the hotter_temp temperature to turn the pumpoff
	full_level_pump_off  //  the calibration of the storage tank full level with the pump off, sets parameter to zero millimeters
	full_level_pump_on  //  the calibration of the storage tank full level with the pump on, will be negative value relative to full_level_pump_on in a drain back system
		//  with a drain back system these would be set different, non drain back they would be set the same
	max_pump_flow  //  the calibration of the pump flow in liters per minute at maximum power
    min_pump_PWM  //  the calibration of the minimum PWM that the pump can reliably run at
    min_pump_flow // the calibration of the pump flow in liters per minute at minimum power
	proportional_gain // the gain for the proportional part of the PID 
    integral_gain  //  the gain for the integral part of the PID
    derivative_gain  //  the gain for the derivative part of the PID 
	over_temp_warning  //  the temperature in degrees C of the storage tank over the max_temp to activate warning 
	below_full_warning  // the level of the storage tank in millimeters below full to activate warning
	pump_flow_warning  //  the measured flow in liters per minute below pump_flowcheck to activate warning  
    fill_time  //  when the pump is turned on the time in milliseconds it takes for fluid level in tank  to change from full_level_pump_off to full_level_pump_on
    drain_time  //  when the pump is turned off the time in milliseconds it takes for fluid level in tank  to change from full_level_pump_on to full_level_pump_off
        //  for a non-drain back system these can be set at the minimum value to allow for pump_flowcheck to be performed
The basic on/off control of the pump is based upon the following:

    if (collector_temp >= (on_buffer_temp + hotter_temp)): 
		turn pump on
		set pump_PWM to 100%
    if (collector_temp <= (off_buffer_temp + hotter_temp)): 
		turn pump off
		set pump_PWM to 0%


The control of the pump is done with a PID controller or Proportional, Integral, Derivative controller

From the input variables the following variables will be calculated:
    
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


    
        
        
    
        
	    
