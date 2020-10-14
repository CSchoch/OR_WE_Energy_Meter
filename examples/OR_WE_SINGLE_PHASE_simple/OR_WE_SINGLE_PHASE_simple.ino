/*
   Program for isolating and publishing smartmeter modbus data to a mqtt broker by using a esp32.
*/

#define ENERGY_RX_PIN 4  // for NodeMCU: GPIO4 = D1
#define ENERGY_TX_PIN 15 // for NodeMCU: GPIO5 = D2
#define ENERGY_ADR 1     // Modbus adress

#include <HardwareSerial.h>
#include <OR_WE.h>

OR_WE_SINGLE_PHASE EnergyMeter;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nHardware serial started");

  Serial1.begin(OR_WE_SERIAL_BAUD, OR_WE_SERIAL_MODE, ENERGY_RX_PIN, ENERGY_TX_PIN);
  // communicate with Modbus slave ID 1 over Serial (port 1)
  EnergyMeter.begin(Serial1, ENERGY_ADR);
  Serial.println("\nEnergy meter serial started");
}

void loop()
{

  float value;
  TotalCounterTariff_t counterValue;

  Serial.println("Voltage");
  value = EnergyMeter.getVoltage();
  Serial.print(value);
  Serial.println(" V");

  value = EnergyMeter.getFrequency();
  Serial.print("Freq: ");
  Serial.print(value);
  Serial.println(" Hz");

  //Current
  Serial.println("Current");
  value = EnergyMeter.getCurrent();
  Serial.print(value);
  Serial.println(" A");

  //Active Power
  value = EnergyMeter.getActivePower() * 1000;
  Serial.print("Bezug: ");
  Serial.print(value, 0);
  Serial.println( "W");
  Serial.println("ActivePower");
  Serial.print(value, 0);
  Serial.println(" W");

  //Reactive Power
  Serial.println("Reactive Power");
  value = EnergyMeter.getReactivePower() * 1000;
  Serial.print(value);
  Serial.println(" var");

  //Apparent Power
  Serial.println("Apparent Power");
  value = EnergyMeter.getApparentPower() * 1000;
  Serial.print(value);
  Serial.println(" VA");

  //Power Factor
  Serial.println("Power Factor");
  value = EnergyMeter.getPowerFactor();
  Serial.println(value);

  //Counter
  counterValue = EnergyMeter.getTotalCounterActivePower();
  Serial.print("Verbrauch: ");
  Serial.print(counterValue.Total);
  Serial.println("kWh ");
  Serial.println("Counter Active Power");
  Serial.print("Total: ");
  Serial.print(counterValue.Total);
  Serial.print(" T1: ");
  Serial.print(counterValue.T1);
  Serial.print(" T2: ");
  Serial.print(counterValue.T2);
  Serial.print(" T3: ");
  Serial.print(counterValue.T3);
  Serial.print(" T3: ");
  Serial.print(counterValue.T4);
  Serial.println(" kWh");

  Serial.println("Counter Reactive Power");
  counterValue = EnergyMeter.getTotalCounterReactivePower();
  Serial.print("Total: ");
  Serial.print(counterValue.Total);
  Serial.print(" T1: ");
  Serial.print(counterValue.T1);
  Serial.print(" T2: ");
  Serial.print(counterValue.T2);
  Serial.print(" T3: ");
  Serial.print(counterValue.T3);
  Serial.print(" T4: ");
  Serial.print(counterValue.T4);
  Serial.println(" kvarh");

  // Other
  Serial.print("getMeterId: ");
  Serial.println(EnergyMeter.getMeterId());
  Serial.print("getBusBaud: ");
  Serial.print(EnergyMeter.getBusBaud().Baud);
  Serial.print(" ");
  Serial.println(EnergyMeter.getBusBaud().Parity);

  delay(100);
}