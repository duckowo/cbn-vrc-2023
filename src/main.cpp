#include <Arduino.h>
#include <motors.h>
#include <controller.h>

#define MOT_L_P1 8
#define MOT_L_P2 9

#define MOT_R_P1 10
#define MOT_R_P2 11

#define BALL_LAUNCHER_P1 14
#define BALL_LAUNCHER_P2 15

#define BALL_COLLECTOR_P1 12
#define BALL_COLLECTOR_P2 13

#define BALL_CONTROLLER_1 6
#define BALL_CONTROLLER_2 7

void setup()
{
  Serial.begin(115200);

  setup_pwm();
  setup_controller();

  Serial.println("Setup done!");
}

void loop()
{
  ps2x.read_gamepad(false, false);

  control_motor(BALL_COLLECTOR_P1, BALL_COLLECTOR_P2, (ps2x.Button(PSB_L1) ? +MAX_PWM_VAL : (ps2x.Button(PSB_L2) ? -MAX_PWM_VAL : 0)));
  control_motor(BALL_LAUNCHER_P1, BALL_LAUNCHER_P2, (ps2x.Button(PSB_R1) ? MAX_PWM_VAL : 0));

  int joyX = ps2x.Analog(PSS_RX);
  int joyY = ps2x.Analog(PSS_RY);

  control_moving_motors(MOT_L_P1, MOT_L_P2, MOT_R_P1, MOT_R_P2, joyX, joyY);

  delay(50);
}
