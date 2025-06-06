#include "CoilCell.h"

#if defined(ARDUINO_ARCH_ESP32)
hw_timer_t* timer = NULL;
uint16_t _ctimer[CC_MAX_NUM] = { 0 };
uint8_t cc_num = 0;

void IRAM_ATTR onTimer() {
  for (uint16_t cc = 0; cc < cc_num; cc++) {
    _ctimer[cc]++;
  }
}
CoilCell::CoilCell(byte IN1, byte IN2) {
  _IN1 = IN1;
  _IN2 = IN2;
}

void CoilCell::Init() {
  pinMode(_IN1, OUTPUT);
  ledcAttach(_IN1, DRIVE_BASE_FREQ, DRIVE_TIMER);
  pinMode(_IN2, OUTPUT);
  ledcAttach(_IN2, DRIVE_BASE_FREQ, DRIVE_TIMER);


  _tnum = cc_num;
  if (cc_num == 0) {
    timer = timerBegin(1000000);           /*Set timer frequency to 1Mhz*/
    timerAttachInterrupt(timer, &onTimer); /*Attach interrupt*/
    timerAlarm(timer, 1000, true, 0);      /*Set alarm to trigger every ms with auto-reload*/
  } else {
    /*Skip*/
  }
  if (cc_num < CC_MAX_NUM) {
    cc_num++;
  } else {
    /*Skip*/
  }
  Serial.print(">> CoilCell");
  Serial.print(cc_num);
  Serial.println(": Ready to Use");
}

void CoilCell::Vibrate(bool smooth, uint8_t power_percent, uint16_t vib_speed_ms) {
  /*Flip the polarity of the actuator or reverse a motor every 'vib_speed_ms' at the duty cycle 'power_percent'*/
  /*Setting 'smooth' to 1, smooths out the motion (ideal for slow motions less than 2Hz)*/

  uint16_t dc_value = (power_percent * 255U) / 100U;
  uint16_t period = vib_speed_ms;
  uint16_t period_halfval = period / 2U;

  if (_ctimer[_tnum] >= period) {
    _state = !_state;
    _ctimer[_tnum] = 0U;
  }

  if (smooth == 0) {
    if (_state) {
      ledcWrite(_IN1, 0U);
      ledcWrite(_IN2, dc_value);
    } else {
      ledcWrite(_IN2, 0U);
      ledcWrite(_IN1, dc_value);
    }
  } else {
    /*PWM Mode*/
    if (_state) {
      if (_ctimer[_tnum] <= period_halfval) {
        /*Period is smaller than 75%*/
        dc_value = (((_ctimer[_tnum]) * 128U) / (period_halfval)) + 128U;
      } else {
        /*Period is greater than 75%*/
        dc_value = 383U - (((_ctimer[_tnum]) * 255U) / (period));
      }
    } else {
      if (_ctimer[_tnum] <= period_halfval) {
        /*Period is smaller than 25%*/
        dc_value = (128U - (((_ctimer[_tnum]) * 128U) / (period_halfval)));
      } else {
        dc_value = ((((_ctimer[_tnum]) * 255U) / (period)) - 128U);
      }
    }
    if (dc_value >= 255U) {
      dc_value = 255U;
    } else {
      /*Skip*/
    }
    ledcWrite(_IN1, dc_value);
    ledcWrite(_IN2, (255U - dc_value));
  }
}

void CoilCell::Buzz(uint16_t us_buzz) {
  /*Play a buzzing sound - 'us_buzz' determines the frequency (ideal 40-120us)*/
  delayMicroseconds(us_buzz);
  _state = !_state;
  if (_state) {
    ledcWrite(_IN1, 0U);
    ledcWrite(_IN2, 255U);
  } else {
    ledcWrite(_IN2, 0U);
    ledcWrite(_IN1, 255U);
  }
}

void CoilCell::Drive(bool direction, uint8_t power_percent) {
  /*For motors - set the driving 'direction' (forward/reverse) and speed duty cycle 'power_percent'*/
  /*For coils - set the polarity 'direction' (north/south) and magnetic strength duty cycle 'power_percent'*/
  uint8_t dc_value = (power_percent * 255) / 100U;
  if (direction) {
    ledcWrite(_IN1, 0U);
    ledcWrite(_IN2, dc_value);
  } else {
    ledcWrite(_IN2, 0U);
    ledcWrite(_IN1, dc_value);
  }
}

void CoilCell::Bounce(bool direction, uint8_t ms_duration) {
  /*Crteate a short Bounce for 'ms_duration'*/
  if (direction) {
    ledcWrite(_IN1, 0U);
    ledcWrite(_IN2, 255U);
    delay(ms_duration);
    ledcWrite(_IN2, 0U);
    ledcWrite(_IN1, 255U);
  } else {
    ledcWrite(_IN2, 0U);
    ledcWrite(_IN1, 255U);
    delay(ms_duration);
    ledcWrite(_IN1, 0U);
    ledcWrite(_IN2, 255U);
  }
}

void CoilCell::Tone() {
  /*Play Tone*/
  for (uint16_t d = 0; d < 1000; d++) {
    Buzz(100);  // Continuous Vibrate with updated parameters
  }

  for (uint16_t d = 0; d < 3000; d++) {
    uint8_t tone_freq = 30U + (d / 50);
    Buzz(tone_freq);  // Continuous Vibrate with updated parameters
  }
}

void CoilCell::Toggle(uint8_t power_percent) {
  /*Toogle the polarity of the coil or the directions of a motor at the desired duty cycle 'power_percent'*/
  uint8_t dc_value = (power_percent * 255) / 100U;
  _state = !_state;
  if (_state) {
    ledcWrite(_IN1, 0U);
    ledcWrite(_IN2, dc_value);
  } else {
    ledcWrite(_IN2, 0U);
    ledcWrite(_IN1, dc_value);
  }
}
#else

CoilCell::CoilCell(byte IN1, byte IN2) {
  _IN1 = IN1;
  _IN2 = IN2;
}

void CoilCell::Init() {
  pinMode(_IN1, OUTPUT);
  pinMode(_IN2, OUTPUT);
}

void CoilCell::Vibrate(uint16_t vib_speed_ms) {
  /*Flip the polarity of the actuator or reverse a motor every 'vib_speed_ms'*/
  delay(vib_speed_ms);
  _state = !_state;
  if (_state) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
  } else {
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN1, HIGH);
  }
}

void CoilCell::Buzz(uint16_t us_buzz) {
  /*Play a buzzing sound - 'us_buzz' determines the frequency (ideal 40-120us)*/
  delayMicroseconds(us_buzz);
  _state = !_state;
  if (_state) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
  } else {
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN1, HIGH);
  }
}


void CoilCell::Bounce(bool direction, uint8_t ms_duration) {
  /*Crteate a short Bounce for 'ms_duration'*/
  if (direction) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
    delay(ms_duration);
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN1, HIGH);
  } else {
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN1, HIGH);
    delay(ms_duration);
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
  }
}

void CoilCell::Tone() {
  /*Play Tone*/
  for (uint16_t d = 0; d < 1000; d++) {
    Buzz(100);  // Continuous Vibrate with updated parameters
  }

  for (uint16_t d = 0; d < 3000; d++) {
    uint8_t tone_freq = 30U + (d / 50);
    Buzz(tone_freq);  // Continuous Vibrate with updated parameters
  }
}

void CoilCell::Toggle() {
  /*Toogle the polarity of the coil or the directions of a motor at full power*/
  _state = !_state;
  if (_state) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
  } else {
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN1, HIGH);
  }
}
#endif
