#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define OSICILLATOR_FREQUENCY 27000000
#define PWM_FREQUENCY 60
#define I2C_COM_CLOCK 400000

#define MAX_PWM_VAL 4095

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

void control_moving_motors(int motL1, int motL2, int motR1, int motR2, int nJoyX, int nJoyY)
{
  // Based on IgorF2's Arduino Bot: https://www.instructables.com/Arduino-Robot-With-PS2-Controller-PlayStation-2-Jo/

  nJoyX = map(nJoyX, 0, 255, -1023, 1023);
  nJoyY = map(nJoyY, 0, 255, 1023, -1023);

  int num = 1;

  if (nJoyY < 0)
  {
    nJoyY = -nJoyY;
    nJoyX = -nJoyX;
    num = -num;
  }

  double nMotL = (nJoyX >= 0) ? 1023.0 : (1023.0 + nJoyX);
  double nMotR = (nJoyX >= 0) ? (1023.0 - nJoyX) : 1023.0;

  nMotL = nMotL * nJoyY / 1023.0;
  nMotR = nMotR * nJoyY / 1023.0;

  double fPivScale = 1.0 - abs(nJoyY) / 1023.0;

  nMotL = (1.0 - fPivScale) * nMotL + fPivScale * (+nJoyX);
  nMotR = (1.0 - fPivScale) * nMotR + fPivScale * (-nJoyX);

  Serial.print(nMotL);
  Serial.print(" ");
  Serial.print(nMotR);
  Serial.println("");

  control_motor(motL1, motL2, nMotL * num);
  control_motor(motR1, motR2, nMotR * num);
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