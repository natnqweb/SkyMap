#include <SkyMap.h>
double Hour_angle = 54.382617, Declination = 36.466667; // if you calculated Hour Angle by your own you can go straight to transision from HA DEC to ALT AZ;
double your_latitude = 52.5;
SKYMAP_search_result_t result;

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    result = SKYMAP_search_for_object(Hour_angle, Declination, your_latitude);
    Serial.print("Azimuth: ");
    Serial.println(result.azimuth);
    Serial.print("Altitude: ");
    Serial.println(result.altitude);
    delay(3000);
}