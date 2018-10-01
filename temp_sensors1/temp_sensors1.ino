//Measure NTC value
byte tank_temp_pin = A1; //signal from temp sensor in bucket
byte collector_temp_pin = A2; //signal from temp sensor iin heated pot
byte output_temp_pin = A3; //signal from temp sensor in outlet pipe from heated pot
long tank_temp_resistor_1 = 9640;  // resistance value of resistor before thermister for tank temp
long tank_temp_resistor_2 = 98800;  // resistance value of resistor after thermister for tank temp
long collector_temp_resistor_1 = 98200;  // resistance value of resistor before thermister for collector temp
long collector_temp_resistor_2 = 199000;  // resistance value of resistor after thermister for collector temp
long output_temp_resistor_1 = 98700;  // resistance value of resistor before thermister for output temp
long output_temp_resistor_2 = 200000;  // resistance value of resistor after thermister for output temp
float tank_temp_ADC_value = 0; // tank temp sensor analog to digital converter value 0-1023
float tank_temp_resistance; // calculated resistance of tank temp sensor
float collector_temp_ADC_value = 0; // collector temp sensor analog to digital converter value 0-1023
float collector_temp_resistance; // calculated resistance of collector temp sensor
float output_temp_ADC_value = 0; // output temp sensor analog to digital converter value 0-1023
float output_temp_resistance; // calculated resistance of output temp sensor
float tank_temp_voltage; // converted ADC_value to voltage
float collector_temp_voltage; // converted ADC_value to voltage
float output_temp_voltage; // converted ADC_value to voltage
float VCC = 3.375; //measured 3.3 volt reference
float tank_temperature; //calculated tank temperature 
float collector_temperature; //calculated collector temperature
float output_temperature; //calculated output temperature

float smoothing_value = 1;


const byte PWM_pin = 4;
const byte POT_pin = 0;
float on_time;
int POT_value;

//Variables for sampling
float tmp_avg; //temp variable for averages

unsigned long	past_millis_tank_temp = 0;
int			curr_sample_num_tank_temp = 0;
double			running_avg_tank_temp = 0;

unsigned long	past_millis_collector_temp = 0;
int			curr_sample_num_collector_temp = 0;
double			running_avg_collector_temp = 0;

unsigned long	past_millis_output_temp = 0;
int			curr_sample_num_output_temp = 0;
double			running_avg_output_temp = 0;


void setup()
{
	Serial.begin(115200);
	analogReference(EXTERNAL);
}
void loop()
{
	/* VCC = analogRead(EXTERNAL);
	VCC = map(VCC,0,1023,1023,0);
	Serial.print("VCC = ");
	Serial.print(VCC);
	VCC = map(VCC,0.0,1023.0,0.0,5.0);

	Serial.print("VCC = ");
	Serial.print(VCC);*/
	POT_value = analogRead(POT_pin);
	on_time = map(POT_value, 0, 1023, 0, 255);
	analogWrite(PWM_pin, on_time);

	// calculate tank temp:
	//Sample returns -1 if not ready, otherwise it returns >= 0 if it is ready
	tmp_avg = sample(tank_temp_pin, 50, 10, past_millis_tank_temp, curr_sample_num_tank_temp, running_avg_tank_temp);
	if (tmp_avg >= 0)
	{
		tank_temp_ADC_value = tmp_avg; //Update value if sample ready, otherwise it remains what it was before
	}

	tank_temp_voltage = tank_temp_ADC_value / 1023 * VCC;

	tank_temp_resistance = tank_temp_resistor_2 / tank_temp_ADC_value * 1023 - tank_temp_resistor_2 - tank_temp_resistor_1;

	if (tank_temp_resistance > 37000)
	{
		tank_temperature = 1.0 / (0.00024807263798212265 + 0.00027560090866740535 * log(tank_temp_resistance) + -4.5102113312005025e-8   * log(tank_temp_resistance) * log(tank_temp_resistance) * log(tank_temp_resistance));
	}
	else if (tank_temp_resistance < 37000)
	{
		tank_temperature = 1.0 / (-0.0006453822260400147 + 0.00040907100900559705 * log(tank_temp_resistance) + -4.837240189412059e-7    * log(tank_temp_resistance) * log(tank_temp_resistance) * log(tank_temp_resistance));
	}
	else
	{
		tank_temperature = 50.0;
	}
	tank_temperature = tank_temperature - 270.75;

	float smoothed_value = 0.0;
	float new_reading = tank_temperature;
	smoothed_value = (smoothing_value * smoothed_value) + ((1 - smoothed_value) * new_reading);



	// calculate collector temp: 
	//Sample returns -1 if not ready, otherwise it returns >= 0 if it is ready
	tmp_avg = sample(collector_temp_pin, 50, 10, past_millis_collector_temp, curr_sample_num_collector_temp, running_avg_collector_temp);
	if (tmp_avg >= 0)
	{
		collector_temp_ADC_value = tmp_avg; //Update value if sample ready, otherwise it remains what it was before
	}

	collector_temp_voltage = collector_temp_ADC_value / 1023 * VCC;

	collector_temp_resistance = collector_temp_resistor_2 / collector_temp_ADC_value * 1023 - collector_temp_resistor_2 - collector_temp_resistor_1;

	if (collector_temp_resistance > 37000)
	{
		collector_temperature = 1.0 / (0.00024807263798212265 + 0.00027560090866740535 * log(collector_temp_resistance) + -4.5102113312005025e-8   * log(collector_temp_resistance) * log(collector_temp_resistance) * log(collector_temp_resistance));
	}
	else if (collector_temp_resistance < 37000)
	{
		collector_temperature = 1.0 / (-0.0006453822260400147 + 0.00040907100900559705 * log(collector_temp_resistance) + -4.837240189412059e-7    * log(collector_temp_resistance) * log(collector_temp_resistance) * log(collector_temp_resistance));
	}
	else
	{
		collector_temperature = 50.0;
	}
	collector_temperature = collector_temperature - 273.15;

	// calculate output temp:
	//Sample returns -1 if not ready, otherwise it returns >= 0 if it is ready
	tmp_avg = sample(output_temp_pin, 50, 10, past_millis_output_temp, curr_sample_num_output_temp, running_avg_output_temp);
	if (tmp_avg >= 0)
	{
		output_temp_ADC_value = tmp_avg; //Update value if sample ready, otherwise it remains what it was before
	}

	output_temp_voltage = output_temp_ADC_value / 1023 * VCC;

	output_temp_resistance = output_temp_resistor_2 / output_temp_ADC_value * 1023 - output_temp_resistor_2 - output_temp_resistor_1;

	if (output_temp_resistance > 37000)
	{
		output_temperature = 1.0 / (0.00024807263798212265 + 0.00027560090866740535 * log(output_temp_resistance) + -4.5102113312005025e-8   * log(output_temp_resistance) * log(output_temp_resistance) * log(output_temp_resistance));
	}
	else if (output_temp_resistance < 37000)
	{
		output_temperature = 1.0 / (-0.0006453822260400147 + 0.00040907100900559705 * log(output_temp_resistance) + -4.837240189412059e-7    * log(output_temp_resistance) * log(output_temp_resistance) * log(output_temp_resistance));
	}
	else
	{
		output_temperature = 50.0;
	}
	output_temperature = output_temperature - 273.15;

	//Serial.print ("POT:  ");
	//Serial.print (POT_value);
	//Serial.print ("  Pump:  ");
	//Serial.print (on_time);
	// Serial.print (" Tank Temp Analog Value: ");
	// Serial.print (tank_temp_ADC_value);
	// Serial.print (" Tank Temp Voltage: ");
	// Serial.print (tank_temp_voltage);
	// Serial.print (" Tank Temp Resistance: ");
	// Serial.print (tank_temp_resistance);
	// Serial.print (" Ohm ");
	Serial.print(" Tank Temp: ");
	Serial.print(tank_temperature, 3);
	Serial.print(" c ");
	Serial.println(smoothed_value, 3);
	//Serial.print (" Collector Temp: "); 
	//Serial.print (collector_temperature);
	//Serial.print (" c ");
	//Serial.print (" Output Temp: "); 
	//Serial.print (output_temperature);
	//Serial.println(" c ");
}
// This function will read the provided sensor pin num_samples of times and take an average.
// Each sample will have an interval of sample_interval milliseconds between samples
// Doesn't block execution of rest of program. Must be called in loop to ensure all samples taken
// Sample returns -1 if not ready, otherwise it returns >= 0 if it is ready, and then resets for the use
// of more samples.
float sample(byte pin, unsigned int num_samples, unsigned int sample_interval, unsigned long& past_millis, int& curr_sample_num, float& running_avg)
{	
	unsigned long present_millis = millis();

	//Check that enough time has passed. If elapsed time is less than sample interval, return <0
	//to let caller know average not ready yet
	if(present_millis - past_millis < sample_interval) //Present - past handles overflow nicely
	{
		return -1; 
	}

	//enough time has passed, take the sample and add it to our running avg. Also update past millis for next time
	curr_sample_num++;
	past_millis = present_millis;
	float val = analogRead(pin); //Take reading and make it a double so we perform floating point division
	running_avg = val / num_samples + running_avg; //Update running average

	//check if we have the desired number of samples
	if(curr_sample_num < num_samples)
	{
		return -1; //Not enough samples
	}
	else
	{
		//Enough samples taken. Return average. 
		float average = running_avg;
		running_avg = 0; //Reset running avg to 0 for next time
		curr_sample_num = 0; //Reset curr sample num for next time
		return average;
	}
}
//end program