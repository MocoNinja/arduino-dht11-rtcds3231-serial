#include <SimpleDHT.h>
struct Measurement
{
    byte        Temperature_Celsius;
    byte        Humidity_Percentage;
    byte        Status;
    uint32_t    Unix_Timestamp_Local;
};

void            start_sensor(uint8_t PIN);

Measurement     read_sensor();

char*           parse_measurement(Measurement* measurement);
