# SkyMap
Tool that let you calculate star azymuth altitude, in any given time and any given position




# constructor example 
    #include <SkyMap.h>
    degs lattitude = 34.06;
    degs longitude = 118.24358;
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
     

