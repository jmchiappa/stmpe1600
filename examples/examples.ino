#include "stmpe.h"

STMPE expander;

// default i2c address is 0x42. Use a variant constructor to assign a different i2c address 
//STMPE expander(0x44);

// Use a non standard i2c output
// TwoWire MyWire( SCL2, SDA2);
// STMPE expander(&MyWire);

uint16_t cnt=0;

void setup(void) {
	Serial.begin(115200);
	expander.init();
	Serial.println(expander.readState());
	expander.swReset();
	expander.writeDirection(~(1<<11));
}

void loop(void) {
	expander.writeState(cnt++);
	delay(10);
}