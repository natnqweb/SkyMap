#include <SkyMap.h>

// always convert right_ascension to SKYMAP_degs!
// here i provided los angeles latitude and longitude
// and we are going to observe sirius sirius Ra -6.768 - we need to convert to degrees therefore we multiply by 15
// sirius DEC -16.7424
// the day and time of observation is going to be 2021.09.04 at 20:12 utc_time
// North-positive South -negative
// East-positive West_negative
//  los angeles location -;;;;;;; Lat -34degress 3min 8 sec North ;;;;;;Long-118deg 14 min  37 sec WEST;;;;;;

// const double latitude = 34.06, longitude = -118.24358, declination = -16.7424, right_ascension = 6.768 * 15, year = 2021, month = 9, day = 4, time = 20.2;
// as you see for West direction value is negative;
// if you need you can use it like that if you are not sure
SKYMAP_degs latitude = 34.06;
SKYMAP_degs longitude = 118.24358; // degrees
SKYMAP_degs declination = -16.7424;
SKYMAP_degs right_ascension = 6.768 * 15;
SKYMAP_years year = 2021;
SKYMAP_months month = 9;
SKYMAP_days day = 4;
SKYMAP_hrs s_time = 20.2;
enum Directions : int8_t
{
    N = 1,
    S = -1,
    E = 1,
    W = -1
};

SKYMAP_skymap_t skymap;
void setup()
{
    SKYMAP_init(&skymap);

    SKYMAP_update(&skymap, latitude * N, longitude * W, declination, right_ascension, year, month, day, s_time);
    SKYMAP_search_result_t star_position = SKYMAP_observe_object(&skymap);

    Serial.begin(115200);
    Serial.println(star_position.altitude);
    Serial.println(star_position.azimuth);
}

void loop()
{
}