/*
    Name:       thermistorshenanigans.ino
*/
#include "Arduino.h"

//Measure NTC value
byte NTCPin = A0;
int SERIESRESISTOR1 = 3930;
long SERIESRESISTOR2 = 49300;
int VCC = 5;
float  T;
long NOMINAL_RESISTANCE = 100000;
int BCOEFFICIENT = 3950;
int NOMINAL_TEMPERATURE = 25;

void setup()
{
	Serial.begin(9600);
}
void loop()
{
	float ADCvalue;
	long Resistance;

	ADCvalue = sample(NTCPin);
	Serial.print("Analog value ");
	Serial.print(ADCvalue);
	Serial.print(" = ");
	//convert value to resistance
	float voltage = ADCvalue / 1023 * VCC;
	Serial.print("---voltage ");
	Serial.print(voltage);
	Resistance = SERIESRESISTOR2 / ADCvalue * 1023 - SERIESRESISTOR2 - SERIESRESISTOR1;
	Serial.print("---Resistance: ");


	Serial.print(Resistance);
	Serial.print(" Ohm");

	/*   if (Resistance > 32700)
	{
	T = 1 / (0.0020036235116798256 + 0.00005045427503670626 * log(Resistance) + 5.042674343611216e-7 * log(Resistance) * log(Resistance) * log(Resistance));
	}
	else if (Resistance < 32700)
	{
	T= 1 / (-0.007553240123376001 + 0.0015032173178446278 * log(Resistance) + -0.000004431968124543485 * log(Resistance) * log(Resistance) * log(Resistance));
	}

	else
	{
	T = 50;
	}
	T = T - 273.15;*/
	float steinhart;
	steinhart = Resistance / NOMINAL_RESISTANCE; // (R/Ro)
	steinhart = log(steinhart); // ln(R/Ro)
	steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
	steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart; // Invert
	steinhart -= 273.15; // convert to C
	T = steinhart;

	Serial.print(" -- Temperature: ");
	Serial.print(T);
	Serial.println(" c");
	delay(500);

}

/* This function will read the Pin 'z' 5 times and take an average.
*/
float sample(byte pin)
{
	float sval = 0;
	float num_samples = 50;
	for (int i = 0; i < num_samples; i++)
	{
		sval = sval + analogRead(pin) / num_samples;// sensor on analog pin 'z'
		delay(5);
	}
	return sval;
}
//end program