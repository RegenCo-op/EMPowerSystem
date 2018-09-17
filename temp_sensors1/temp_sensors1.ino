//Measure NTC value
byte tank_temp = A1; //signal from temp sensor in bucket
byte collector_temp = A2; //signal from temp sensor iin heated pot
byte output_temp = A3; //signal from temp sensor in outlet pipe from heated pot
long tank_temp_resistor_1 = 9640;  // resistance value of resistor before thermister for tank temp
long tank_temp_resistor_2 = 98800;  // resistance value of resistor after thermister for tank temp
long collector_temp_resistor_1 = 98200;  // resistance value of resistor before thermister for collector temp
long collector_temp_resistor_2 = 199000;  // resistance value of resistor after thermister for collector temp
long output_temp_resistor_1 = 98700;  // resistance value of resistor before thermister for output temp
long output_temp_resistor_2 = 200000;  // resistance value of resistor after thermister for output temp
float tank_temp_ADC_value; // tank temp sensor analog to digital converter value 0-1023
float tank_temp_resistance; // calculated resistance of tank temp sensor
float collector_temp_ADC_value; // collector temp sensor analog to digital converter value 0-1023
float collector_temp_resistance; // calculated resistance of collector temp sensor
float output_temp_ADC_value; // output temp sensor analog to digital converter value 0-1023
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

	tank_temp_ADC_value = sample(tank_temp);

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

	collector_temp_ADC_value = sample(collector_temp);

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

	output_temp_ADC_value = sample(output_temp);

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
// This function will read the tank temp sensor pin x# of times and take an average.

float sample(byte pin)
{
	float sample_value;
	const long num_samples = 8000;
	long buffer[num_samples];
	long index;
	unsigned long present_millis;
	unsigned long past_millis;
	unsigned long sample_interval = 10;
	float readsample(sample_value);
	{
		present_millis = millis();
		if (present_millis >= sample_interval + past_millis)
		{
			sample_value = analogRead(pin);
			past_millis = millis();
		}
		return sample_value;
	}

	float addsamples(sample_value);
	{
		buffer[index] = sample_value;
		index++;
		if (index >= num_samples) index = 0;
		return sample_value;
	}

	float sample_average();
	{
		float sum = 0;
		for (int i = 0; i < num_samples; i++)
		{
			sum += buffer[i];
		}
		return (sum / num_samples);
	}



}
//end program