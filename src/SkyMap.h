//created by Natan Lisowski
// github --> https://github.com/natnqweb
// email -> natanlisowski@gmail.com
/**
 * @author @b Natan @b Lisowski @github: @b @natnqweb   @email: @c pythonboardsbeta@gmail.com
 * 
 * */
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
/** 
 * @brief custom type definitions to represent units
 */
typedef float hrs, days, rads, degs, years, months;
/**
 * @brief SkyMap a class that contains all essential functions to perform astronomic calculations
 * 
 */
class SkyMap
{
public:
    /**
     * @brief Construct a new SkyMap object
     * when constructor is called without any input arguments you must provide all this information later in program
     * 
     * @param lattitude - default value:0, type: float, details: geographic coordinates
     * @param longitude - default value:0, type: float, details: geographic coordinates
     * @param declination - default value:0, type: float, details: Star coordinates 
     * @param right_ascension - default value:0, type: float, details: Star coordinates 
     * @param year - default value:0, type: float, details: datetime, current year
     * @param month - default value:0, type: float, details: datetime, current month
     * @param day - default value:0, type: float, details: datetime, current day
     * @param time - default value:0, type: float, details: datetime, current time utc.
     */
    SkyMap(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); //leave empty if you want to use real_time calculations or provide all data to calculate once and then you can also use update to calculate things in real_time
    /**
     * @brief function transfers your location deeper to program,
     * so your location is taken for further calculations
     * if your location is not constant you may want to provide it as an input for this function
     * 
     * @param lattitude - default value:0, type: float, details: geographic coordinates
     * @param longitude - default value:0, type: float, details: geographic coordinates
     * @return degs* return pointer to array where first argument is your lattitude and next is your longitude so it looks like this lat=*p; long=*(p+1)
     */
    degs *my_location(degs lattitude = 0, degs longitude = 0); //returns pointer to array where your location is stored or when provided data it can update your position
    /** @brief function:star_ra_dec
     * this is another way to feed data for calculations input star coordinates 
     * @param right_ascension - default value:0, type: float, details: Star coordinates 
     * @param declination - default value:0, type: float, details: Star coordinates 
    */
    float *star_ra_dec(hrs right_ascension = 0, degs declination = 0);
    /**
     * @brief function transforms current local time to UTC
     * 
     * @param hhh -  hour type:float
     * @param mmm - minute type:float
     * @param sss - second type:float
     * @param your_timezone_offset type:float
     * @return float returns UTC type: float
     */
    float Hh_mm_ss2UTC(float hhh, float mmm, float sss, float your_timezone_offset);
    /**
     * @brief if you want to perform realtime calculations you update time and date for calculations calling this function 
     * 
     * @param year - default value:0, type: float, details: datetime, current year
     * @param month - default value:0, type: float, details: datetime, current month
     * @param day - default value:0, type: float, details: datetime, current day
     * @param UTC - default value:0, type: float, details: datetime, current time utc.
     * @return float*  datetime[4]={year,month,day,utc}; returns pointer to frist value 
     */
    float *DateTime(years year = 0, months month = 0, days day = 0, hrs UTC = 0);
    /**
     * @brief Calculating the days from J2000 the reference date is J2000, which corresponds to 1200 hrs UT on Jan 1st 2000 AD
     * 
     * @param Y- year - default value:0, type: float, details: datetime, current year
     * @param M  month - default value:0, type: float, details: datetime, current month
     * @param D  day - default value:0, type: float, details: datetime, current day
     * @param TIME   - default value:0, type: float, details: datetime, current time utc.
     * @return days returns number of days since J2000 type:float
     */
    days J2000(years Y = 0, months M = 0, days D = 0, hrs TIME = 0);
    /**
     * @brief calculates Local_Sidereal_Time and stores it.:
     *  is a timekeeping system that astronomers use to locate celestial objects. Using sidereal time, it is possible to easily point a telescope to the proper coordinates in the night sky. In short, sidereal time is a "time scale that is based on Earth's rate of rotation measured relative to the fixed stars"
     * @param j2000 - to calculate LST we need to know how many days passed since J2000
     * @param time  - default value:0, type: float, details: datetime, current time utc.
     * @param longitude - default value:0, type: float, details: geographic coordinates
     * @return degs return local sidereal time
     */
    degs Local_Sidereal_Time(days j2000 = 0, hrs time = 0, degs longitude = 0);
    /**
     * @brief the hour angle is the angle between two planes: one containing Earth's axis and the zenith (the meridian plane), and the other containing Earth's axis and a given point of interest (the hour circle)
     * 
     * @param LST -local sidereal time
     * @param right_ascension 
     * @return degs 
     */
    degs Hour_Angle(degs LST = 0, hrs right_ascension = 0); //calculates hour_angle and stores it
    /**
     * @brief calculate az and alt , returns pointer to array where the az and alt is stored
     * 
     * @param hour_angle 
     * @param declination 
     * @param lattitude 
     * @return degs* 
     */
    degs *calculate_AZ_alt(degs hour_angle = 0, degs declination = 0, degs lattitude = 0);
    /**
     * @brief perform all necessary calculations and after this function is called you can use get_star_azimuth and get_star_altitude
     * it is called automatically when using update() or when all data is provided in constuctor
     * 
     */
    void Calculate_all();
    /**
     * @brief Get the star azimuth object works only if you provide all data at constructor or in update() function and if you previously used calculate_AZ_alt()
     * 
     * @return * degs 
     */
    degs get_star_Azimuth();
    /**
     * @brief Get the star Altitude object works only if you provide all data at constructor or in update() function and if you previously used calculate_AZ_alt()
     * 
     * @return degs 
     */
    degs get_star_Altitude();
    /**
     * @brief this function let you 
     * 
     * @param lattitude 
     * @param longitude 
     * @param declination 
     * @param right_ascension 
     * @param year 
     * @param month 
     * @param day 
     * @param time 
     */
    void update(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); //if you created empty constructor you can provide all data here then use get..() functions
    /**
     * @brief convert degrees to radians
     * 
     * @param Deg 
     * @return rads 
     */
    rads deg2rad(degs Deg);
    /**
     * @brief convert radians to degrees
     * 
     * @param Rad 
     * @return degs 
     */
    degs rad2deg(rads Rad);
    //check for star visibility  sometimes user wants to know only if it will be visible or not , function returns true if is visible false if it is not returns value when previously provided data to update function on in constructor what star you want to look at
    /**
     * @brief check star visibility at your location
     * 
     * @return true if star is visible
     * @return false if star is not visible
     */
    bool IsVisible();

private:
    bool isvisible = false;
    degs _MyLocation[2];
    float _star_ra_dec[2];
    degs _Star_ALT_AZ[2];
    float _DateTime[4];
    degs h2deg(hrs h);
    hrs deg2h(degs Deg);

    degs asind(rads rad);
    degs acosd(rads rad);
    /* angle from the vernal
    equinox measured along the equator. This angle
    is the right ascension */
    hrs _right_ascension;
    hrs _time;
    //geographic coordinates
    degs _lattitude, _longitude;
    /* The angular separation of a star from the equa-
    torial plane is not affected by the rotation of the
    Earth.This angle is called the declination */
    degs _declination;
    years _year;
    months _month;
    /*  the hour angle is the angle between two planes: one containing Earth's axis and the zenith (the meridian plane), and the other containing Earth's axis and a given point of interest (the hour circle) */
    degs _hourangle;
    /* is a timekeeping system that astronomers use to locate celestial objects. Using sidereal time, it is possible to easily point a telescope to the proper coordinates in the night sky. In short, sidereal time is a "time scale that is based on Earth's rate of rotation measured relative to the fixed stars" */
    degs _local_sidereal_time;
    /* is a timekeeping system that astronomers use to locate celestial objects. Using sidereal time, it is possible to easily point a telescope to the proper coordinates in the night sky. In short, sidereal time is a "time scale that is based on Earth's rate of rotation measured relative to the fixed stars" */
    degs _LST;
    days _day;
    days _j2000;
    degs _HA;
    float _JD;
    days newday = 0;
};

#endif