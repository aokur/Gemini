#include <Arduino.h>
#include <main.h>

void setup(void)
{
  pinMode(VD_POWER_PIN_2, OUTPUT);
  pinMode(VD_POWER_PIN_3, OUTPUT);
  // pinMode(VD_POWER_PIN_4, OUTPUT);
  // pinMode(VD_POWER_PIN_5, OUTPUT);

  Serial.begin(9600);
}

// take voltage readings from the voltage divider
float readAnalog(int powerPin, int analogPin)
{
  float average = 0;

  digitalWrite(powerPin, HIGH);
  for (size_t i = 0; i < SAMPLING_RATE; i++)
  {
    average += analogRead(analogPin);
    delay(10);
  }
  digitalWrite(powerPin, LOW);

  average = average / SAMPLING_RATE;
  return average;
}

float calculateResistance(float analogValue)
{
  float resistance = 0;
  resistance = (1023 / analogValue) - 1;
  resistance = SERIESRESISTOR / resistance;

#if defined(DEBUG)
  Serial.print(resistance);
  Serial.println(" Ohm");
#endif

  return resistance;
}

float steinhartCalculation(float resistance)
{
  float steinhart = 0.0f;
  steinhart = resistance / NOMINAL_RESISTANCE;       // (R/Ro)
  steinhart = log(steinhart);                        // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                       // Invert
  steinhart -= 273.15;                               // Convert to celsius

  return steinhart;
}

void loop(void)
{
  float analogRead_1 = readAnalog(VD_POWER_PIN_2, NTC_PIN_A0);
  float analogRead_2 = readAnalog(VD_POWER_PIN_3, NTC_PIN_A1);
  // float analogRead_3 = readAnalog(VD_POWER_PIN_4, NTC_PIN_A2);
  // float analogRead_4 = readAnalog(VD_POWER_PIN_5, NTC_PIN_A3);

  float resistance_1 = calculateResistance(analogRead_1);
  float resistance_2 = calculateResistance(analogRead_2);
  // float resistance_3 = calculateResistance(analogRead_3);
  // float resistance_4 = calculateResistance(analogRead_4);

  float steinhart_1 = steinhartCalculation(resistance_1);
  float steinhart_2 = steinhartCalculation(resistance_2);
  // float steinhart_3 = steinhartCalculation(resistance_3);
  // float steinhart_4 = steinhartCalculation(resistance_4);

#if defined(DEBUG)
  // Serial.print("Temperature ");
  // Serial.print(steinhart_1);
  // Serial.println(" oC");

  // Serial.print("Temperature ");
  // Serial.print(steinhart_2);
  // Serial.println(" oC");

  // Serial.print("Temperature ");
  // Serial.print(steinhart_3);
  // Serial.println(" oC");

  // Serial.print("Temperature ");
  // Serial.print(steinhart_4);
  // Serial.println(" oC");
#endif

  delay(1000);
}