// Alexander Vaughan, av1045643
// av1045643@swccd.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*
############# PROJECT INFO #############
cplusplus.com
C library reference, has list of all includes

Expected commandline input
C:\getDist 32.639987 -116.995167 32.640870 -116.997001

Calculation checked against 'haversine' formula
http://www.movable-type.co.uk/scripts/latlong.html

Various links
// https://swccd.instructure.com/courses/6682/assignments/31433
// https://swccd.instructure.com/courses/6682/files/203101
// http://www.cplusplus.com/reference/cmath/cos/

// we need minimum of 5 args (a lat1,long1,lat2,long2)
// no error checking for arg input, assume correct input
*/

// struct declarations
struct geoLocation{
    double latitude;
    double longitude;
};

// method declarations
double calculateDistance(double lat1, double long1, double lat2, double long2);
void printResult(struct geoLocation, struct geoLocation, double result);
double distanceBetween(struct geoLocation one, struct geoLocation two);
double kilometerToYards(double kilometers);
double toRadians(double degree);

int main(int argc, char* argv[]){

    struct geoLocation point1;
    struct geoLocation point2;

    // for loop to assign args to geoLocations
    for (int i = 0; i < argc; i++){

        // DEBUG
        //printf("command line was %s\n", argv[i]);

        // get points
        if(i == 0){
            // skip inital arg
        } else if(i == 1){
            sscanf(argv[i],"%lf", &point1.latitude);
        } else if(i == 2) {
            sscanf(argv[i],"%lf", &point1.longitude);
        } else if(i == 3) {
            sscanf(argv[i],"%lf", &point2.latitude);
        } else if(i == 4) {
            sscanf(argv[i],"%lf", &point2.longitude);
        }
    }

    // calculate distance
    double result = distanceBetween(point1,point2);

    // print result
    printResult(point1,point2,result);

    return 0;
}

double distanceBetween(struct geoLocation one, struct geoLocation two){

    // convert to radians
    double lat1 = toRadians(one.latitude);
    double long1 = toRadians(one.longitude);

    double lat2 = toRadians(two.latitude);
    double long2 = toRadians(two.longitude);

    // calculate distance points
    double distance = calculateDistance(lat1,long1,lat2,long2);

    return distance;
}

double toRadians(double degree){

    // multiply coordindate in degrees by pi/180 to get radians
    // ex:90 degrees
    // 90 * PI/180 = PI/2 ~ 1.57096

    //DEBUG
    //printf("%lf in radians is %lf \n", degree, degree * (M_PI/180.00) );

    return degree * (M_PI/180.00);
}

double calculateDistance(double lat1, double long1, double lat2, double long2){

    // radious of earth in miles
    double RadiusMi = 3963.1676;
    // radius of earth in kilometers
    double RadiusKm = 6371;

    // midpoint formula
    double dlong = (long2 - long1);
    double dlat = (lat2 - lat1);

    // calculate distance formula
    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlong/2) * sin(dlong/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    // result
    double result = RadiusKm * c;
    // convert to yards
    result = kilometerToYards(result);
    return result;
}

double kilometerToYards(double kilometers){
    // convert kilometers to yards
    return kilometers * 1093.6;
}

void printResult(struct geoLocation one, struct geoLocation two, double result){
    printf("The distance between points (%lf , %lf) and (%lf, %lf) is %lf yards. \n", one.latitude, one.longitude, two.latitude, two.longitude, result);
}





