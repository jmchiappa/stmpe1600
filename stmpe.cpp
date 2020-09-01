#include "stmpe.h"
/*
static const uint16_t PROGMEM VL_select[] = {
    VL6180_CE_TOP,
    VL6180_CE_BOTTOM,
    VL6180_CE_LEFT,
    VL6180_CE_RIGHT
};

static const uint16_t PROGMEM digit_sel[] = {
  0b0000011100000000, //LSB
  0b0000011010000000,
  0b0000010110000000,
  0b0000001110000000
};

static const unsigned char PROGMEM Segment_digit[] = {
  S_G,            // 0
  ~(S_E | S_F),   // 1
  S_C | S_F,      // 2
  S_B | S_C,      // 3
  S_A | S_B | S_D,// 4
  S_B | S_E,      // 5
  S_E,            // 6
  ~(S_D | S_E | S_F), // 7
  0,              // 8
  S_B,            // 9
  S_A,            // A
  S_D | S_E,      // B
  S_E | S_F | S_G, // C
  S_D | S_E,      // D
  S_E | S_F,      // E
  S_E | S_F | S_A, // F
  ~S_G,           // -
  0x7F,           // BLANK
};
*/


/** constructors 
*/

STMPE::STMPE(void) {
  InstanceWire = &Wire;
  address = I2C_ADDR;
}

STMPE::STMPE(TwoWire *wire) {
  InstanceWire = wire;
  address = I2C_ADDR;
}

STMPE::STMPE(uint8_t i2cAddr) {
  InstanceWire = &Wire;
  address = i2cAddr;
//  writeReg16Bit(0x14,(uint16_t)(~(1<<11)));
}

STMPE::STMPE(uint8_t i2cAddr, TwoWire *wire) {
  InstanceWire = wire;
  address = i2cAddr;
//  writeReg16Bit(0x14,(uint16_t)(~(1<<11)));
}

/**
  I2C access
**/

void STMPE::writeReg(uint8_t reg, uint8_t value)
{
  InstanceWire->beginTransmission(address);
  InstanceWire->write(reg & 0xff);         // reg low byte
  InstanceWire->write(value);
  last_status = InstanceWire->endTransmission();
}

// Writes a 16-bit register
void STMPE::writeReg16Bit(uint8_t reg, uint16_t value)
{
  InstanceWire->beginTransmission(address);
  InstanceWire->write(reg & 0xff);         // reg low byte
  InstanceWire->write(value & 0xff);         // value low byte
  InstanceWire->write((value >> 8) & 0xff);  // value high byte
  last_status = InstanceWire->endTransmission();
}

// Reads an 8-bit register
uint8_t STMPE::readReg(uint8_t reg)
{
  uint8_t value;

  InstanceWire->beginTransmission(address);
  InstanceWire->write(reg & 0xff);         // reg low byte
  last_status = InstanceWire->endTransmission();

  InstanceWire->requestFrom(address, (uint8_t)1);
  value = InstanceWire->read();

  return value;
}

// Reads a 16-bit register
uint16_t STMPE::readReg16Bit(uint8_t reg)
{
  uint16_t value;

  InstanceWire->beginTransmission(address);
  InstanceWire->write(reg & 0xff);         // reg low byte
  last_status = InstanceWire->endTransmission();

  InstanceWire->requestFrom(address, (uint8_t)2);
  value = (uint16_t)InstanceWire->read(); // value high byte
  value |= InstanceWire->read() << 8;               // value low byte

  return value;
}

void STMPE::init(void) {
  InstanceWire->begin();
}

void STMPE::writeDirection(uint16_t direction) {
  writeReg16Bit(GPDR, direction);
}

void STMPE::writeState(uint16_t value) {
  writeReg16Bit(GPSR, value);
}

uint16_t STMPE::readState(void) {
  return readReg16Bit(GPMR);
}

void STMPE::swReset(void) {
  writeReg(SYS_CTRL, 0x80);
  delay(1);
}

uint8_t STMPE::getLastStatus(void) {
  return last_status;
}

/*
void dispVal(uint16_t val) {
  uint8_t tmp;
  for(uint8_t d=0;d<4;d++){
    tmp = val - (val/10)*10;
    Serial.println(tmp);
    if( (d>0) && (val==0) )
      writeReg16Bit(0x12,digit_sel[d] | Segment_digit[S_BLANK] );
    else
      writeReg16Bit(0x12,digit_sel[d] | ( Segment_digit[tmp] & 0x7F) );
    delay(2);
    val /= 10;
  }
}

void select_VL(uint8_t sensor_nb) {
  if(sensor_nb<4){
    uint16_t tmp =readReg16Bit(0x10);
    tmp |= VL_select[sensor_nb];
    writeReg16Bit(0x12,tmp);
  }
}

void deselect_VL(uint8_t sensor_nb) {
  if(sensor_nb<4){
    uint16_t tmp =readReg16Bit(0x10);
    tmp &= (~VL_select[sensor_nb]);
    writeReg16Bit(0x12,tmp);
  }
}
*/