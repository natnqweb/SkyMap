#include <SkyMap.h>

double Hour_angle;
double local_sidereal_time = 0; //place here your lst
double right_ascension = 0;     //here star RA;
SkyMap sm;
void setup()
{
    Serial.begin(9600);

    Hour_angle = sm.Hour_Angle(local_sidereal_time, right_ascension);
}
void loop()
{

    Serial.print("Hour Angle: ");
    Serial.println(Hour_angle);

    delay(3000);
}