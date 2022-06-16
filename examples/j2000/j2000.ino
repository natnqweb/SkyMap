#include <SkyMap.h>

void setup()
{
    Serial.begin(115200);
    float hour = 12, minute = 20, second = 12; // 12:20:12
    float localtimeoffset = 2;                 //+2
    float Y = 2021, M = 9, D = 4;              // 2021.09.04 , 2021,september,4
    float UTC = Skymap.Hh_mm_ss2UTC(hour, minute, second, localtimeoffset);

    float J = Skymap.J2000(Y, M, D, UTC);
    Serial.print("time UTC:");
    Serial.println(UTC);
    Serial.print("days since January 2000:");
    Serial.println(J);
}
void loop()
{
}