//created by Natan Lisowski
// github --> https://github.com/natnqweb
// email -> natanlisowski@gmail.com
//this library is powerful tool created by me to calculate star position of any star
//if has given RA and DEC
// by simply providing a data from gps and RTC you can calculate
//star position in any time
// i created this tool to use it in my StarTracking device
// actual speed of calculations measured in UNO R3 is 1400 [us] [micro seconds]
//this should work on any board im using only standard math library

#ifndef SKY_MAP_H
#define SKY_MAP_H
#include <math.h>
#define DEBUG false
#ifdef DEBUG
#if DEBUG == true
#define START_DEBUG(x) Serial.begin(x)
#define LOG(y) Serial.println(y)
#else
#define START_DEBUG(x)
#define LOG(y)
#endif
#else
#define START_DEBUG(x)
#define LOG(y)
#endif

typedef float hrs, days, rads, degs, years, months;

class SkyMap
{
public:
    SkyMap(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); //leave empty if you want to use real_time calculations or provide all data to calculate once and then you can also use update to calculate things in real_time
    degs *my_location(degs lattitude = 0, degs longitude = 0);                                                                                                   //returns pointer to array where your location is stored or when provided data it can update your position
    float *star_ra_dec(hrs right_ascension = 0, degs declination = 0);
    float Hh_mm_ss2UTC(float hhh, float mmm, float sss, float your_timezone_offset); //calculate utc from your local time
    float *DateTime(years year = 0, months month = 0, days day = 0, hrs UTC = 0);
    days J2000(years Y = 0, months M = 0, days D = 0, hrs TIME = 0);                       //Calculating the days from J2000 the reference date is J2000, which corresponds to 1200 hrs UT on Jan 1st 2000 AD
    degs Local_Sidereal_Time(days j2000 = 0, hrs time = 0, degs longitude = 0);            //calculates Local_Sidereal_Time and stores it
    degs Hour_Angle(degs LST = 0, hrs right_ascension = 0);                                //calculates hour_angle and stores it
    degs *calculate_AZ_alt(degs hour_angle = 0, degs declination = 0, degs lattitude = 0); //calculate az and alt , returns pointer to array where the az and alt is stored
    void Calculate_all();                                                                  //this function is available only if you provide all data at constructor! returns true on success false on failure! indicating that you probably didn't provided all data at construction
    degs get_star_Azymuth();                                                               //works only if you provide all data at constructor or in update() function and if you previously used calculate_AZ_alt()

    degs get_star_Altitude(); //works only if you provide all data at constructor or in update() function and if you previously used calculate_AZ_alt()

    void update(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); //if you created empty constructor you can provide all data here then use get..() functions
    rads deg2rad(degs Deg);
    degs rad2deg(rads Rad);
	//check for star visibility  sometimes user wants to know only if it will be visible or not , function returns true if is visible false if it is not returns value when previously provided data to update function on in constructor what star you want to look at
	bool IsVisible();
private:
	bool isvisible=false;
    degs _MyLocation[2];
    float _star_ra_dec[2];
    degs _Star_ALT_AZ[2];
    float _DateTime[4];
    degs h2deg(hrs h);
    hrs deg2h(degs Deg);

    degs asind(rads rad);
    degs acosd(rads rad);
    hrs _right_ascension, _time;
    degs _lattitude, _longitude, _declination;
    years _year;
    months _month;
    degs _hourangle, _local_sidereal_time, _LST;
    days _day;
    days _j2000;
    degs _HA;
    float _JD;
	days newday=0;
};

#endif