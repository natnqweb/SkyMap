#include <SkyMap.h>

void setup()
{
    Serial.begin(115200);
    double hour = 12, minute = 20, second = 12; // 12:20:12
    double localtimeoffset = 2;                 //+2        
    SKYMAP_date_time_values_t dt; // 2021.09.04 , 2021,september,4
    dt.year = 2021;
    dt.month = 9;
    dt.day = 4;
    double UTC = SKYMAP_hh_mm_ss2UTC(&dt, hour, minute, second, localtimeoffset);
    double J = SKYMAP_j2000(&dt);

    Serial.print("time UTC:");
    Serial.println(UTC);
    Serial.print("SKYMAP_days since January 2000:");
    Serial.println(J);
}
void loop()
{
}