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
C:\programName instructions.txt

Calculation checked against 'haversine' formula
http://www.movable-type.co.uk/scripts/latlong.html

Various links
// https://swccd.instructure.com/courses/6682/assignments/31434
// http://www.cplusplus.com/reference/cmath/cos/
*/

/*
TODO:
take input as string
use ascii to integer
integer to binary

Have concatenated string(?) of binary instruction set
figure out instruction format
then get values based on that
print result
*/



// struct declarations
typedef struct instructionSet* link;

struct instructionSet {
  char machineCode[8];
  int binary;
  //hex
  int opcode;
  //hex
  int func;
  int instruction;
  char Format;
  int rd;
  int rs;
  int rt;
  //hex
  int Imm;

  link next;
};
// method declarations
int convertHexAsciiValueToDecimal(char c);

#define MAX_LENGTH 1048576
int main(int argc, char* argv[]){

    //linked list node setup
    link temp,node,head;
    temp = malloc(sizeof(struct instructionSet));
    head = temp;
    node = temp;

    //temporary values read from commandline
    char *tempMachine;
    //char *longitude;

    //commandline line
    char line[MAX_LENGTH];

    //open file from commandline
    FILE* input = fopen(argv[1],"r"); // "r" for read

    if(input == NULL){
        // appropriate args not found
        printf("%s","No such file\n");
        exit(1);
    } else {
        // read args from file and build linked list
        while(fgets(line, 1000, input) != NULL){
            printf("%s \n", line);
            tempMachine = strtok(line, "");

            node->next = malloc(sizeof(*node));
            node = node->next;
            strcpy(node->machineCode, line);
        }
    }

    fclose(input);
    node->next = NULL;

    printAll(head);

    return 0;
}

void printAll( link x){
    //skips uninitialized node
    x=x->next;

    printf("\n");
    if(x==NULL){
        return;
    } else if(x->next==NULL){
        printf("machineCode: %s \n", x->machineCode);

        printf("End\n");
    } else while(x!=NULL){
        printf("machineCode: %s \n", x->machineCode);
        convertToBinary(x->machineCode);
        printf("\n");
        x=x->next;
    }
    return;
}

void convertToBinary(char* machineCode){

    int i;
    for (i = 0; i < strlen(machineCode); i++){
        int result = convertHexAsciiValueToDecimal(machineCode[i]);
        printf("Value: %d \n", result);
    }
}

int convertHexAsciiValueToDecimal(char c){
    if(isalpha(c)){
        char r = tolower(c);
        if(r > 'f'){
            // - Handle error here - character is not base 16
            return 0;
        }

        int nIndex = (int)('a' - r);
        nIndex = -nIndex;
        nIndex += 10;
        return nIndex;
    }
    else if(isdigit(c)){
        int nIndex = c - '0';
        return nIndex;
    }

    // Handle error here - character is not A-F or 0-9
    return 0;
}

int convertDecimalToBinary(int decimal){
        int remainder;
        int binary = 0, i = 1;

    while(decimal != 0) {
        remainder = decimal%2;
        decimal = decimal/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}





