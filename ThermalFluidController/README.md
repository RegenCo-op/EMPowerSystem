# Solar Thermal Fluid Controller and Performance Analyzer

Goal: Achieve desired temperature while minimizing pump power usage.
A thermal fluid system uses a fluid to collect and store thermal energy.
The components consist of a collector to absorb the thermal energy, a storage tank to store the thermal energy and a pump to circulate the fluid from the collector and storage tank
Collector efficiency is maximized by maintaining the highest temperature differential between the collector and the fluid stream. 
To maintain this temperature differential the pump speed must be precisely regulated. 
Precise regulation is achieved by pulsed width modulation or PWM of the power for the pump.

For the system to work many inputs are required.

The controller must monitor the following variables:
	tanklevelpumpoff  // the amount of fluid below full in the storage tank with the pump off in millimeters
	tanklevelpumpon  //  the amount of fluid below full in the storage tank with the pump on in millimeters
		// with a drain back system these would be set different, non drain back they would be set the same
	hottertemp  // the temperature of the hotter tank in degrees C in a two tank system or the top of the tank in a stratified system
	coldertemp  //  the temperature of the colder tank in degrees C in a two tank system or the bottom of the tank in a stratified system
	collectortemp //  the temperature in degrees C of the collector heat exchanger
	outputtemp // the temperature in degrees C of the fluid exiting the collector
	pumpflow // the amount of fluid the pump is pumping in liters per minute

The system must be set up initially and the following variables must be input:
	maxtemp // the desired maximum temperature in degrees C of the fluid in the storage tank
	onbuffertemp  // the temperature in degrees C above the hottertemp temperature to turn the pump on
	offbuffertemp // the temperature in degrees C above the hottertemp temperature to turn the pump off
	fulllevelpumpoff  //  the calibration of the storage tank full level with the pump off, sets parameter to zero millimeters
	fulllevelpumpon  //  the calibration of the storage tank full level with the pump on, will be negative value relative to fulllevelpumpon in a drain back system
		//  with a drain back system these would be set different, non drain back they would be set the same
	maxpumpflow  //  the calibration of the pump flow in liters per minute at maximum power
	
	overtempwarning  //  the temperture in degrees C of the storage tank over the maxtemp to activate warning 
	belowfullwarning  // the level of the storage tank in millimeters below full to activate warning
	pumpflowwarning  //  the measured flow in liters per minute below maxpumpflow to activate warning  

From the input variables the following variables will be calculated:
	desiredoutputtemp  // this is calculated by averaging the collectortemp and hottertemp variables
	pumpstatedelay  // the time it takes for the system to respond to changes in the pump speed
