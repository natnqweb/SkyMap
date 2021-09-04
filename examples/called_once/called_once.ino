
#include "SkyMap.h"

//always convert right_ascension to degs!
//here i provided los angeles lattitude and longitude
//and we are going to observe sirius sirius Ra -6.768 - we need to convert to degrees therefore we multiply by 15
//sirius DEC -16.7424
//the day and time of observation is going to be 2021.09.04 at 20:12 utc_time
//North-positive South -negative
//East-positive West_negative
// los angeles location -;;;;;;; Lat -34degress 3min 8 sec North ;;;;;;Long-118deg 14 min  37 sec WEST;;;;;;

//const float lattitude = 34.06, longitude = -118.24358, declination = -16.7424, right_ascension = 6.768 * 15, year = 2021, month = 9, day = 4, time = 20.2;
//as you see for West direction value is negative;
//if you need you can use it like that if you are not sure
degs lattitude = 34.06;
degs longitude = 118.24358; // degrees
degs declination = -16.7424;
degs right_ascension = 6.768 * 15;
years year = 2021;
months month = 9;
days day = 4;
hrs time = 20.2;
enum Directions : int8_t
{
    N = 1,
    S = -1,
    E = 1,
    W = -1
};

SkyMap star(lattitude *N, longitude *W, declination, right_ascension, year, month, day, time);
//SkyMap star(lattitude, longitude, declination, right_ascension, year, month, day, time);
void setup()
{
    Serial.begin(115200);
    Serial.println(star.get_star_Altitude());
    Serial.println(star.get_star_Azymuth());
}
void loop()
{
}