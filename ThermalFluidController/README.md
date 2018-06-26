## Solar Thermal Fluid Controller and Performance Analyzer

Goal: Achieve desired temperature while minimizing pump power usage.
A thermal fluid system uses a fluid to collect and store thermal energy.
The components consist of a collector to absorb the thermal energy, a storage tank to store the thermal energy and a pump to circulate the fluid from the collector and storage tank
Collector efficiency is maximized by maintaining the highest temperature differential between the collector and the fluid stream. 
To maintain this temperature differential the pump speed must be precisely regulated. 
Precise regulation is achieved by pulsed width modulation or PWM of the power for the pump.

For the system to work many inputs are required.

#### The controller must monitor sensors to generate the following variables
    
    tanklevelpumpoff  // the amount of fluid below full in the storage tank with the pump off in millimeters
    tanklevelpumpon  //  the amount of fluid below full in the storage tank with the pump on in millimeters
		// with a drain back system these would be set different, non drain back they would be set the same
    hottertemp  // the temperature of the hotter tank in degrees C in a two tank system or the top of the tank in a stratified system
    coldertemp  //  the temperature of the colder tank in degrees C in a two tank system or the bottom of the tank in a stratified system
    collectortemp //  the temperature in degrees C of the collector heat exchanger
    outputtemp // the temperature in degrees C of the fluid exiting the collector
    pumpflow // the amount of fluid the pump is pumping in liters per minute

#### The system must be set up initially and the following variables must be input:

	maxtemp // the desired maximum temperature in degrees C of the fluid in the storage tank
	onbuffertemp  // the temperature of the collectortemp above the hottertemp temperature to turn the pumpon
	offbuffertemp // the temperature of the collectortemp above the hottertemp temperature to turn the pumpoff
	fulllevelpumpoff  //  the calibration of the storage tank full level with the pump off, sets parameter to zero millimeters
	fulllevelpumpon  //  the calibration of the storage tank full level with the pump on, will be negative value relative to fulllevelpumpon in a drain back system
		//  with a drain back system these would be set different, non drain back they would be set the same
	maxpumpflow  //  the calibration of the pump flow in liters per minute at maximum power
    minpumpPWM  //  the calibration of the minimum PWM that the pump can reliably run at
    minpumpflow // the calibration of the pump flow in liters per minute at minimum power
	proportionalgain // the gain for the proportional part of the PID 
    integralgain  //  the gain for the integral part of the PID
    derivativegain  //  the gain for the derivative part of the PID 
	overtempwarning  //  the temperature in degrees C of the storage tank over the maxtemp to activate warning 
	belowfullwarning  // the level of the storage tank in millimeters below full to activate warning
	pumpflowwarning  //  the measured flow in liters per minute below PumpFlowCheck() to activate warning  
    fill time  //  when the pump is turned on the time in milliseconds it takes for fluid level in tank  to change from fulllevelpumpoff to fulllevelpumpon
    drain time  //  when the pump is turned off the time in milliseconds it takes for fluid level in tank  to change from fulllevelpumpon to fulllevelpumpoff
        //  for a non-drain back system these can be set at the minimum value to allow for PumpFlowCheck() to be performed
The basic on/off control of the pump is based upon the following:

    if collectortemp >= (onbuffertemp + hottertemp) turn pumpon
    if collectortemp <= (offbuffertemp + hottertemp) turn pumpoff

    when pumpon set pumpPWM to 100
    when pumpoff set pumpPWM to 0

The control of the pump is done with a PID controller or Proportional, Integral, Derivative controller

From the input variables the following variables will be calculated:
    
    desiredoutputtemp  // this is calculated by (collectortemp + hottertemp) / 2 = desiredoutputtemp thus its an average of collectortemp and hottertemp
    // This establishes the set point of the PID
    outputtemperror  //  This is calculated by desiredoutputtemp - outputtemp = outputtemperror
    // This calculates the amount of error or difference between what the desiredoutputtemp is and what the outputtemp is
    outputtemperrorprevious  //  this is the error from the previous PID loop

The PID also must keep track of time and used the following variables to do so:
        
    timecurrent // this is the current time in milliseconds 
    timeprevious // this is the time from previous update of PID loop

For the Proportional part:

    proportional = outputtemperror * proportionalgain

For the Integral part:
        
    integral = integralgain * outputtemperror * (timecurrent-timeprevious) + integral

For the Derivative part:
        
    derivative = (outputtemperror-outputtemperrorprevious) / (timecurrent-timeprevious) * derivativegain

The output is the amount to adjust the  PWM of the power to the pump and is found by:

    pumpPWMadjust = proportional + integral + derivative 

The pumpPWM is then adjusted by:

    pumpPWM + pumpPWMadjust = pumpPWM

The pumpPWM is limited by:

    if pumpPWM <= minpumpPWM set pumpPWM = minpumpPWM


    
        
        
    
        
	    
