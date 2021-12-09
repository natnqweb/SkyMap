#include <SkyMap.h>
// data you must provide
float year, month, day, hour, minute, second; //date and time can be taken from rtc
float local_timezone_offset;
float Time_utc;             //we will convert it from your time +offset
float lattitude, longitude; //your lat and long can be taken from gps or hardcoded
float RA, dec;              // can be taken from internet just look for star you are interested in
float j2000;                //days since jan 2000  - to be calculated
float Local_sidereal_time;  //to be calculated
float Hour_angle;           // to be calculated
float *p;                   // pointer to results
float Az;                   //finally Azimuth of star and altitude
float Alt;
SkyMap sm;

void setup()
{

    Serial.begin(9600);

    //date 2021-09-04 time 20:30:00-los angeles time not UTC!, observation object Sirius
    year = 2021;
    month = 9;
    day = 4;
    hour = 20;
    minute = 30;
    second = 0;
    local_timezone_offset = -7;                                               //offset for los angeles
    lattitude = 34.06;                                                       //los angeles
    longitude = -118.24358;                                                  //los angeles
    RA = 101.52;                                                             //sirius
    dec = -16.7424;                                                          //sirius
    Time_utc = sm.Hh_mm_ss2UTC(hour, minute, second, local_timezone_offset); //converting to UTC
    j2000 = sm.J2000(year, month, day, Time_utc);
    Local_sidereal_time = sm.Local_Sidereal_Time(j2000, Time_utc, longitude);
    Hour_angle = sm.Hour_Angle(Local_sidereal_time, RA);
    p = sm.calculate_AZ_alt(Hour_angle, dec, lattitude);
    Az = *p;
    Alt = *(p + 1);
}
void loop()
{
    Serial.print("Azimuth: ");
    Serial.println(Az);
    Serial.print("Altitude: ");
    Serial.println(Alt);
    delay(3000);
}