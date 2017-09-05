// Alexander Vaughan, av1045643
// av1045643@swccd.edu

#include <stdio.h>
#include <stdlib.h>

// probably need
#include <math.h>
#include <string.h>
/*  cplusplus.com
    ^ C library reference, has list of all includes
*/


/* PROJECT INFO */
// take the 4 points and get distance between them
// https://swccd.instructure.com/courses/6682/assignments/31433
// https://swccd.instructure.com/courses/6682/files/203101
// http://www.cplusplus.com/reference/cmath/cos/

// C:\getDist 32.639987 -116.995167 32.640870 -116.997001

// The distance between points X and Y is RESULT yards

// we need minimum of 5 args (a lat1,long1,lat2,long2)

// no error checking for arg input, assume correct input




// make a struct
// an array of structs
/* */

double distanceBetween(double lat1, double long1, double lat2, double long2);
double toRadians(double degree);
double calculateDistance(double lat1, double long1, double lat2, double long2);
double kilometerToYards(double kilometers);
struct geoLocation{
    double latitude;
    double longitude;
};


int main(int argc, char* argv[]){

    #define PI 3.14159265

    // get points
    // print output from commandline
    // for loop to print all args
    for (int i = 0; i < argc; i++){
        // maybe do i+1 to avoid program arg
        printf("command line was %s\n", argv[i]);

    }

    //print argc
    //int argc is number of arguments on commandline (a 123 123 = 3 args)
    printf("argc: %d \n", argc);

    double  lat1 = -99.9;
    double  long1 = 99.8;
    double  lat2 = 99.7;
    double  long2 = -99.6;

    struct geoLocation point1;
    struct geoLocation point2;
    point1.latitude = lat1;
    point1.longitude = long1;
    point2.latitude = lat2;
    point2.longitude = long2;


    //get args from command line
    double result = distanceBetween(lat1,long1,lat2,long2);

    printf("The distance between points (%lf , %lf) and (%lf, %lf) is %lf yards. \n", lat1, long1, lat2, long2, result);

    return 0;
}

double distanceBetween(double lat1, double long1, double lat2, double long2){

    // convert to radians
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);

    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    double distance = calculateDistance(lat1,long1,lat2,long2);

    return distance;
}



double toRadians(double degree){

    // pi radians = 180 degrees
    // multiply angle in degrees by pi/180
    // ex:90 degrees
    // 90 * PI/180 = PI/2 ~ 1.57096
    printf("%lf in radians is %lf \n", degree, degree * (M_PI/180.00) );
    return degree * (M_PI/180.00);

}

double calculateDistance(double lat1, double long1, double lat2, double long2){

    // radious of earth in miles
    double RadiusMi = 3963.1676;
    // radius of earth in kilometers
    double RadiusKm = 6371;

    double dlong = (long2 - long1);
    double dlat = (lat2 - lat1);

    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlong/2) * sin(dlong/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    double result = RadiusKm * c;
    //result = kilometerToYards(result);
    return result;
}

double kilometerToYards(double kilometers){
    // convert kilometers to yards
    return kilometers * 1093.6;
}




