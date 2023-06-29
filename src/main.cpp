#include <Arduino.h>
#include <motors.h>
#include <controller.h>
#include <config.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello world!!!");

  setup_pwm();
  setup_controller();

  Serial.println("Setup done!");
}

void loop()
{
  ps2x.read_gamepad(false, false);

  control_motor(BALL_COLLECTOR_P1, BALL_COLLECTOR_P2, ps2x.Button(PSB_L2) ? MAX_PWM_VAL : 0);
  control_motor(BALL_LAUNCHER_P1, BALL_LAUNCHER_P2, ps2x.Button(PSB_L1) ? MAX_PWM_VAL : 0);

  control_servo(BALL_CONTROLLER_1, ps2x.Button(PSB_R1) ? 440 : 0);
  control_servo(BALL_CONTROLLER_2, ps2x.Button(PSB_R1) ? 440 : 0);

  int joyX = ps2x.Analog(PSS_RX) - DEFAULT_X_VAL;
  int joyY = ps2x.Analog(PSS_RY) - DEFAULT_Y_VAL;

  control_moving_motors(joyX, joyY);

  delay(50);
}
