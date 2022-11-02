# SkyMap

Tool that let you calculate star azimuth altitude, in any given time and any given position
i provided some examples
in examples we observate sirius from los angeles
as you will see in examples under you can gather some interesting data as for example hour angle or days from j2000 or local sidereal time and even you can calculate UTC for your timezone

# Install tutorial here

<https://www.ardu-badge.com/SkyMap>

# constructor example observation object-Sirius - observation location los angeles ----Lat 34deg 3min 8 sec North----Long 118deg 14 min  37 sec WEST---- observation time 20:12UTC date: 4.september.2021

```C++
    #include <SkyMap.h>
    degs lattitude = 34.06;
    degs longitude = 118.24358;
    degs declination = -16.7424;
    degs right_ascension = 6.768 * 15;
    years year = 2021;
    months month = 9;
    days day = 4;
    hrs s_time = 20.2;
    enum Directions : int8_t
    {
    N = 1,
    S = -1,
    E = 1,
    W = -1
    };


    SkyMap star(lattitude *N, longitude *W, declination, right_ascension, year, month, day, s_time);
```

# Step by Step example without creating new SkyMap object 

```C++
    #include <SkyMap.h>
    // data you must provide
    double year, month, day, hour, minute, second; //date and time can be taken from rtc
    double local_timezone_offset;
    double Time_utc;             //we will convert it from your time +offset
    double lattitude, longitude; //your lat and long can be taken from gps or hardcoded
    double RA, dec;              // can be taken from internet just look for star you are interested in
    double j2000;                //days since jan 2000  - to be calculated
    double Local_sidereal_time;  //to be calculated
    double Hour_angle;           // to be calculated
    double *p;                   // pointer to results
    double Az;                   //finally Azimuth of star and altitude
    double Alt;

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
        Time_utc = Skymap.Hh_mm_ss2UTC(hour, minute, second, local_timezone_offset); //converting to UTC
        j2000 = Skymap.J2000(year, month, day, Time_utc);
        Local_sidereal_time = Skymap.Local_Sidereal_Time(j2000, Time_utc, longitude);
        Hour_angle = Skymap.Hour_Angle(Local_sidereal_time, RA);
        SearchResult result = Skymap.calculate_AZ_alt(Hour_angle, dec, lattitude);
        Az = result.GetAzimuth();
        Alt = result.GetAltitude();
    }
    void loop()
    {
        Serial.print("Azimuth: ");
        Serial.println(Az);
        Serial.print("Altitude: ");
        Serial.println(Alt);
        delay(3000);
    }
```
