/* Library for reading Orno WE Modbus Energy meters.
*  Reading via Hardware or Software Serial library & rs232<->rs485 converter
*/

//------------------------------------------------------------------------------
#ifndef OR_WE_h
#define OR_WE_h
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <ModbusMaster.h>
//------------------------------------------------------------------------------
#define OR_WE_SERIAL_BAUD 9600
#define OR_WE_SERIAL_MODE SERIAL_8E1

//------------------------------------------------------------------------------
struct TotalCounterTarif_t
{
  float Total;
  float T1;
  float T2;
  float T3;
  float T4;
};

//------------------------------------------------------------------------------
struct TarifConfigData_t
{
  uint8_t Hour;
  uint8_t Minute;
  uint8_t TarifIndex;
};

struct TarifConfig_t
{
  TarifConfigData_t Data[8];
};

//------------------------------------------------------------------------------
struct HolidayConfigData_t
{
  uint8_t Month;
  uint8_t Day;
};

struct HolidayConfig_t
{
  HolidayConfigData_t Data[100];
};

struct uint16Array_t
{
  uint16_t value[4];
};

//------------------------------------------------------------------------------
class OR_WE
{
public:
  OR_WE();

  void begin(Stream &serial, uint8_t slave);

  uint8_t getErrCode(bool _clear = false); //return last errorcode (optional clear this value, default flase)
  void clearErrCode();                     //clear last errorcode

protected:
  // instantiate ModbusMaster object
  ModbusMaster _node;
  uint8_t _result = _node.ku8MBSuccess;

  float getModbusFloat(uint16_t data[2]);
  uint32_t getModbusUint32(uint16_t data[2]);
  tm getModbusTime(uint16_t data[4]);
  uint16Array_t setModbusTime(tm vale);
  TarifConfigData_t getModbusTarifConfig(uint16_t data[2]);
  uint16Array_t setModbusTarifConfig(TarifConfigData_t value);
  HolidayConfigData_t getModbusHolidayConfig(uint16_t data);
  uint16_t setModbusHolidayConfig(HolidayConfigData_t value);
};

class OR_WE_SINGLE_PHASE : public OR_WE
{
public:
  OR_WE_SINGLE_PHASE();

  //Voltage
  float getVoltage();

  //Frequency
  float getFrequency();

  //Current
  float getCurrent();

  //Active Power
  float getActivePower();

  //Reactive Power
  float getReactivePower();

  //Apparent Power
  float getApparentPower();

  //Power Factor
  float getPowerFactor();

  //Counter
  TotalCounterTarif_t getTotalCounterActivePower();
  TotalCounterTarif_t getTotalCounterReactivePower();

  //Other
  uint16_t getMeterId();
  uint16_t getBusBaud();
  uint16_t getLcdState();

protected:
  //OR_WE registers
  //Voltages
  static const uint16_t RegisterVoltage = 0x0131;

  //Frequency
  static const uint16_t RegisterFrequency = 0x0130;

  //Current
  static const uint16_t RegisterCurrent = 0x0139;

  //Active Power
  static const uint16_t RegisterActivePower = 0x0140;

  //Reactive Power
  static const uint16_t RegisterReactivePower = 0x0148;

  //Apparent Power
  static const uint16_t RegisterApparentPower = 0x0150;

  //Power Factor
  static const uint16_t RegisterPowerFactor = 0x0158;

  //Counter
  static const uint16_t RegisterTotalActivePower = 0xA000;
  static const uint16_t RegisterTotalReactivePower = 0xA01E;

  //Other
  static const uint16_t RegisterMeterId = 0x0110;
  static const uint16_t RegisterBusBaud = 0x0111;
  static const uint16_t RegisterLcdState = 0x0112;
};

class OR_WE_SINGLE_PHASE_TARIF : public OR_WE_SINGLE_PHASE
{
public:
  OR_WE_SINGLE_PHASE_TARIF();

  //Other
  TarifConfig_t getWeekdayTarif();
  TarifConfig_t getTotalWeekendTarif();
  TarifConfig_t getHolidayTarif();
  HolidayConfig_t getHoliday();
  tm getDateTime();

  void setWeekdayTarif(TarifConfig_t value);
  void setTotalWeekendTarif(TarifConfig_t value);
  void setHolidayTarif(TarifConfig_t value);
  void setHoliday(HolidayConfig_t value);
  void setDateTime(tm value);

protected:
  //OR_WE registers
  //Other
  static const uint16_t RegisterWeekdayTarif = 0x8100;
  static const uint16_t RegisterWeekendTarif = 0x8110;
  static const uint16_t RegisterHolidayTarif = 0x8130;
  static const uint16_t RegisterHoliday = 0x8140;
  static const uint16_t RegisterDateTime = 0x8120;
};

class OR_WE_THRE_PHASE : public OR_WE
{
public:
  OR_WE_THRE_PHASE();

  //Voltage
  float getVoltageL1();
  float getVoltageL2();
  float getVoltageL3();

  //Frequency
  float getFrequency();

  //Current
  float getCurrentL1();
  float getCurrentL2();
  float getCurrentL3();

  //Active Power
  float getActivePowerTotal();
  float getActivePowerL1();
  float getActivePowerL2();
  float getActivePowerL3();

  //Reactive Power
  float getReactivePowerTotal();
  float getReactivePowerL1();
  float getReactivePowerL2();
  float getReactivePowerL3();

  //Apparent Power
  float getApparentPowerTotal();
  float getApparentPowerL1();
  float getApparentPowerL2();
  float getApparentPowerL3();

  //Power Factor
  float getPowerFactorTotal();
  float getPowerFactorL1();
  float getPowerFactorL2();
  float getPowerFactorL3();

  //Counter
  float getTotalCounterActivePowerTotal();
  float getTotalCounterActivePowerL1();
  float getTotalCounterActivePowerL2();
  float getTotalCounterActivePowerL3();

  float getTotalCounterReactivePowerTotal();
  float getTotalCounterReactivePowerL1();
  float getTotalCounterReactivePowerL2();
  float getTotalCounterReactivePowerL3();

  //Counter Import
  float getImportCounterActivePowerTotal();
  float getImportCounterActivePowerL1();
  float getImportCounterActivePowerL2();
  float getImportCounterActivePowerL3();

  float getImportCounterReactivePowerTotal();
  float getImportCounterReactivePowerL1();
  float getImportCounterReactivePowerL2();
  float getImportCounterReactivePowerL3();

  //Counter Export
  float getExportCounterActivePowerTotal();
  float getExportCounterActivePowerL1();
  float getExportCounterActivePowerL2();
  float getExportCounterActivePowerL3();

  float getExportCounterReactivePowerTotal();
  float getExportCounterReactivePowerL1();
  float getExportCounterReactivePowerL2();
  float getExportCounterReactivePowerL3();

  //Other
  uint32_t getSerialNo();
  uint16_t getMeterId();
  uint16_t getBusBaud();
  float getSoftwareVersion();
  float getHardwareVersion();
  uint16_t getCountRate();
  float getS0Rate();
  uint16_t getA3();
  uint16_t getCycleTime();
  uint16_t getCrc();
  uint16_t getCombinedCode();

protected:
  //OR_WE registers
  //Voltages
  static const uint16_t RegisterVoltageP1 = 0x000E;
  static const uint16_t RegisterVoltageP2 = 0x0010;
  static const uint16_t RegisterVoltageP3 = 0x0012;

  //Frequency
  static const uint16_t RegisterFrequency = 0x0014;

  //Current
  static const uint16_t RegisterCurrentP1 = 0x0016;
  static const uint16_t RegisterCurrentP2 = 0x0018;
  static const uint16_t RegisterCurrentP3 = 0x001A;

  //Active Power
  static const uint16_t RegisterActivePowerSystem = 0x001C;
  static const uint16_t RegisterActivePowerP1 = 0x001E;
  static const uint16_t RegisterActivePowerP2 = 0x0020;
  static const uint16_t RegisterActivePowerP3 = 0x0022;

  //Reactive Power
  static const uint16_t RegisterReactivePowerSystem = 0x0024;
  static const uint16_t RegisterReactivePowerP1 = 0x0026;
  static const uint16_t RegisterReactivePowerP2 = 0x0028;
  static const uint16_t RegisterReactivePowerP3 = 0x002A;

  //Apparent Power
  static const uint16_t RegisterApparentPowerSystem = 0x002C;
  static const uint16_t RegisterApparentPowerP1 = 0x002E;
  static const uint16_t RegisterApparentPowerP2 = 0x0030;
  static const uint16_t RegisterApparentPowerP3 = 0x0032;

  //Power Factor
  static const uint16_t RegisterPowerFactorSystem = 0x0034;
  static const uint16_t RegisterPowerFactorP1 = 0x0036;
  static const uint16_t RegisterPowerFactorP2 = 0x0038;
  static const uint16_t RegisterPowerFactorP3 = 0x003A;

  //Counter
  static const uint16_t RegisterTotalActivePowerSystem = 0x0100;
  static const uint16_t RegisterTotalActivePowerP1 = 0x0102;
  static const uint16_t RegisterTotalActivePowerP2 = 0x0104;
  static const uint16_t RegisterTotalActivePowerP3 = 0x0106;
  static const uint16_t RegisterTotalActivePowerSystemT1 = 0x0130; // Todo
  static const uint16_t RegisterTotalActivePowerSystemT2 = 0x013C; // Todo
  static const uint16_t RegisterTotalActivePowerSystemT3 = 0x0148; // Todo
  static const uint16_t RegisterTotalActivePowerSystemT4 = 0x0154; // Todo

  static const uint16_t RegisterTotalReactivePowerSystem = 0x0118;
  static const uint16_t RegisterTotalReactivePowerP1 = 0x011A;
  static const uint16_t RegisterTotalReactivePowerP2 = 0x011C;
  static const uint16_t RegisterTotalReactivePowerP3 = 0x011E;
  static const uint16_t RegisterTotalReactivePowerSystemT1 = 0x0136; // Todo
  static const uint16_t RegisterTotalReactivePowerSystemT2 = 0x0142; // Todo
  static const uint16_t RegisterTotalReactivePowerSystemT3 = 0x014E; // Todo
  static const uint16_t RegisterTotalReactivePowerSystemT4 = 0x015A; // Todo

  //Counter Import
  static const uint16_t RegisterImportActivePowerSystem = 0x0108;
  static const uint16_t RegisterImportActivePowerP1 = 0x010A;
  static const uint16_t RegisterImportActivePowerP2 = 0x010C;
  static const uint16_t RegisterImportActivePowerP3 = 0x010E;
  static const uint16_t RegisterImportActivePowerSystemT1 = 0x0132; // Todo
  static const uint16_t RegisterImportActivePowerSystemT2 = 0x013E; // Todo
  static const uint16_t RegisterImportActivePowerSystemT3 = 0x014A; // Todo
  static const uint16_t RegisterImportActivePowerSystemT4 = 0x0156; // Todo

  static const uint16_t RegisterImportReactiveSystem = 0x0120;
  static const uint16_t RegisterImportReactiveP1 = 0x0122;
  static const uint16_t RegisterImportReactiveP2 = 0x0124;
  static const uint16_t RegisterImportReactiveP3 = 0x0126;
  static const uint16_t RegisterImportReactiveSystemT1 = 0x0138; // Todo
  static const uint16_t RegisterImportReactiveSystemT2 = 0x0144; // Todo
  static const uint16_t RegisterImportReactiveSystemT3 = 0x0150; // Todo
  static const uint16_t RegisterImportReactiveSystemT4 = 0x015C; // Todo

  //Counter Export
  static const uint16_t RegisterExportActivePowerSystem = 0x0110;
  static const uint16_t RegisterExportActivePowerP1 = 0x0112;
  static const uint16_t RegisterExportActivePowerP2 = 0x0114;
  static const uint16_t RegisterExportActivePowerP3 = 0x0116;
  static const uint16_t RegisterExportActivePowerSystemT1 = 0x0134; // Todo
  static const uint16_t RegisterExportActivePowerSystemT2 = 0x0140; // Todo
  static const uint16_t RegisterExportActivePowerSystemT3 = 0x014C; // Todo
  static const uint16_t RegisterExportActivePowerSystemT4 = 0x0158; // Todo

  static const uint16_t RegisterExportReactivePowerSystem = 0x0128;
  static const uint16_t RegisterExportReactivePowerP1 = 0x012A;
  static const uint16_t RegisterExportReactivePowerP2 = 0x012C;
  static const uint16_t RegisterExportReactivePowerP3 = 0x012E;
  static const uint16_t RegisterExportReactivePowerSystemT1 = 0x013A; // Todo
  static const uint16_t RegisterExportReactivePowerSystemT2 = 0x0146; // Todo
  static const uint16_t RegisterExportReactivePowerSystemT3 = 0x0152; // Todo
  static const uint16_t RegisterExportReactivePowerSystemT4 = 0x015E; // Todo

  //Other
  static const uint16_t RegisterSerial = 0x0000;
  static const uint16_t RegisterMeterId = 0x0002;
  static const uint16_t RegisterBusBaud = 0x0003;
  static const uint16_t RegisterSoftwareVersion = 0x0004;
  static const uint16_t RegisterHardwareVersion = 0x0006;
  static const uint16_t RegisterCountRate = 0x0008;
  static const uint16_t RegisterS0Rate = 0x0009;
  static const uint16_t RegisterA3 = 0x000B;
  static const uint16_t RegisterCycleTime = 0x000D;
  static const uint16_t RegisterCrc = 0x0041;
  static const uint16_t RegisterCombinedCode = 0x0042;
  static const uint16_t RegisterDateTime = 0x003C;     // Todo
  static const uint16_t RegisterLcdCycleTine = 0x000D; // Todo
};

class OR_WE_THRE_PHASE_TARIF : public OR_WE_THRE_PHASE
{
public:
  OR_WE_THRE_PHASE_TARIF();

  //Counter Export
  float getExportCounterActivePowerTotal();
  float getExportCounterActivePowerL1();
  float getExportCounterActivePowerL2();
  float getExportCounterActivePowerL3();

  float getExportCounterReactivePowerTotal();
  float getExportCounterReactivePowerL1();
  float getExportCounterReactivePowerL2();
  float getExportCounterReactivePowerL3();

protected:
  //OR_WE registers
  //Other
  static const uint16_t RegisterHolidayWeekendTarif = 0x000C;
  // Hier weiter
};
#endif //OR_WE_h
