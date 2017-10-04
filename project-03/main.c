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

Various links
// https://swccd.instructure.com/courses/6682/assignments/31435
// http://www.kurtm.net/mipsasm/index.cgi
*/

/*
TODO:
take input as string

add to struct instructionSet

add binary version of input aswell

call individual functions to add rest of codes to struct

Function to print a full instructionset

Use printAll to display all instructionSets

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
char integerToHex(int integer);
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

    //open file from commandline
    FILE* input = fopen(argv[1],"r"); // "r" for read

    if(input == NULL){
        // appropriate args not found
        printf("%s","No such file\n");
        exit(1);
    } else {
        // read args from file and build linked list
        while(fgets(line, 1000, input) != NULL){

            // remove carriage return from string input
            int i = 0;
            while(i<10){
                if(i == 8){
                    // go to 8th index and push in terminating character
                    line[i] = '\0';
                }
                printf("%d", line[i]);
                i++;
            }

            printf("\n");
            //printf("%s", line); //pull out last index of string array first?

            // allocate memory for next node
            node->next = malloc(sizeof(*node));
            node = node->next;

            // assign to current node
            strcpy(node->machineCode, line);
            strcpy(node->binary, convertHexToBinary(line));
            node->opcode = getOpcode(node->binary);
        }
    }

    fclose(input);
    node->next = NULL;

    //printAll(head);
    writeToFile(head);

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
        printf("Binary number: %s \n", x->binary);
        printf("End\n");
    } else while(x!=NULL){
        printf("machineCode: %s", x->machineCode);
        printf("Binary number: %s \n", x->binary);
        printf("Opcode: %c \n", integerToHex(x->opcode));
        printf("\n");
        x=x->next;
    }
    return;
}

void printIntArray(int array[], int arraySize){
    int i;
    for (i=0; i < arraySize; i++) {
        printf("%d",array[i]);
    }
}

getOpcode(char binary[32]){
    // return hex number
    char opCode[6];
    // analyse first 6 bits to determine opcode
    for(int i = 0; i < 6; i++){
        opCode[i] = binary[i];

    }

    //printf("opcode: %d", binaryToInteger(opCode));

    return binaryToInteger(opCode);
}

getFunc(){
    // return func hex
}

getMIPS(){
    // return operation (addiu, ori, lui, add etc)
}

getFormat(){
    // return "I" or "R"
}

getRD(){
    //return hex of RD
}

getRS(){
    // return hex of RS
}

getRT(){
    // return hex of RT
}

getImm(){
    // return Immediate value
    //which is last 4 digits of machineCode
    // IE: 24020004 = 0044
}

int binaryToInteger(const char *s){
  return (int) strtol(s, NULL, 2);
}

void writeToFile(link x){
    FILE* fp = fopen("out.csv", "w"); //to write

    //skips uninitialized node
    x=x->next;

    printf("\n");
    if(x==NULL){
        return;
    } else if(x->next==NULL){
        fprintf(fp,"machineCode: %s \n", x->machineCode);
        fprintf(fp,"Binary number: %s \n", x->binary);
        fprintf(fp,"Opcode: %c \n", integerToHex(x->opcode));
        fprintf(fp,"End\n");
    } else while(x!=NULL){
        /*
        fprintf(fp,"machineCode: %s \n", x->machineCode);
        fprintf(fp,"Binary number: %s \n", x->binary);
        fprintf(fp,"Opcode: %c \n", integerToHex(x->opcode));
        fprintf(fp,"\n");
        */
        fprintf(fp,"%s,%s,%c \n", x->machineCode,x->binary,integerToHex(x->opcode));
        x=x->next;
    }
    return;
}

char integerToHex(int integer){
    char result;
    printf("integer: %d \n", integer);
    switch(integer){
        case 0:
            result = '0';
            return result;
        case 1:
            result = '1';
            return result;
        case 2:
            result = '2';
            return result;
        case 3:
            result = '3';
            return result;
        case 4:
            result = '4';
            return result;
        case 5:
            result = '5';
            return result;
        case 6:
            result = '6';
            return result;
        case 7:
            result = '7';
            return result;
        case 8:
            result = '8';
            return result;
        case 9:
            result = '9';
            return result;
        case 10:
            result = 'a';
            return result;
        case 11:
            result = 'b';
            return result;
        case 12:
            result = 'c';
            return result;
        case 13:
            result = 'd';
            return result;
        case 14:
            result = 'e';
            return result;
        case 15:
            result = 'f';
            return result;
        default:
            // NOT A HEX VALUE
            result = 'x';
            return result;
            break;
    }
}

char* convertHexToBinary(char* hex){

    int i =0;
    // create new char array with size for 4bit digits
    char* binaryInstruction = malloc(33);

    // initialize null terminator
    binaryInstruction[0] = '\0';

    // extract each hex digit and convert to 16bit binary
    for(i=0; hex[i]!='\0'; i++){
        switch(hex[i]){
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

    //printf("Binary number   : %s \n", binaryInstruction);
    return binaryInstruction;

}
