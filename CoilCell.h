#ifndef COILCELL_H
#define COILCELL_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)

#define DRIVE_TIMER 8
#define DRIVE_BASE_FREQ 20000
#define CC_MAX_NUM 10

class CoilCell {
private:
  byte _IN1;
  byte _IN2;
  bool _state = 1;
  uint8_t _tnum = 0;

public:
  CoilCell(byte IN1, byte IN2);
  void Init();
  void Vibrate(bool smooth, uint8_t power_percent, uint16_t vib_speed_ms);
  void Buzz(uint16_t us_buzz);
  void Drive(bool direction, uint8_t power_percent);
  void Bounce(bool direction, uint8_t ms_duration);
  void Tone();
  void Slide();
  void Toggle(uint8_t power_percent);
};
#else
class CoilCell {
private:
  byte _IN1;
  byte _IN2;
  bool _state = 1;
  uint8_t _tnum = 0;

public:
  CoilCell(byte IN1, byte IN2);
  void Init();
  void Vibrate( uint16_t vib_speed_ms);
  void Buzz(uint16_t us_buzz);
  void Bounce(bool direction, uint8_t ms_duration);
  void Tone();
  void Slide();
  void Toggle();
};
#endif
#endif