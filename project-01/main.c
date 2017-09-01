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


int main(int argc, char* argv[])
{
    #define PI 3.14159265

    double RADIUS = 3963.1676;

    // print output from commandline
    // for loop to print all args
    for (int i = 0; i < argc; i++){
        // maybe do i+1 to avoid program arg
        printf("command line was %s\n", argv[i]);
    }

    //print argc
    //int argc is number of arguments on commandline (a 123 123 = 3 args)
    printf("argc: %d \n", argc);












    return 0;
}
