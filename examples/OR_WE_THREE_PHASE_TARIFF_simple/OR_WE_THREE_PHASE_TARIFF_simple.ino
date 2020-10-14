/*
   Program for isolating and publishing smartmeter modbus data to a mqtt broker by using a esp32.
*/

#define ENERGY_RX_PIN 14 // for NodeMCU: GPIO4 = D1
#define ENERGY_TX_PIN 26 // for NodeMCU: GPIO5 = D2
#define ENERGY_ADR 1     // Modbus adress

#include <HardwareSerial.h>

#include <OR_WE.h>

// instantiate ModbusMaster object
OR_WE_THREE_PHASE_TARIFF EnergyMeter;

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
  float value;
  TotalCounterTariff_t counterValue;
  TariffConfig_t tarifConfigValue;
  HolidayWeekendConfig_t holidayWeekendConfigValue;
  TimeZoneConfig_t timeZoneConfigValue;
  tm dateTimeValue;

  // Voltage
  Serial.println("Voltage");
  value = EnergyMeter.getVoltageL1();
  Serial.print("L1: ");
  Serial.print(value);
  value = EnergyMeter.getVoltageL2();
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getVoltageL3();
  Serial.print(" L3: ");
  Serial.print(value);
  Serial.println(" V");

  value = EnergyMeter.getFrequency();
  Serial.print("Freq: ");
  Serial.print(value);
  Serial.println(" Hz");

  //Current
  Serial.println("Current");
  value = EnergyMeter.getCurrentL1();
  Serial.print("L1: ");
  Serial.print(value);
  value = EnergyMeter.getCurrentL2();
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getCurrentL3();
  Serial.print(" L3: ");
  Serial.print(value);
  Serial.println(" A");

  //Active Power
  value = EnergyMeter.getActivePowerTotal() * 1000;
  Serial.print("Bezug: ");
  Serial.print(value, 0);
  Serial.println("W");
  Serial.println("ActivePower");
  Serial.print("Total ");
  Serial.print(value);
  value = EnergyMeter.getActivePowerL1() * 1000;
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getActivePowerL2() * 1000;
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getActivePowerL3() * 1000;
  Serial.print(" L3: ");
  Serial.print(value);
  Serial.println(" W");

  //Reactive Power
  Serial.println("Reactive Power");
  value = EnergyMeter.getReactivePowerTotal() * 1000;
  Serial.print("Total: ");
  Serial.print(value);
  value = EnergyMeter.getReactivePowerL1() * 1000;
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getReactivePowerL2() * 1000;
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getReactivePowerL3() * 1000;
  Serial.print(" L3: ");
  Serial.print(value);
  Serial.println(" var");

  //Apparent Power
  Serial.println("Apparent Power");
  value = EnergyMeter.getApparentPowerTotal() * 1000;
  Serial.print("Total: ");
  Serial.print(value);
  value = EnergyMeter.getApparentPowerL1() * 1000;
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getApparentPowerL2() * 1000;
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getApparentPowerL3() * 1000;
  Serial.print(" L3: ");
  Serial.print(value);
  Serial.println(" VA");

  //Power Factor
  Serial.println("Power Factor");
  value = EnergyMeter.getPowerFactorTotal();
  Serial.print("Total: ");
  Serial.print(value);
  value = EnergyMeter.getPowerFactorL1();
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getPowerFactorL2();
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getPowerFactorL3();
  Serial.print(" L3: ");
  Serial.println(value);

  //Counter
  value = EnergyMeter.getTotalCounterActivePowerTotal();
  Serial.print("Verbrauch: ");
  Serial.print(value);
  Serial.println("kWh ");
  Serial.println("Counter Active Power");
  Serial.print("Total: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerL1();
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerL2();
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerL3();
  Serial.print(" L3: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerT1();
  Serial.print(" T1: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerT2();
  Serial.print(" T2: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerT3();
  Serial.print(" T3: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterActivePowerT4();
  Serial.print(" T4: ");
  Serial.print(value);
  Serial.println(" kWh");

  Serial.println("Counter Reactive Power");
  value = EnergyMeter.getTotalCounterReactivePowerTotal();
  Serial.print("Total: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerL1();
  Serial.print(" L1: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerL2();
  Serial.print(" L2: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerL3();
  Serial.print(" L3: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerT1();
  Serial.print(" T1: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerT2();
  Serial.print(" T2: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerT3();
  Serial.print(" T3: ");
  Serial.print(value);
  value = EnergyMeter.getTotalCounterReactivePowerT4();
  Serial.print(" T4: ");
  Serial.print(value);
  Serial.println(" kvarh");

  //Counter Import
  Serial.println("Counter Import Active Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerL2());
  Serial.print(" L3: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerL3());
  Serial.print(" T1: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerT1());
  Serial.print(" T2: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerT2());
  Serial.print(" T3: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerT3());
  Serial.print(" T4: ");
  Serial.print(EnergyMeter.getImportCounterActivePowerT4());
  Serial.println(" kWh");

  Serial.println("Counter Import Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerL2());
  Serial.print(" L3: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerL3());
  Serial.print(" T1: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerT1());
  Serial.print(" T2: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerT2());
  Serial.print(" T3: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerT3());
  Serial.print(" T4: ");
  Serial.print(EnergyMeter.getImportCounterReactivePowerT4());
  Serial.println(" kvarh");

  //Counter Export
  Serial.println("Counter Export Active Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerL2());
  Serial.print(" L3: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerL3());
  Serial.print(" T1: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerT1());
  Serial.print(" T2: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerT2());
  Serial.print(" T3: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerT3());
  Serial.print(" T4: ");
  Serial.print(EnergyMeter.getExportCounterActivePowerT4());
  Serial.println(" kWh");

  Serial.println("Counter Export Reactive Power");
  Serial.print("Total: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerTotal());
  Serial.print(" L1: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerL1());
  Serial.print(" L2: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerL2());
  Serial.print(" L3: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerL3());
  Serial.print(" T1: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerT1());
  Serial.print(" T2: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerT2());
  Serial.print(" T3: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerT3());
  Serial.print(" T4: ");
  Serial.print(EnergyMeter.getExportCounterReactivePowerT4());
  Serial.println(" kvarh");

  Serial.print("getSerialNo: ");
  Serial.println(EnergyMeter.getSerialNo());
  Serial.print("get/setMeterId: ");
  Serial.println(EnergyMeter.getMeterId());
  EnergyMeter.setMeterId(1);
  Serial.println(EnergyMeter.getErrCode());
  Serial.print("get/setBusBaud: ");
  Serial.println(EnergyMeter.getBusBaud());
  EnergyMeter.setBusBaud(9600);
  Serial.println(EnergyMeter.getErrCode());
  Serial.print("getSoftwareVersion: ");
  Serial.println(EnergyMeter.getSoftwareVersion());
  Serial.print("getHardwareVersion: ");
  Serial.println(EnergyMeter.getHardwareVersion());
  Serial.print("get/setS0Rate: ");
  Serial.println(EnergyMeter.getS0Rate());
  EnergyMeter.setS0Rate(100);
  Serial.println(EnergyMeter.getS0Rate());
  Serial.println(EnergyMeter.getErrCode());
  EnergyMeter.setS0Rate(10);
  Serial.println(EnergyMeter.getS0Rate());
  Serial.println(EnergyMeter.getErrCode());
  EnergyMeter.setS0Rate(1);
  Serial.println(EnergyMeter.getS0Rate());
  Serial.println(EnergyMeter.getErrCode());
  EnergyMeter.setS0Rate(1000);
  Serial.println(EnergyMeter.getErrCode());
  Serial.print("get/setCombinedCode: ");
  Serial.println(EnergyMeter.getCombinedCode());
  EnergyMeter.setCombinedCode(1);
  Serial.println(EnergyMeter.getErrCode());
  EnergyMeter.setCombinedCode(9);
  Serial.println(EnergyMeter.getErrCode());
  EnergyMeter.setCombinedCode(5);
  Serial.println(EnergyMeter.getErrCode());
  Serial.print("get/setLcdCycleTime: ");
  Serial.println(EnergyMeter.getLcdCycleTime());
  for (uint16_t i = 1; i <= 30; i++)
  {
    EnergyMeter.setLcdCycleTime(i);
    Serial.println(EnergyMeter.getErrCode());
    Serial.println(EnergyMeter.getLcdCycleTime());
  }
  Serial.print("getCrc: ");
  Serial.println(EnergyMeter.getCrc());
  Serial.print("get/setDateTime: ");
  dateTimeValue = EnergyMeter.getDateTime();
  Serial.print(dateTimeValue.tm_mday);
  Serial.print(".");
  Serial.print(dateTimeValue.tm_mon);
  Serial.print(".");
  Serial.print(dateTimeValue.tm_year);
  Serial.print(" ");
  Serial.print(dateTimeValue.tm_hour);
  Serial.print(":");
  Serial.print(dateTimeValue.tm_min);
  Serial.print(":");
  Serial.print(dateTimeValue.tm_sec);
  Serial.print(" ");
  Serial.println(dateTimeValue.tm_wday);
  EnergyMeter.setDateTime(dateTimeValue);
  Serial.println(EnergyMeter.getErrCode());

  Serial.print("get/setHolidayWeekendTariff:");
  for (uint16_t i = 1; i <= 8; i++)
  {
    holidayWeekendConfigValue.Weekend = i;
    holidayWeekendConfigValue.Holiday = 9 - i;
    EnergyMeter.setHolidayWeekendTariff(holidayWeekendConfigValue);
    Serial.println(EnergyMeter.getErrCode());
    holidayWeekendConfigValue = EnergyMeter.getHolidayWeekendTariff();
    Serial.print(" Weekend: ");
    Serial.print(holidayWeekendConfigValue.Weekend);
    Serial.print(" Holiday: ");
    Serial.println(holidayWeekendConfigValue.Holiday);
  }
  Serial.print("get/setTimeInterval1: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval1(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval1();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval2: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval2(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval2();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval3: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval3(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval3();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval4: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval4(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval4();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval5: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval5(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval5();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval6: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval6(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval6();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval7: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval7(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval7();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeInterval8: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    tarifConfigValue.Data[i].Hour = i + 1;
    tarifConfigValue.Data[i].Minute = i + 11;
    tarifConfigValue.Data[i].TariffIndex = (i % 4) + 1;
  }
  EnergyMeter.setTimeInterval8(tarifConfigValue);
  tarifConfigValue = EnergyMeter.getTimeInterval8();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(tarifConfigValue.Data[i].Hour);
    Serial.print(":");
    Serial.print(tarifConfigValue.Data[i].Minute);
    Serial.print(" T");
    Serial.print(tarifConfigValue.Data[i].TariffIndex);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.print("get/setTimeZone: ");
  for (uint16_t i = 0; i < 8; i++)
  {
    timeZoneConfigValue.Data[i].Day = i + 11;
    timeZoneConfigValue.Data[i].Month = i + 1;
    timeZoneConfigValue.Data[i].TimeIntervall = i + 1;
  }
  EnergyMeter.setTimeZone(timeZoneConfigValue);
  timeZoneConfigValue = EnergyMeter.getTimeZone();
  for (uint16_t i = 0; i < 8; i++)
  {
    Serial.print(timeZoneConfigValue.Data[i].Day);
    Serial.print(".");
    Serial.print(timeZoneConfigValue.Data[i].Month);
    Serial.print(" Offset ");
    Serial.print(timeZoneConfigValue.Data[i].TimeIntervall);
    Serial.print(" ");
  }
  Serial.println("");
  delay(500);
}
