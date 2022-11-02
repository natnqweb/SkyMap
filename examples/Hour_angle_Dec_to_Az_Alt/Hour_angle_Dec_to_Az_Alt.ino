#include <SkyMap.h>
double Hour_angle = 54.382617, Declination = 36.466667; // if you calculated Hour Angle by your own you can go straight to transision from HA DEC to ALT AZ;
double your_lattitude = 52.5;
SearchResult result;
double Az;
double Alt;
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    result = Skymap.calculate_AZ_alt(Hour_angle, Declination, your_lattitude);
    Az = result.GetAzimuth();
    Alt = result.GetAltitude();
    Serial.print("Azimuth: ");
    Serial.println(Az);
    Serial.print("Altitude: ");
    Serial.println(Alt);
    delay(3000);
}