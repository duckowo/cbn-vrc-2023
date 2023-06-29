#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <config.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void control_motor(int pin1, int pin2, int val)
{
  int val1 = 0, val2 = 0;

  if (val >= 0)
  {
    val1 = +val;
  }
  else
  {
    val2 = -val;
  }

  pwm.setPWM(pin1, val1, MAX_PWM_VAL - val1);
  pwm.setPWM(pin2, val2, MAX_PWM_VAL - val2);
}

void control_servo(int pin, int val)
{
  pwm.setPWM(pin, 0, val);
}

void control_moving_motors(int nJoyX, int nJoyY)
{
  // TODO: Add algorithm to calculate speed for each motors
}

void setup_pwm()
{
  Serial.println("Setting up PWM Controller...");

  pwm.begin();
  pwm.setOscillatorFrequency(OSICILLATOR_FREQUENCY);
  pwm.setPWMFreq(PWM_FREQUENCY);
  Wire.setClock(I2C_COM_CLOCK);

  control_motor(8, 9, 0);
  control_motor(10, 11, 0);
  control_motor(12, 13, 0);
  control_motor(14, 15, 0);
}