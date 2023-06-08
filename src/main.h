#define DEBUG

// Resistance definitions
#define NOMINAL_RESISTANCE 10000  // Nominal resistance at 25⁰C
#define NOMINAL_TEMPERATURE 25    // Temperature for nominal resistance (almost always 25⁰ C)

#define SERIESRESISTOR 10000
#define SAMPLING_RATE 5           // Number of samples
#define BCOEFFICIENT 3950         // The beta coefficient or the B value of the thermistor (usually 3000-4000) check the datasheet for the accurate value.

// Analog pins definitions
#define NTC_PIN_A0 A0
#define NTC_PIN_A1 A1
#define NTC_PIN_A2 A2
#define NTC_PIN_A3 A3

#define VD_POWER_PIN_2 2
#define VD_POWER_PIN_3 3
#define VD_POWER_PIN_4 4
#define VD_POWER_PIN_5 5