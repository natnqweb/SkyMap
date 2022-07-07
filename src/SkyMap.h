// created by Natan Lisowski
//  github --> https://github.com/natnqweb
//  email -> natanlisowski@gmail.com
/**
 * @author @b Natan @b Lisowski @github: @b @natnqweb   @email: @c pythonboardsbeta@gmail.com
 *
 * */
// this library is powerful tool created by me to calculate star position of any star
// if has given RA and DEC
//  by simply providing a data from gps and RTC you can calculate
// star position in any time
//  i created this tool to use it in my StarTracking device
//  actual speed of calculations measured in UNO R3 is 1400 [us] [micro seconds]
// this should work on any board im using only standard math library
#pragma once
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
 * @brief data structure for storing date and time values
 */
struct DateTimeValues
{
    years year;
    months month;
    days day;
    hrs time;
};
/**
 * @brief Structure for storing observer information
 *
 */
struct ObserverPosition
{
    degs lattitude;
    degs longitude;
};

/**
 * @brief interface that represents celestial body
 * @details
 *
 */
struct CelestialObject
{

    virtual hrs GetRA() = 0;
    virtual degs GetDec() = 0;
    virtual void SetRA(hrs) = 0;
    virtual void SetDec(degs) = 0;
    virtual ~CelestialObject() = default;
};
/**
 * @brief Structure to represent a star
 */
struct Star : CelestialObject
{
    hrs right_ascension;
    degs declination;

    Star(hrs RA, degs Dec) : right_ascension(RA), declination(Dec) {}
    Star() = default;
    ~Star() override = default;
    hrs GetRA() override
    {
        return right_ascension;
    }
    degs GetDec() override
    {
        return declination;
    }
    void SetRA(hrs RA) override
    {
        right_ascension = RA;
    }
    void SetDec(degs Dec) override
    {
        declination = Dec;
    }
};
/**
 * @brief Structure to represent a planet
 */
struct Planet : public Star
{
    Planet(hrs RA, degs Dec) : Star(RA, Dec) {}
    Planet() = default;
};
/**
 * @brief data structure for storing search result Azimuth and Altitude
 *
 */
struct SearchResult
{
    degs Azimuth;
    degs Altitude;
    // constructor
    SearchResult(degs Az, degs Alt) : Azimuth(Az), Altitude(Alt) {}
    SearchResult() = default;

    // setters and getters
    void SetAzimuth(degs Azimuth)
    {
        this->Azimuth = Azimuth;
    }
    void SetAltitude(degs Altitude)
    {
        this->Altitude = Altitude;
    }
    degs GetAzimuth()
    {
        return Azimuth;
    }
    degs GetAltitude()
    {
        return Altitude;
    }
};
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
     * @param ObserverPosition Observer position
     * @param DateTimeValues Date and time values
     * @param CelestialObject Celestial object
     */
    SkyMap::SkyMap(ObserverPosition observer, CelestialObject *celestialobject, DateTimeValues datetime);
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
    SkyMap(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); // leave empty if you want to use real_time calculations or provide all data to calculate once and then you can also use update to calculate things in real_time
    /**
     * @brief function transfers your location deeper to program,
     * so your location is taken for further calculations
     * if your location is not constant you may want to provide it as an input for this function
     *
     * @param lattitude -  type: float, details: geographic coordinates
     * @param longitude -  type: float, details: geographic coordinates
     * @return ObserverPosition return  your lattitude and longitude
     */
    ObserverPosition my_location(degs lattitude, degs longitude); // returns pointer to array where your location is stored or when provided data it can update your position
    /**
     * @brief function transfers your location deeper to program,
     * so your location is taken for further calculations
     * if your location is not constant you may want to provide it as an input for this function
     * @return ObserverPosition return  your lattitude and longitude
     */
    ObserverPosition my_location(); // returns pointer to array where your location is stored or when provided data it can update your position
    /** @brief function:star_ra_dec
     * this is another way to feed data for calculations input star coordinates
     * @param right_ascension - default value:0, type: float, details: Star coordinates
     * @param declination - default value:0, type: float, details: Star coordinates
     * @return returns Star coordinates
     */
    Star star_ra_dec(hrs right_ascension, degs declination);
    /** @brief function:star_ra_dec
     * @return returns Star coordinates
     */
    Star star_ra_dec();
    /** @brief function:CelebralObject_ra_dec
     * this is another way to feed data for calculations input star coordinates
     * @param celestial_object - default value:nullptr, type: CelestialObject(float,float), details: Star coordinates
     * @return returns Star coordinates in form of CelestialObject*
     */
    CelestialObject *celestial_object_ra_dec(CelestialObject *celestial_object);
    /** @brief function:CelebralObject_ra_dec
     * @return returns Star coordinates in form of CelestialObject*
     */
    CelestialObject *celestial_object_ra_dec();
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
     * @param year -  type: float, details: datetime, current year
     * @param month -  type: float, details: datetime, current month
     * @param day -  type: float, details: datetime, current day
     * @param UTC -  type: float, details: datetime, current time utc.
     * @return DateTimeValues
     */
    DateTimeValues DateTime(years year, months month, days day, hrs UTC);
    /**
     * @brief Datetimevalues getter
     * @return DateTimeValues
     */
    DateTimeValues DateTime();
    /**
     * @brief Calculating the days from J2000 the reference date is J2000, which corresponds to 1200 hrs UT on Jan 1st 2000 AD
     *
     * @param Y- year -  type: float, details: datetime, current year
     * @param M  month -  type: float, details: datetime, current month
     * @param D  day -  type: float, details: datetime, current day
     * @param TIME   -  type: float, details: datetime, current time utc.
     * @return days returns number of days since J2000 type:float
     */
    days J2000(years Y, months M, days D, hrs TIME);
    /**
     * @brief J2000 Getter
     * @return days returns number of days since J2000 type:float
     */
    days J2000();
    /**
     * @brief calculates Local_Sidereal_Time and stores it.:
     *  is a timekeeping system that astronomers use to locate celestial objects. Using sidereal time, it is possible to easily point a telescope to the proper coordinates in the night sky. In short, sidereal time is a "time scale that is based on Earth's rate of rotation measured relative to the fixed stars"
     * @param j2000 - to calculate LST we need to know how many days passed since J2000
     * @param time  - default value:0, type: float, details: datetime, current time utc.
     * @param longitude - default value:0, type: float, details: geographic coordinates
     * @return degs return local sidereal time
     */
    degs Local_Sidereal_Time(days j2000, hrs time, degs longitude);
    /**
     * @brief LST getter
     * @return degs return local sidereal time
     */
    degs Local_Sidereal_Time();
    /**
     * @brief the hour angle is the angle between two planes: one containing Earth's axis and the zenith (the meridian plane), and the other containing Earth's axis and a given point of interest (the hour circle)
     *
     * @param LST -local sidereal time
     * @param right_ascension
     * @return degs
     */
    degs Hour_Angle(degs LST, hrs right_ascension); // calculates hour_angle and stores it
    /**
     * @brief the hour angle is the angle between two planes: one containing Earth's axis and the zenith (the meridian plane), and the other containing Earth's axis and a given point of interest (the hour circle)
     * @return Hour angle in degs
     */
    degs Hour_Angle();
    /**
     * @brief calculate az and alt , returns pointer to array where the az and alt is stored
     *
     * @param hour_angle
     * @param declination
     * @param lattitude
     * @return SearchResult
     */
    SearchResult calculate_AZ_alt(degs hour_angle, degs declination, degs lattitude);
    /**
     * @brief calculate az and alt , returns pointer to array where the az and alt is stored
     * @return SearchResult
     */
    SearchResult calculate_AZ_alt();
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
    void update(degs lattitude = 0, degs longitude = 0, degs declination = 0, hrs right_ascension = 0, years year = 0, months month = 0, days day = 0, hrs time = 0); // if you created empty constructor you can provide all data here then use get..() functions
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
    // check for star visibility  sometimes user wants to know only if it will be visible or not , function returns true if is visible false if it is not returns value when previously provided data to update function on in constructor what star you want to look at
    /**
     * @brief check star visibility at your location
     *
     * @return true if star is visible
     * @return false if star is not visible
     */
    bool IsVisible();
    /**
     * @brief get star azimuth and altitude
     *
     * @return SearchResult
     */
    SearchResult get_star_search_result();
    /**
     * @brief function returns pointer to the celestial object
     *
     * @return CelestialObject*
     */
    CelestialObject *get_celestial_object();

private:
    bool isvisible = false;
    ObserverPosition _observer_position{};
    SearchResult _search_result{0, 0};
    Star _star{};
    degs h2deg(hrs h);
    hrs deg2h(degs Deg);

    degs asind(rads rad);
    degs acosd(rads rad);
    /* angle from the vernal
    equinox measured along the equator. This angle
    is the right ascension */
    hrs _right_ascension;
    hrs _time;
    // geographic coordinates
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
static SkyMap Skymap{};