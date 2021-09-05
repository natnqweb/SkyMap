#include <SkyMap.h>
float Hour_angle = 54.382617, Declination = 36.466667; // if you calculated Hour Angle by your own you can go straight to transision from HA DEC to ALT AZ;
float your_lattitude = 52.5;
float *p;
float Az;
float Alt;
SkyMap sm;
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    p = sm.calculate_AZ_alt(Hour_angle, Declination, your_lattitude);
    Az = *p;
    Alt = *(p + 1);
    Serial.print("Azymuth: ");
    Serial.println(Az);
    Serial.print("Altitude: ");
    Serial.println(Alt);
    delay(3000);
}