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
C:\getDist coordinateFile.txt

Calculation checked against 'haversine' formula
http://www.movable-type.co.uk/scripts/latlong.html

Various links
// https://swccd.instructure.com/courses/6682/assignments/31434
// http://www.cplusplus.com/reference/cmath/cos/
*/

// struct declarations
typedef struct latLong* link;

struct latLong {
  double latitude;
  double longitude;
  link next;
};

// method declarations
double calculateDistance(double lat1, double long1, double lat2, double long2);
double distanceBetween(struct latLong one, struct latLong two);
double toRadians(double degree);
void  printClosest(struct latLong*  head, struct latLong  myLocation);

#define MAX_LENGTH 1048576
int main(int argc, char* argv[]){

    // barefoot solutions
    struct latLong  myLocation;

    //linked list node setup
    link temp,node,head;
    temp = malloc(sizeof(struct latLong));
    head = temp;
    node = temp;

    //commandline line
    char line[MAX_LENGTH];

    //temporary values read from commandline
    char *latitude;
    char *longitude;

    FILE* input = fopen(argv[1],"r"); // "r" for read

    if(input == NULL){
        // appropriate args not found
        printf("%s","No such file\n");
        exit(1);
    } else {
        // ensure first line populates myLocation
        int lineNumber = 1;
        // read args from file and build linked list
        while(fgets(line, 1000, input) != NULL){

            latitude = strtok(line, ",");
            longitude = strtok(NULL, "");

            if(lineNumber==1){
                myLocation.latitude = atof(latitude);
                myLocation.longitude = atof(longitude);
            } else {
                node->next = malloc(sizeof(*node));
                node = node->next;
                node->latitude = atof(latitude);
                node->longitude = atof(longitude);
            }
            lineNumber++;
        }

        fclose(input);

        node->next = NULL;

        //TODO: first node is uninitialized
        //printAll(head);

        printClosest(head,myLocation);

    }
    return 0;
}

void printAll( link x){
    //skips uninitialized node
    x=x->next;

    printf("\n");
    if(x==NULL){
        return;
    } else if(x->next==NULL){
        printf("latitude: %f \n", x->latitude);
        printf("longitude: %f \n", x->longitude);
        printf("End\n");
    } else while(x!=NULL){
        printf("latitude: %f \n", x->latitude);
        printf("longitude: %f \n", x->longitude);
        printf("\n");
        x=x->next;
    }
    return;
}

double distanceBetween(struct latLong one, struct latLong two){

    // convert to radians
    double lat1 = toRadians(one.latitude);
    double long1 = toRadians(one.longitude);

    double lat2 = toRadians(two.latitude);
    double long2 = toRadians(two.longitude);

    // calculate distance points
    double distance = calculateDistance(lat1,long1,lat2,long2);

    return distance;
}

double calculateDistance(double lat1, double long1, double lat2, double long2){

    // radious of earth in miles
    double RadiusMi = 3963.1676;

    // midpoint formula
    double dlong = (long2 - long1);
    double dlat = (lat2 - lat1);

    // calculate distance formula
    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlong/2) * sin(dlong/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    // result
    double result = RadiusMi * c;
    // convert to yards
    //result = kilometerToYards(result);
    return result * 1760;
}

double toRadians(double degree){

    // multiply coordindate in degrees by pi/180 to get radians
    // ex:90 degrees
    // 90 * PI/180 = PI/2 ~ 1.57096

    //DEBUG
    //printf("%lf in radians is %lf \n", degree, degree * (M_PI/180.00) );

    return degree * (M_PI/180.00);
}

void  printClosest(struct latLong*  head, struct latLong  myLocation){

    //skips uninitialized node
    head=head->next;
    printf("\n");

    //array size
    int i = 0;

    //distance between coordinates
    double result;

    //get array of results with their associated coordinate
    double distance[linkedListLength(head)];
    struct latLong coordinates[linkedListLength(head)];

    if(head==NULL){
        return;
    } else if(head->next==NULL){
        // calculate distance
        result = distanceBetween(*head,myLocation);
        distance[i] = result;
        coordinates[i] = *head;
        i++;
        printf("End\n");
    } else while(head!=NULL){
        // calculate distance
        result = distanceBetween(*head,myLocation);

        // place results in array
        distance[i] = result;
        coordinates[i] = *head;

        //increment array size
        i++;
        head=head->next;
    }

    printResult(distance,coordinates,i);
    return;

}

void printResult(double distance[],struct latLong coordinates[],int arraySize){

    //which array index to pull closest distance and its associated coordinates
    int index = shortestDistanceIndex(distance,arraySize);

    //printf("latLong: (%lf,%lf) is the closest distance at %.02lf yards \n", coordinates[index].latitude, coordinates[index].longitude, distance[index]);
    printf("The location closest to the first point is at: %lf,%lf\n", coordinates[index].latitude, coordinates[index].longitude);

}

int shortestDistanceIndex(double a[], int n) {
  int c, index;
  double min;

  // use first index as default min
  min = a[0];
  index = 0;

  // compare shortest distance to current value
  for (c = 0; c < n; c++) {
    if (a[c] < min) {
       index = c;
       min = a[c];
    }
  }

  // returns index of the shortest distance
  return index;
}

int linkedListLength(struct latLong* head)
{
    //walks linked list and returns number of links
    int num = 0;
    while (head != NULL)
    {
        num += 1;
        head = head->next;
    }
    return num;
}






