#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

#include <chrono>
#include <cstdint>
#include <ctime>

class RealTimeClock {
public:
  enum RTCReg { RTC_SEC, RTC_MIN, RTC_HOUR, RTC_DLOW, RTC_DHIGH };

private:
  RTCReg active_reg;
  uint8_t seconds : 6;
  uint8_t minutes : 6;
  uint8_t hours : 5;
  uint8_t day_low;
  uint8_t day_high;

  void set_active_reg(RTCReg value) { active_reg = value; }

  /*
  ** Members for the time counter
  */
  clock_t clock_now;
  clock_t clock_last;
  float elapsed_time;

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &active_reg;
    ar &seconds;
    ar &minutes;
    ar &hours;
    ar &day_low;
    ar &day_high;
  }

public:
  RealTimeClock(void)
      : active_reg(RTC_SEC), seconds(0), minutes(0), hours(0), day_low(0),
        day_high(0), elapsed_time(0.0f) {
    clock_now = clock();
    clock_last = clock_now;
  }

  uint8_t get_seconds() const { return seconds; }
  uint8_t get_minutes() const { return minutes; }
  uint8_t get_hours() const { return hours; }
  uint8_t get_day_low() const { return day_low; }
  uint8_t get_day_high() const { return day_high & 0x1; }
  uint8_t get_halt() const { return ((day_high >> 6) & 0x1); }
  uint8_t get_carry() const { return ((day_high >> 7) & 0x1); }

  void set_seconds(uint8_t value) { seconds = value & 0x3F; }
  void set_minutes(uint8_t value) { minutes = value & 0x3F; }
  void set_hours(uint8_t value) { hours = value & 0x1F; }
  void set_day_low(uint8_t value) { day_low = value; }
  void set_day_high(uint8_t value) {
    day_high = (day_high & 0xC0) | (value & 0x1);
  }
  void set_halt(uint8_t value) {
    day_high = (day_high & 0x81) | ((value & 0x1) << 6);
  }
  void set_carry(uint8_t value) {
    day_high = (day_high & 0x41) | ((value & 0x1) << 7);
  }

  void reset() {
    active_reg = RTC_SEC;
    seconds = 0;
    minutes = 0;
    hours = 0;
    day_low = 0;
    day_high = 0;

    clock_now = clock();
    clock_last = clock_now;
    elapsed_time = 0.0f;
  }

  void switch_reg(uint8_t value) {
    RTCReg new_reg;

    refresh();
    switch (value) {
    case 0x8:
      new_reg = RTC_SEC;
      break;
    case 0x9:
      new_reg = RTC_MIN;
      break;
    case 0xA:
      new_reg = RTC_HOUR;
      break;
    case 0xB:
      new_reg = RTC_DLOW;
      break;
    case 0xC:
      new_reg = RTC_DHIGH;
    }
    set_active_reg(new_reg);
  }

  void set(uint8_t value) {
    refresh();
    switch (active_reg) {
    case RTC_SEC:
      seconds = value;
      break;
    case RTC_MIN:
      minutes = value;
      break;
    case RTC_HOUR:
      hours = value;
      break;
    case RTC_DLOW:
      day_low = value;
      break;
    case RTC_DHIGH:
      day_high = value;
      break;
    }
  }

  uint8_t get() const {
    switch (active_reg) {
    case RTC_SEC:
      return seconds;
    case RTC_MIN:
      return minutes;
    case RTC_HOUR:
      return hours;
    case RTC_DLOW:
      return day_low;
    case RTC_DHIGH:
      return day_high;
    default:
      break;
    }
    return 0;
  }

  /*
  ** This function should be called at LEAST before
  ** every access to time registers
  */
  void refresh() {
    int elapsed_sec = 0;

    if (get_halt())
      return;
    clock_now = clock();
    elapsed_time += clock_now - clock_last;
    elapsed_sec = static_cast<int>(elapsed_time / CLOCKS_PER_SEC);
    if (elapsed_sec > 0)
      elapsed_time = 0;
    while (elapsed_sec > 0) {
      tick();
      elapsed_sec--;
    }
    clock_last = clock_now;
  }

private:
  /*
  ** This function increments the clock counter by a second and
  ** sets the carry bit if an overflow happens
  **
  ** THIS FUNCTION SHOULD ONLY BE CALLED ONCE A SECOND
  */
  void tick() {
    if ((day_high & 0x40) == 1) // Is HALT flag set?
      return;

    if (seconds < 59) {
      seconds++;
    } else if (minutes < 59) {
      seconds = 0;
      minutes++;
    } else if (hours < 23) {
      seconds = 0;
      minutes = 0;
      hours++;
    } else {
      seconds = 0;
      minutes = 0;
      hours = 0;
      if (day_low == 0xFF) // Is the lower day counter about to overflow?
      {
        day_low = 0;
        if ((day_high & 0x1) ==
            1) {            // Is the high day counter about to overflow?
          day_high |= 0x80; // If so, set the carry flag
          day_high &= 0xFE; // Unset the day upper bit day counter
        } else {
          day_high |= 0x1; // Set the day upper bit day counter
        }
      } else
        day_low++;
    }
  }
};

#endif /* REALTIMECLOCK_H */
