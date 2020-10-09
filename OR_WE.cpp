#ifndef __OR_WE_H__
#define __OR_WE_H__

/* Library for reading Orno WE Modbus Energy meters.
*  Reading via Hardware or Software Serial library & rs232<->rs485 converter
*/

//------------------------------------------------------------------------------
#include "OR_WE.h"
#include "ModbusMaster.h"

//------------------------------------------------------------------------------
OR_WE::OR_WE(void)
{
}

void OR_WE::begin(Stream &serial, uint8_t slave)
{
  _node.begin(slave, serial);
}

uint8_t OR_WE::getErrCode(bool _clear)
{
  uint8_t _tmp = _result;
  if (_clear == true)
    clearErrCode();
  return (_tmp);
}

void OR_WE::clearErrCode()
{
  _result = _node.ku8MBSuccess;
}

float OR_WE::getModbusFloat(uint16_t data[2])
{
  union u_data
  {
    byte b[4];
    uint16_t data[2];
  } source;

  union u_tag
  {
    byte b[4];
    float val;
  } dest;

  source.data[0] = data[0];
  source.data[1] = data[1];

  dest.b[2] = source.b[0];
  dest.b[3] = source.b[1];
  dest.b[0] = source.b[2];
  dest.b[1] = source.b[3];

  return dest.val;
}

uint32_t OR_WE::getModbusUint32(uint16_t data[2])
{
  union u_data
  {
    byte b[4];
    uint16_t data[2];
  } source;

  union u_tag
  {
    byte b[4];
    uint32_t val;
  } dest;

  source.data[0] = data[0];
  source.data[1] = data[1];

  dest.b[2] = source.b[0];
  dest.b[3] = source.b[1];
  dest.b[0] = source.b[2];
  dest.b[1] = source.b[3];

  return dest.val;
}

tm OR_WE::getModbusTime(uint16_t data[4])
{
  union u_data
  {
    byte b[8];
    uint16_t data[4];
  } source;

  tm dest;

  source.data[0] = data[0];
  source.data[1] = data[1];
  source.data[2] = data[2];
  source.data[3] = data[3];

  dest.tm_mon = source.b[1];
  dest.tm_mday = source.b[0];
  dest.tm_year = source.b[3];
  dest.tm_hour = source.b[2];
  dest.tm_min = source.b[5];
  dest.tm_sec = source.b[4];
  dest.tm_wday = source.b[7];

  return dest;
}

uint16Array_t OR_WE::setModbusTime(tm value)
{
  union u_data
  {
    byte b[8];
    uint16_t data[4];
  } source;

  uint16Array_t dest;

  source.b[1] = value.tm_mon;
  source.b[0] = value.tm_mday;
  source.b[3] = value.tm_year;
  source.b[2] = value.tm_hour;
  source.b[5] = value.tm_min;
  source.b[4] = value.tm_sec;
  source.b[7] = value.tm_wday;

  dest.value[0] = source.data[0];
  dest.value[1] = source.data[1];
  dest.value[2] = source.data[2];
  dest.value[3] = source.data[3];

  return dest;
}

TariffConfigData_t OR_WE::getModbusTariffConfig(uint16_t data[2])
{
  union u_data
  {
    byte b[4];
    uint16_t data[2];
  } source;

  TariffConfigData_t dest;

  source.data[0] = data[0];
  source.data[1] = data[1];

  dest.Hour = source.b[1];
  dest.Minute = source.b[0];
  dest.TariffIndex = source.b[2];

  return dest;
}

uint16Array_t OR_WE::setModbusTariffConfig(TariffConfigData_t value)
{
  union u_data
  {
    byte b[4];
    uint16_t data[2];
  } source;

  uint16Array_t dest;

  source.b[1] = value.Hour;
  source.b[0] = value.Minute;
  source.b[2] = value.TariffIndex;

  dest.value[0] = source.data[0];
  dest.value[1] = source.data[1];

  return dest;
}

HolidayConfigData_t OR_WE::getModbusHolidayConfig(uint16_t data)
{
  union u_data
  {
    HolidayConfigData_t val;
    uint16_t data;
  } source;

  source.data = data;

  return source.val;
}

uint16_t OR_WE::setModbusHolidayConfig(HolidayConfigData_t value)
{
  union u_data
  {
    HolidayConfigData_t val;
    uint16_t data;
  } source;

  source.val = value;

  return source.data;
}

BaudConfig_t OR_WE::getModbusBaud(uint16_t data)
{
  union u_data
  {
    byte b[2];
    uint16_t data;
  } source;

  BaudConfig_t dest;

  source.data = data;

  switch (source.b[0])
  {
  case 1:
    dest.Baud = 1200;
    break;

  case 2:
    dest.Baud = 2400;
    break;

  case 3:
    dest.Baud = 4800;
    break;

  case 4:
    dest.Baud = 9600;
    break;

  default:
    dest.Baud = 9600;
    break;
  }

  dest.Parity = source.b[1];

  return dest;
}

uint16_t OR_WE::setModbusBaud(BaudConfig_t value)
{
  union u_data
  {
    byte b[2];
    uint16_t data;
  } source;

  switch (value.Baud)
  {
  case 1200:
    source.b[0] = 1;
    break;

  case 2400:
    source.b[0] = 2;
    break;

  case 4800:
    source.b[0] = 3;
    break;

  case 9600:
    source.b[0] = 4;
    break;

  default:
    source.b[0] = 4;
    break;
  }

  source.b[1] = value.Parity;

  return source.data;
}

//------------------------------------------------------------------------------
OR_WE_THREE_PHASE::OR_WE_THREE_PHASE(void)
{
}

//Voltage
float OR_WE_THREE_PHASE::getVoltageL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterVoltageP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getVoltageL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterVoltageP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getVoltageL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterVoltageP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Frequency
float OR_WE_THREE_PHASE::getFrequency()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterFrequency, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Current
float OR_WE_THREE_PHASE::getCurrentL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterCurrentP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getCurrentL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterCurrentP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getCurrentL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterCurrentP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Active Power
float OR_WE_THREE_PHASE::getActivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterActivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getActivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterActivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getActivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterActivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getActivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterActivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Reactive Power
float OR_WE_THREE_PHASE::getReactivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterReactivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getReactivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterReactivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getReactivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterReactivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getReactivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterReactivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Apparent Power
float OR_WE_THREE_PHASE::getApparentPowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterApparentPowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getApparentPowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterApparentPowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getApparentPowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterApparentPowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getApparentPowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterApparentPowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Power Factor
float OR_WE_THREE_PHASE::getPowerFactorTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactorSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getPowerFactorL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactorP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getPowerFactorL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactorP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getPowerFactorL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactorP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Counter
float OR_WE_THREE_PHASE::getTotalCounterActivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getTotalCounterActivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getTotalCounterActivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterActivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterActivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterActivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterActivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterActivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePowerSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getTotalCounterReactivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getTotalCounterReactivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getTotalCounterReactivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePowerSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Counter Import
float OR_WE_THREE_PHASE::getImportCounterActivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getImportCounterActivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getImportCounterActivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterActivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterActivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterActivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterActivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterActivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportActivePowerSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getImportCounterReactivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getImportCounterReactivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getImportCounterReactivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterImportReactiveSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Counter Export
float OR_WE_THREE_PHASE::getExportCounterActivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getExportCounterActivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getExportCounterActivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterActivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterActivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterActivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterActivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterActivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportActivePowerSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerTotal()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerSystem, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getExportCounterReactivePowerL1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerP1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}
float OR_WE_THREE_PHASE::getExportCounterReactivePowerL2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerP2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerL3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerP3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerT1()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerSystemT1, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerT2()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerSystemT2, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerT3()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerSystemT3, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getExportCounterReactivePowerT4()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterExportReactivePowerSystemT4, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

//Other
uint32_t OR_WE_THREE_PHASE::getSerialNo()
{
  uint8_t j;
  uint16_t data[2];
  uint32_t result = 0;

  _result = _node.readHoldingRegisters(RegisterSerial, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusUint32(data);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getMeterId()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterMeterId, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

BaudConfig_t OR_WE_THREE_PHASE::getBusBaud()
{
  BaudConfig_t result;

  _result = _node.readHoldingRegisters(RegisterBusBaud, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = getModbusBaud(_node.getResponseBuffer(0));
  }
  return result;
}

void OR_WE_THREE_PHASE::setBusBaud(BaudConfig_t value)
{
  _node.setTransmitBuffer(0, setModbusBaud(value));

  _result = _node.writeMultipleRegisters(RegisterBusBaud, 1);
}

void OR_WE_THREE_PHASE::setS0Rate(float value) 
{
  
}

void OR_WE_THREE_PHASE::setCombinedCode(uint16_t value) 
{
  
}

void OR_WE_THREE_PHASE::setLcdCycleTime(uint16_t value) 
{
  
}

void OR_WE_THREE_PHASE::setDateTime(tm value) 
{
  
}

float OR_WE_THREE_PHASE::getSoftwareVersion()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterSoftwareVersion, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

float OR_WE_THREE_PHASE::getHardwareVersion()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterHardwareVersion, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getCountRate()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterCountRate, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

float OR_WE_THREE_PHASE::getS0Rate()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterS0Rate, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusFloat(data);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getA3()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterA3, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getCycleTime()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterCycleTime, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getCrc()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterCrc, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getCombinedCode()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterCombinedCode, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

uint16_t OR_WE_THREE_PHASE::getLcdCycleTime() 
{
  
}

tm OR_WE_THREE_PHASE::getDateTime() 
{
  
}

void OR_WE_THREE_PHASE::setMeterId(uint16_t value) 
{
  
}

//------------------------------------------------------------------------------
OR_WE_THREE_PHASE_TARIFF::OR_WE_THREE_PHASE_TARIFF()
{
}

HolidayConfig_t OR_WE_THREE_PHASE_TARIFF::getHolidayWeekendTariff()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval1()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval2()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval3()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval4()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval5()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval6()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval7()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeInterval8()
{
}

TariffConfig_t OR_WE_THREE_PHASE_TARIFF::getTimeZone()
{
}

void OR_WE_THREE_PHASE_TARIFF::setHolidayWeekendTariff(HolidayConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval1(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval2(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval3(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval4(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval5(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval6(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval7(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeInterval8(TariffConfig_t value)
{
}

void OR_WE_THREE_PHASE_TARIFF::setTimeZone(TariffConfig_t value) 
{
  
}

//------------------------------------------------------------------------------
OR_WE_SINGLE_PHASE::OR_WE_SINGLE_PHASE(void)
{
}

//Voltage
float OR_WE_SINGLE_PHASE::getVoltage()
{
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterVoltage, 1);
  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0) / 100.0;
  }
  return result;
}

//Frequency
float OR_WE_SINGLE_PHASE::getFrequency()
{
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterFrequency, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0) / 100.0;
  }
  return result;
}

//Current
float OR_WE_SINGLE_PHASE::getCurrent()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterCurrent, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusUint32(data) / 1000.0;
  }
  return result;
}

//Active Power
float OR_WE_SINGLE_PHASE::getActivePower()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterActivePower, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusUint32(data) / 1000.0;
  }
  return result;
}

//Reactive Power
float OR_WE_SINGLE_PHASE::getReactivePower()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterReactivePower, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusUint32(data) / 1000.0;
  }
  return result;
}

//Apparent Power
float OR_WE_SINGLE_PHASE::getApparentPower()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterApparentPower, 2);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusUint32(data) / 1000.0;
  }
  return result;
}

//Power Factor
float OR_WE_SINGLE_PHASE::getPowerFactor()
{
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactor, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0) / 1000.0;
  }
  return result;
}

//Counter
TotalCounterTariff_t OR_WE_SINGLE_PHASE::getTotalCounterActivePower()
{
  uint8_t j;
  uint8_t k;
  uint16_t data[2];
  TotalCounterTariff_t result;

  _result = _node.readHoldingRegisters(RegisterTotalActivePower, 10);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    k = 0;
    for (j = 0; j < 10; j++)
    {
      data[k] = _node.getResponseBuffer(j);
      k++;
      switch (j)
      {
      case 1:
        result.Total = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 3:
        result.T1 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 5:
        result.T2 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 7:
        result.T3 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 9:
        result.T4 = getModbusUint32(data) / 100.0;
        k = 0;
        break;
      }
    }
  }
  return result;
}

TotalCounterTariff_t OR_WE_SINGLE_PHASE::getTotalCounterReactivePower()
{
  uint8_t j;
  uint8_t k;
  uint16_t data[2];
  TotalCounterTariff_t result;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 10);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    k = 0;
    for (j = 0; j < 10; j++)
    {
      data[k] = _node.getResponseBuffer(j);
      k++;
      switch (j)
      {
      case 1:
        result.Total = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 3:
        result.T1 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 5:
        result.T2 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 7:
        result.T3 = getModbusUint32(data) / 100.0;
        k = 0;
        break;

      case 9:
        result.T4 = getModbusUint32(data) / 100.0;
        k = 0;
        break;
      }
    }
  }
  return result;
}

//Other
uint16_t OR_WE_SINGLE_PHASE::getMeterId()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterMeterId, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

BaudConfig_t OR_WE_SINGLE_PHASE::getBusBaud()
{
  BaudConfig_t result;

  _result = _node.readHoldingRegisters(RegisterBusBaud, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = getModbusBaud(_node.getResponseBuffer(0));
  }
  return result;
}

void OR_WE_SINGLE_PHASE::setBusBaud(BaudConfig_t value)
{
  _node.setTransmitBuffer(0, setModbusBaud(value));

  _result = _node.writeMultipleRegisters(RegisterBusBaud, 1);
}

// uint16_t OR_WE_SINGLE_PHASE::getLcdState()
// {
//   uint16_t result = 0;

//   _result = _node.readHoldingRegisters(RegisterLcdState, 1);

//   // do something with data if read is successful
//   if (_result == _node.ku8MBSuccess)
//   {
//     result = _node.getResponseBuffer(0);
//   }
//   return result;
// }

//------------------------------------------------------------------------------
OR_WE_SINGLE_PHASE_TARIFF::OR_WE_SINGLE_PHASE_TARIFF(void)
{
}

TariffConfig_t OR_WE_SINGLE_PHASE_TARIFF::getWeekdayTariff()
{
  uint8_t j;
  uint8_t k;
  uint16_t data[2];
  TariffConfig_t result;

  _result = _node.readHoldingRegisters(RegisterWeekdayTariff, 16);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    k = 0;
    for (j = 0; j < 16; j++)
    {
      data[k] = _node.getResponseBuffer(j);
      k++;
      if (k == 2)
      {
        result.Data[j / 2] = getModbusTariffConfig(data);
        k = 0;
      }
    }
  }
  return result;
}

TariffConfig_t OR_WE_SINGLE_PHASE_TARIFF::getWeekendTariff()
{
  uint8_t j;
  uint8_t k;
  uint16_t data[2];
  TariffConfig_t result;

  _result = _node.readHoldingRegisters(RegisterWeekendTariff, 16);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    k = 0;
    for (j = 0; j < 16; j++)
    {
      data[k] = _node.getResponseBuffer(j);
      k++;
      if (k == 2)
      {
        result.Data[j / 2] = getModbusTariffConfig(data);
        k = 0;
      }
    }
  }
  return result;
}

TariffConfig_t OR_WE_SINGLE_PHASE_TARIFF::getHolidayTariff()
{
  uint8_t j;
  uint8_t k;
  uint16_t data[2];
  TariffConfig_t result;

  _result = _node.readHoldingRegisters(RegisterHolidayTariff, 16);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    k = 0;
    for (j = 0; j < 16; j++)
    {
      data[k] = _node.getResponseBuffer(j);
      k++;
      if (k == 2)
      {
        result.Data[j / 2] = getModbusTariffConfig(data);
        k = 0;
      }
    }
  }
  return result;
}

HolidayConfig_t OR_WE_SINGLE_PHASE_TARIFF::getHoliday()
{
  uint8_t j;
  uint16_t data;
  HolidayConfig_t result;

  _result = _node.readHoldingRegisters(RegisterHoliday, 100);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 100; j++)
    {
      data = _node.getResponseBuffer(j);
      result.Data[j] = getModbusHolidayConfig(data);
    }
  }
  return result;
}

tm OR_WE_SINGLE_PHASE_TARIFF::getDateTime()
{
  uint8_t j;
  uint16_t data[4];
  tm result;

  _result = _node.readHoldingRegisters(RegisterDateTime, 4);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    for (j = 0; j < 4; j++)
    {
      data[j] = _node.getResponseBuffer(j);
    }
    result = getModbusTime(data);
  }
  return result;
}

void OR_WE_SINGLE_PHASE_TARIFF::setWeekdayTariff(TariffConfig_t value)
{
  uint8_t j;
  uint8_t k;
  uint16Array_t data;

  for (j = 0; j < 8; j++)
  {
    data = setModbusTariffConfig(value.Data[j]);
    for (k = 0; k < 2; k++)
    {
      _node.setTransmitBuffer(j * 2 + k, data.value[k]);
    }
  }
  _result = _node.writeMultipleRegisters(RegisterWeekdayTariff, 16);
}

void OR_WE_SINGLE_PHASE_TARIFF::setWeekendTariff(TariffConfig_t value)
{
  uint8_t j;
  uint8_t k;
  uint16Array_t data;

  for (j = 0; j < 8; j++)
  {
    data = setModbusTariffConfig(value.Data[j]);
    for (k = 0; k < 2; k++)
    {
      _node.setTransmitBuffer(j * 2 + k, data.value[k]);
    }
  }
  _result = _node.writeMultipleRegisters(RegisterWeekendTariff, 16);
}

void OR_WE_SINGLE_PHASE_TARIFF::setHolidayTariff(TariffConfig_t value)
{
  uint8_t j;
  uint8_t k;
  uint16Array_t data;

  for (j = 0; j < 8; j++)
  {
    data = setModbusTariffConfig(value.Data[j]);
    for (k = 0; k < 2; k++)
    {
      _node.setTransmitBuffer(j * 2 + k, data.value[k]);
    }
  }
  _result = _node.writeMultipleRegisters(RegisterHolidayTariff, 16);
}

void OR_WE_SINGLE_PHASE_TARIFF::setHoliday(HolidayConfig_t value)
{
  uint8_t j;

  for (j = 0; j < 100; j++)
  {
    _node.setTransmitBuffer(j, setModbusHolidayConfig(value.Data[j]));
  }
  _result = _node.writeMultipleRegisters(RegisterHoliday, 100);
}

void OR_WE_SINGLE_PHASE_TARIFF::setDateTime(tm value)
{
  uint8_t j;
  uint16Array_t data;

  data = setModbusTime(value);
  for (j = 0; j < 4; j++)
  {
    _node.setTransmitBuffer(j, data.value[j]);
  }
  _result = _node.writeMultipleRegisters(RegisterDateTime, 4);
}

#endif // __OR_WE_H__