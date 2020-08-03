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

//Voltage
float OR_WE::getVoltageL1()
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

float OR_WE::getVoltageL2()
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

float OR_WE::getVoltageL3()
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
float OR_WE::getFrequency()
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
float OR_WE::getCurrentL1()
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

float OR_WE::getCurrentL2()
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

float OR_WE::getCurrentL3()
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
float OR_WE::getActivePowerTotal()
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

float OR_WE::getActivePowerL1()
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

float OR_WE::getActivePowerL2()
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

float OR_WE::getActivePowerL3()
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
float OR_WE::getReactivePowerTotal()
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

float OR_WE::getReactivePowerL1()
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

float OR_WE::getReactivePowerL2()
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
float OR_WE::getReactivePowerL3()
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
float OR_WE::getApparentPowerTotal()
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
float OR_WE::getApparentPowerL1()
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
float OR_WE::getApparentPowerL2()
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
float OR_WE::getApparentPowerL3()
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
float OR_WE::getPowerFactorTotal()
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
float OR_WE::getPowerFactorL1()
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
float OR_WE::getPowerFactorL2()
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
float OR_WE::getPowerFactorL3()
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
float OR_WE::getTotalCounterActivePowerTotal()
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
float OR_WE::getTotalCounterActivePowerL1()
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
float OR_WE::getTotalCounterActivePowerL2()
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
float OR_WE::getTotalCounterActivePowerL3()
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

float OR_WE::getTotalCounterReactivePowerTotal()
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
float OR_WE::getTotalCounterReactivePowerL1()
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
float OR_WE::getTotalCounterReactivePowerL2()
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
float OR_WE::getTotalCounterReactivePowerL3()
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
float OR_WE::getImportCounterActivePowerTotal()
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
float OR_WE::getImportCounterActivePowerL1()
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
float OR_WE::getImportCounterActivePowerL2()
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
float OR_WE::getImportCounterActivePowerL3()
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

float OR_WE::getImportCounterReactivePowerTotal()
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
float OR_WE::getImportCounterReactivePowerL1()
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
float OR_WE::getImportCounterReactivePowerL2()
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
float OR_WE::getImportCounterReactivePowerL3()
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
float OR_WE::getExportCounterActivePowerTotal()
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
float OR_WE::getExportCounterActivePowerL1()
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
float OR_WE::getExportCounterActivePowerL2()
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

float OR_WE::getExportCounterActivePowerL3()
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

float OR_WE::getExportCounterReactivePowerTotal()
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
float OR_WE::getExportCounterReactivePowerL1()
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
float OR_WE::getExportCounterReactivePowerL2()
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

float OR_WE::getExportCounterReactivePowerL3()
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
uint32_t OR_WE::getSerialNo()
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

uint16_t OR_WE::getMeterId()
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

uint16_t OR_WE::getBusBaud()
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

float OR_WE::getSoftwareVersion()
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

float OR_WE::getHardwareVersion()
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

uint16_t OR_WE::getCountRate()
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

float OR_WE::getS0Rate()
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

uint16_t OR_WE::getA3()
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

uint16_t OR_WE::getCycleTime()
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

uint16_t OR_WE::getCrc()
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

uint16_t OR_WE::getCombinedCode()
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
  union u_data {
    byte b[4];
    uint16_t data[2];
  float result = -1;

  } source;

  union u_tag {
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
  union u_data {
    byte b[4];
    uint16_t data[2];
  float result = -1;

  } source;

  union u_tag {
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