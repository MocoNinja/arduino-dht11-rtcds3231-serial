#include "sensor.h"
#include "clock.h"

SimpleDHT11 dht11;
uint8_t pinDHT11;

// Ojito! Si esto es local a la funcion va al stack -> al retornar ya no existe -> nada que mostrar
// Aqui es mas mejor, pero no es thread safe; que para lo que voy a hacer con esto no importa mucho...
char msg[128];

void start_sensor(uint8_t PIN)
{
    pinDHT11 = PIN;
}

Measurement read_sensor()
{
    Measurement measurement = {0};
    byte temperature = 0;
    byte humidity = 0;

    measurement.Unix_Timestamp_Local = rtc_get_local_unix();

    if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
    {
        measurement.Status = 0;
    } else {
        measurement.Status = 1;
        measurement.Temperature_Celsius = temperature;
        measurement.Humidity_Percentage = humidity;
    }

    return measurement;
}

char* parse_measurement(Measurement *measurement)
{
    const char *status_friendly_display = (measurement->Status)
        ? "OK"
        : "KO";
    sprintf(msg, "{\"Status\":\"%s\",\"Temperature_Celsius\":%d,\"Humidity_Percent\":%d,\"Unix_Local_Timestamp\":%lu}",
        status_friendly_display, measurement->Temperature_Celsius, measurement->Humidity_Percentage, measurement->Unix_Timestamp_Local); 
    return msg;
}
