//Measure NTC value
byte NTCPin = A0;
long SERIESRESISTOR1 = 24300;
long SERIESRESISTOR2 = 133900;
float VCC = 3.33;
float  T;
long NOMINAL_RESISTANCE = 100000;
int BCOEFFICIENT = 3950;
int NOMINAL_TEMPERATURE = 25;

void setup()
{
  Serial.begin(9600);
  analogReference(EXTERNAL);
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
 
    if (Resistance > 37000) 
  {
    T = 1.0 / (0.00024807263798212265 + 0.00027560090866740535 * log(Resistance) + -4.5102113312005025e-8   * log(Resistance) * log(Resistance) * log(Resistance));
  }
   else if (Resistance < 37000) 
  {
   T = 1.0 / (-0.0006453822260400147 + 0.00040907100900559705 * log(Resistance) + -4.837240189412059e-7    * log(Resistance) * log(Resistance) * log(Resistance));
  }
  else 
  {
    T = 50.0;
  }
  T = T - 273.15;
//  float steinhart;
//  steinhart = (float)Resistance / NOMINAL_RESISTANCE; // (R/Ro)
//  steinhart = log(steinhart); // ln(R/Ro)
//  steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
//  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
//  steinhart = 1.0 / steinhart; // Invert
//  steinhart -= 273.15; // convert to C
//  T = steinhart;

  Serial.print(" -- Temperature: "); 
  Serial.print(T);
  Serial.println(" c"); 
}

/* This function will read the Pin 'z' 5 times and take an average.
 */
float sample(byte pin)
{
  float sval = 0;
  float num_samples = 2000;
  for (int i = 0; i < num_samples; i++)
  {
    sval = sval + analogRead(pin)/num_samples;// sensor on analog pin 'z'
    delay (1);
  }
  return sval;
}
//end program
