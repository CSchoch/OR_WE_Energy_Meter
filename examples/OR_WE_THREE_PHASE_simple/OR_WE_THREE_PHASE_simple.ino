/*
   Program for isolating and publishing smartmeter modbus data to a mqtt broker by using a esp32.
*/

#define ENERGY_RX_PIN 14 // for NodeMCU: GPIO4 = D1
#define ENERGY_TX_PIN 26 // for NodeMCU: GPIO5 = D2
#define ENERGY_ADR 1     // Modbus adress

#include <HardwareSerial.h>

#include <OR_WE.h>

// instantiate ModbusMaster object
OR_WE_THREE_PHASE EnergyMeter;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nHardware serial started");
  Serial1.begin(OR_WE_SERIAL_BAUD, OR_WE_SERIAL_MODE, ENERGY_RX_PIN, ENERGY_TX_PIN);

  // communicate with Modbus slave ID 1 over Serial (port 1)
  EnergyMeter.begin(Serial1, ENERGY_ADR);
}


void loop()
{
  Serial.println("Voltage");
  Serial.print("L1: ");
  Serial.print(EnergyMeter.getVoltageL1());

  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getVoltageL2());

  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getVoltageL3());

  Serial.print("Freq: ");
  Serial.println(EnergyMeter.getFrequency());

  //Current
  Serial.println("Current");
  Serial.print("L1: ");
  Serial.print(EnergyMeter.getCurrentL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getCurrentL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getCurrentL3());

  //Active Power
  Serial.println("ActivePower");
  Serial.print("Total ");
  Serial.print(EnergyMeter.getActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getActivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getActivePowerL3());

  //Reactive Power
  Serial.println("Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getReactivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getReactivePowerL3());

  //Apparent Power
  Serial.println("Apparent Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getApparentPowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getApparentPowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getApparentPowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getApparentPowerL3());

  //Power Factor
  Serial.println("Power Factor");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getPowerFactorTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getPowerFactorL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getPowerFactorL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getPowerFactorL3());

  //Counter
  Serial.println("Counter Active Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getTotalCounterActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getTotalCounterActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getTotalCounterActivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getTotalCounterActivePowerL3());

  Serial.println("Counter Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getTotalCounterReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getTotalCounterReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getTotalCounterReactivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getTotalCounterReactivePowerL3());

  //Counter Import
  Serial.println("Counter Import Active Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getImportCounterActivePowerL3());

  Serial.println("Counter Import Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getImportCounterReactivePowerL3());

  //Counter Export
  Serial.println("Counter Export Active Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getExportCounterActivePowerL3());

  Serial.println("Counter Export Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerL2());
  Serial.print(" L3: ");
  Serial.println(EnergyMeter.getExportCounterReactivePowerL3());

  Serial.print("getSerialNo: ");
  Serial.println(EnergyMeter.getSerialNo());
  Serial.print("getMeterId: ");
  Serial.println(EnergyMeter.getMeterId());
  Serial.print("getBusBaud: ");
  Serial.println(EnergyMeter.getBusBaud().Baud);
  Serial.print("getSoftwareVersion: ");
  Serial.println(EnergyMeter.getSoftwareVersion());
  Serial.print("getHardwareVersion: ");
  Serial.println(EnergyMeter.getHardwareVersion());
  Serial.print("getCountRate: ");
  Serial.println(EnergyMeter.getCountRate());
  Serial.print("getS0Rate: ");
  Serial.println(EnergyMeter.getS0Rate());
  Serial.print("getA3: ");
  Serial.println(EnergyMeter.getA3());
  Serial.print("getCycleTime: ");
  Serial.println(EnergyMeter.getCycleTime());
  Serial.print("getCrc: ");
  Serial.println(EnergyMeter.getCrc());
  Serial.print("getCombinedCode: ");
  Serial.println(EnergyMeter.getCombinedCode());

  Serial.println("");
  delay(500);
}
