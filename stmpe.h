#ifndef STMPE_h
#define STMPE_h

#include <Arduino.h>
#include <Wire.h>

/*
      d
      -
   c | | e
      -  <-- g
   b | | f
      - 
      a
*/

// segment is off when set to 1
/*
#define S_A (1<<0)
#define S_B (1<<1)
#define S_C (1<<2)
#define S_D (1<<3)
#define S_E (1<<4)
#define S_F (1<<5)
#define S_G (1<<6)

#define DIGIT1  (1<<7)
#define DIGIT2  (1<<8)
#define DIGIT3  (1<<9)
#define DIGIT4  (1<<10)

#define VL6180_CE_TOP     (1<<12)
#define VL6180_CE_BOTTOM  (1<<13)
#define VL6180_CE_LEFT    (1<<14)
#define VL6180_CE_RIGHT   (1<<15)

#define S_MINUS 16
#define S_BLANK 17

#define ALL_SEG_SEL 0x780
*/

#define I2C_ADDR  0x42

class STMPE
{
  public:
  	enum RegAddr {
  		SYS_CTRL = 0x03,// SYSTEM CONTROL
  		GPMR		=0x10,	// Read state
  		GPSR		=0x12,	// set state
  		GPDR		=0x14,	// pin direction (1=OUTPUT,0=INPUT)
  		GPPIR		=0x16		// input pin polarity inversion
  	};
  	STMPE(void);
  	STMPE(uint8_t i2cAddr);
  	STMPE(TwoWire *wire);
  	STMPE(uint8_t i2cAddr,TwoWire *wire);
  	void 			init(void);
  	void 			writeDirection(uint16_t direction);
  	void 			writeState(uint16_t value);
  	uint16_t 	readState(void);
  	void 			swReset(void);
  	uint8_t		getLastStatus(void);

  private:
  	//i2c routines
  	void writeReg(uint8_t reg, uint8_t value);
  	void writeReg16Bit(uint8_t reg, uint16_t value);
  	uint8_t readReg(uint8_t reg);
		uint16_t readReg16Bit(uint8_t reg);

  	// object's variables
		TwoWire *InstanceWire;
		uint8_t address;
		uint32_t last_status;
};

#endif
