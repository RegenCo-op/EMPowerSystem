// ThermalFluidController.h

#ifndef _THERMALFLUIDCONTROLLER_h
#define _THERMALFLUIDCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// The controller must monitor sensors to generate the following variables  
* tank_level_pump_off  // the amount of fluid below full in the storage tank with the pump off in millimeters
* tank_level_pump_on  //  the amount of fluid below full in the storage tank with the pump on in millimeters  
					  **Note** with a drain back system these would be set different, non drain back they would be set the same
	* tank_level // this is the current level of the fluid in the tank relative negative to the calibration variable `full_level_pump_off`_
	* hotter_temp  // the temperature of the hotter tank in degrees C in a two tank system or the top of the tank in a stratified system
	* colder_temp  //  the temperature of the colder tank in degrees C in a two tank system or the bottom of the tank in a stratified system
	* collector_temp //  the temperature in degrees C of the collector heat exchanger
	* output_temp // the temperature in degrees C of the fluid exiting the collector
	* pump_flow // the amount of fluid the pump is pumping in liters per minute //

				// The system must be set up initially and the following variables must be input:
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
	**NOTE:**  for a non - drain back system these can be set at the minimum value to allow for pump_flowcheck to be performed //

#endif

