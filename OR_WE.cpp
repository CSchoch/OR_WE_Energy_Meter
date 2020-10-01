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
    float result = -1;

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
    float result = -1;

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

//------------------------------------------------------------------------------
OR_WE_THRE_PHASE::OR_WE_THRE_PHASE(void)
{
}

//Voltage
float OR_WE_THRE_PHASE::getVoltageL1()
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

float OR_WE_THRE_PHASE::getVoltageL2()
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

float OR_WE_THRE_PHASE::getVoltageL3()
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
float OR_WE_THRE_PHASE::getFrequency()
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
float OR_WE_THRE_PHASE::getCurrentL1()
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

float OR_WE_THRE_PHASE::getCurrentL2()
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

float OR_WE_THRE_PHASE::getCurrentL3()
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
float OR_WE_THRE_PHASE::getActivePowerTotal()
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

float OR_WE_THRE_PHASE::getActivePowerL1()
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

float OR_WE_THRE_PHASE::getActivePowerL2()
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

float OR_WE_THRE_PHASE::getActivePowerL3()
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
float OR_WE_THRE_PHASE::getReactivePowerTotal()
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

float OR_WE_THRE_PHASE::getReactivePowerL1()
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

float OR_WE_THRE_PHASE::getReactivePowerL2()
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
float OR_WE_THRE_PHASE::getReactivePowerL3()
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
float OR_WE_THRE_PHASE::getApparentPowerTotal()
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
float OR_WE_THRE_PHASE::getApparentPowerL1()
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
float OR_WE_THRE_PHASE::getApparentPowerL2()
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
float OR_WE_THRE_PHASE::getApparentPowerL3()
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
float OR_WE_THRE_PHASE::getPowerFactorTotal()
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
float OR_WE_THRE_PHASE::getPowerFactorL1()
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
float OR_WE_THRE_PHASE::getPowerFactorL2()
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
float OR_WE_THRE_PHASE::getPowerFactorL3()
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
float OR_WE_THRE_PHASE::getTotalCounterActivePowerTotal()
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
float OR_WE_THRE_PHASE::getTotalCounterActivePowerL1()
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
float OR_WE_THRE_PHASE::getTotalCounterActivePowerL2()
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
float OR_WE_THRE_PHASE::getTotalCounterActivePowerL3()
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

float OR_WE_THRE_PHASE::getTotalCounterReactivePowerTotal()
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
float OR_WE_THRE_PHASE::getTotalCounterReactivePowerL1()
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
float OR_WE_THRE_PHASE::getTotalCounterReactivePowerL2()
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
float OR_WE_THRE_PHASE::getTotalCounterReactivePowerL3()
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

//Counter Import
float OR_WE_THRE_PHASE::getImportCounterActivePowerTotal()
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
float OR_WE_THRE_PHASE::getImportCounterActivePowerL1()
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
float OR_WE_THRE_PHASE::getImportCounterActivePowerL2()
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
float OR_WE_THRE_PHASE::getImportCounterActivePowerL3()
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

float OR_WE_THRE_PHASE::getImportCounterReactivePowerTotal()
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
float OR_WE_THRE_PHASE::getImportCounterReactivePowerL1()
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
float OR_WE_THRE_PHASE::getImportCounterReactivePowerL2()
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
float OR_WE_THRE_PHASE::getImportCounterReactivePowerL3()
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

//Counter Export
float OR_WE_THRE_PHASE::getExportCounterActivePowerTotal()
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
float OR_WE_THRE_PHASE::getExportCounterActivePowerL1()
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
float OR_WE_THRE_PHASE::getExportCounterActivePowerL2()
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

float OR_WE_THRE_PHASE::getExportCounterActivePowerL3()
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

float OR_WE_THRE_PHASE::getExportCounterReactivePowerTotal()
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
float OR_WE_THRE_PHASE::getExportCounterReactivePowerL1()
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
float OR_WE_THRE_PHASE::getExportCounterReactivePowerL2()
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

float OR_WE_THRE_PHASE::getExportCounterReactivePowerL3()
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

//Other
uint32_t OR_WE_THRE_PHASE::getSerialNo()
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

uint16_t OR_WE_THRE_PHASE::getMeterId()
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

uint16_t OR_WE_THRE_PHASE::getBusBaud()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterBusBaud, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

float OR_WE_THRE_PHASE::getSoftwareVersion()
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

float OR_WE_THRE_PHASE::getHardwareVersion()
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

uint16_t OR_WE_THRE_PHASE::getCountRate()
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

float OR_WE_THRE_PHASE::getS0Rate()
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

uint16_t OR_WE_THRE_PHASE::getA3()
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

uint16_t OR_WE_THRE_PHASE::getCycleTime()
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

uint16_t OR_WE_THRE_PHASE::getCrc()
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

uint16_t OR_WE_THRE_PHASE::getCombinedCode()
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

//------------------------------------------------------------------------------
OR_WE_THRE_PHASE_TARIF::OR_WE_THRE_PHASE_TARIF(void)
{
}

//Counter Export
float OR_WE_THRE_PHASE_TARIF::getExportCounterActivePowerTotal()
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
float OR_WE_THRE_PHASE_TARIF::getExportCounterActivePowerL1()
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
float OR_WE_THRE_PHASE_TARIF::getExportCounterActivePowerL2()
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

float OR_WE_THRE_PHASE_TARIF::getExportCounterActivePowerL3()
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

float OR_WE_THRE_PHASE_TARIF::getExportCounterReactivePowerTotal()
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
float OR_WE_THRE_PHASE_TARIF::getExportCounterReactivePowerL1()
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
float OR_WE_THRE_PHASE_TARIF::getExportCounterReactivePowerL2()
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

float OR_WE_THRE_PHASE_TARIF::getExportCounterReactivePowerL3()
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

//------------------------------------------------------------------------------
OR_WE_SINGLE_PHASE::OR_WE_SINGLE_PHASE(void)
{
}

//Voltage
float OR_WE_SINGLE_PHASE::getVoltage()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterVoltage, 2);

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
float OR_WE_SINGLE_PHASE::getFrequency()
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
    result = getModbusFloat(data);
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
    result = getModbusFloat(data);
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
    result = getModbusFloat(data);
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
    result = getModbusFloat(data);
  }
  return result;
}

//Power Factor
float OR_WE_SINGLE_PHASE::getPowerFactor()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterPowerFactor, 2);

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
float OR_WE_SINGLE_PHASE::getTotalCounterActivePower()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalActivePower, 2);

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

float OR_WE_SINGLE_PHASE::getTotalCounterReactivePower()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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

uint16_t OR_WE_SINGLE_PHASE::getBusBaud()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterBusBaud, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

uint16_t OR_WE_SINGLE_PHASE::getLcdState()
{
  uint16_t result = 0;

  _result = _node.readHoldingRegisters(RegisterLcdState, 1);

  // do something with data if read is successful
  if (_result == _node.ku8MBSuccess)
  {
    result = _node.getResponseBuffer(0);
  }
  return result;
}

//------------------------------------------------------------------------------
OR_WE_SINGLE_PHASE_TARIF::OR_WE_SINGLE_PHASE_TARIF(void)
{
}

float OR_WE_SINGLE_PHASE_TARIF::getWeekdayTarif()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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

float OR_WE_SINGLE_PHASE_TARIF::getTotalWeekendTarif()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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

float OR_WE_SINGLE_PHASE_TARIF::getHolidayTarif()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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

float OR_WE_SINGLE_PHASE_TARIF::getHoliday()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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

float OR_WE_SINGLE_PHASE_TARIF::getDateTime()
{
  uint8_t j;
  uint16_t data[2];
  float result = -1;

  _result = _node.readHoldingRegisters(RegisterTotalReactivePower, 2);

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
