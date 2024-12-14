#include <SkyMap.h>
// data you must provide
double year, month, day, hour, minute, second; // date and time can be taken from rtc
double local_timezone_offset;
double Time_utc;             // we will convert it from your time +offset
double lattitude, longitude; // your lat and long can be taken from gps or hardcoded
double RA, dec;              // can be taken from internet just look for star you are interested in
double j2000;                // SKYMAP_days since jan 2000  - to be calculated
double Local_sidereal_time;  // to be calculated
double Hour_angle;           // to be calculated
double Az;                   // finally Azimuth of star and altitude
double Alt;

void setup()
{

    Serial.begin(9600);

    // date 2021-09-04 time 20:30:00-los angeles time not UTC!, observation object Sirius
    year = 2021;
    month = 9;
    day = 4;
    hour = 20;
    minute = 30;
    second = 0;
    local_timezone_offset = -7;                                                  // offset for los angeles
    SKYMAP_date_time_values_t dt;
    dt.day = day;
    dt.month = month;
    dt.year = year;
    Time_utc = SKYMAP_hh_mm_ss2UTC(&dt, hour, minute, second, local_timezone_offset); // converting to UTC

    lattitude = 34.06;                                                           // los angeles
    longitude = -118.24358;                                                      // los angeles
    RA = 101.52;                                                                 // sirius
    dec = -16.7424;                                                              // sirius
    j2000 = SKYMAP_j2000(&dt);
    Local_sidereal_time = SKYMAP_local_sidereal_time(j2000, Time_utc, longitude);
    Hour_angle = SKYMAP_hour_angle(Local_sidereal_time, RA);
    SKYMAP_search_result_t result = SKYMAP_search_for_object(Hour_angle, dec, lattitude);
    Az = result.azimuth;
    Alt = result.altitude;
}
void loop()
{
    Serial.print("Azimuth: ");
    Serial.println(Az);
    Serial.print("Altitude: ");
    Serial.println(Alt);
    delay(3000);
}