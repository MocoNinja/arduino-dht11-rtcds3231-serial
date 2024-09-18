#include "clock.h"

#define BUFFER 4+1+2+1+2+1+2+1+2+1+2

RTC_DS3231 rtc;

char timestamp[BUFFER];

void start_clock()
{
  rtc.begin();
}

uint32_t rtc_get_local_unix()
{
  return rtc.now().unixtime();
}

char* rtc_get_local_iso()
{
  DateTime now = rtc.now();
  sprintf(timestamp, "%04i-%02i-%02iT%02i:%02i:%02i", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  return timestamp;
}
