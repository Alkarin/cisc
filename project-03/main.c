// Alexander Vaughan, av1045643
// av1045643@swccd.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

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
// http://www.kurtm.net/mipsasm/index.cgi
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

  // initial hex instruction
  char* machineCode[8];
  // instruction converted to 32bit binary
  char binary[32];

  int binaryAsNum;
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
char* convertHexToBinary(char hex[]);
void printIntArray(int array[], int arraySize);

//typedef short int16_t

#define MAX_LENGTH 1048576
int main(int argc, char* argv[]){

    //linked list node setup
    link temp,node,head;
    temp = malloc(sizeof(struct instructionSet));
    head = temp;
    node = temp;

    //commandline line
    char line[MAX_LENGTH];

    char *tempHex;

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

            // allocate memory for next node
            node->next = malloc(sizeof(*node));
            node = node->next;

            //tempHex = (char *) malloc(sizeof(char) * 32);
            tempHex = convertHexToBinary(line);
            printf("temphex: %s \n", tempHex);


            strcpy(node->machineCode, line);
            strcpy(node->binary, &tempHex);

            printf("machineCode: %s \n", node->machineCode);
            printf("Binary number: %s \n", node->binary);

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
        printf("machineCode2: %s \n", x->machineCode);
        printf("Binary number2: %s \n", x->binary);

        printf("End\n");
    } else while(x!=NULL){
        printf("machineCode2: %s \n", x->machineCode);
        printf("Binary number2: %s \n", x->binary);
        printf("\n");
        x=x->next;
    }
    return;
}

char* convertHexToBinary(char* hex){

    int i =0;
    // create new char array with size for 4bit digits
    char* binaryInstruction = malloc(33);

    // initialize null terminator
    binaryInstruction[0] = '\0';

    // extract each hex digit and convert to 16bit binary
    for(i=0; hex[i]!='\0'; i++)
    {
        switch(hex[i])
        {
            case '0':
                strcat(binaryInstruction, "0000");
                break;
            case '1':
                strcat(binaryInstruction, "0001");
                break;
            case '2':
                strcat(binaryInstruction, "0010");
                break;
            case '3':
                strcat(binaryInstruction, "0011");
                break;
            case '4':
                strcat(binaryInstruction, "0100");
                break;
            case '5':
                strcat(binaryInstruction, "0101");
                break;
            case '6':
                strcat(binaryInstruction, "0110");
                break;
            case '7':
                strcat(binaryInstruction, "0111");
                break;
            case '8':
                strcat(binaryInstruction, "1000");
                break;
            case '9':
                strcat(binaryInstruction, "1001");
                break;
            case 'a':
            case 'A':
                strcat(binaryInstruction, "1010");
                break;
            case 'b':
            case 'B':
                strcat(binaryInstruction, "1011");
                break;
            case 'c':
            case 'C':
                strcat(binaryInstruction, "1100");
                break;
            case 'd':
            case 'D':
                strcat(binaryInstruction, "1101");
                break;
            case 'e':
            case 'E':
                strcat(binaryInstruction, "1110");
                break;
            case 'f':
            case 'F':
                strcat(binaryInstruction, "1111");
                break;
            default:
                // should be end of input
                break;
        }
    }

    printf("Binary number = %s \n", binaryInstruction);
    return binaryInstruction;

}

void printIntArray(int array[], int arraySize){
    int i;
    for (i=0; i < arraySize; i++) {
        printf("%d",array[i]);
    }
}





