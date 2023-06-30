#include <Arduino.h>
#include <PS2X_lib.h>

#define PS2_DAT 12
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_CLK 14
#define pressures false
#define rumble false

PS2X ps2x = PS2X();

void setup_controller()
{
  Serial.println("Connecting to PS2 controller...");

  int err = -1;
  while (err != 0)
  {
    delay(1000);
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.println("Trying...");
  }
}