## Library for reading ORNO WE Modbus Energy meters. ##

### SECTIONS: ###
#### 1. [INTRODUCTION](#introduction) ####
#### 2. [ModbusMaster](#modbusmaster) ####
---

### Introduction: ###
This library allows you reading ORNO WE energy meter(s) using:
- [x] Hardware Serial (<i>recommended option, smallest number of reads errors</i>) <b><i>or</i></b>
- [x] Software Serial (<i>[library for ESP8266](https://github.com/plerup/espsoftwareserial)</i>) <b><i>and</i></b>
- [x] ModbusMaster (<i>[library for Arduino](https://github.com/4-20ma/ModbusMaster)</i>)

you also need rs232<->rs485 converter:
- [x] with automatic flow direction control
- [x] *WITHOUT* automatic flow direction control


Default DeRe Pin is D6 (NodeMCU) - in the OR_WE.h file you can redefine the Pin for your needs.

---

### modbusmaster: ###
You need to change the value "ku8MaxBufferSize" inside the library to 100!
