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


  //declare as size 3, 2 for digits +1 null terminator
  //hex value
  char opcode[3];
  //hex value
  char func[3];

  char instruction[6];

  char format;

  char rd[3];

  char rs[3];

  char rt[3];

  //hex
  int Imm;

  link next;
};
// method declarations
char* convertHexToBinary(char hex[]);
char integerToHex(int integer);
void printIntArray(int array[], int arraySize);
char getFormat(char opcode[3]);
void getFunc(char format,char binary[32],char func[3]);
void getOpcode(char opcode[3], char binary[32]);
void getMIPS(char instruction[6],char opcode[3],char format,char func[3]);
void getRD(char rd[3],char binary[32],char format);
void getRS(char rs[3],char binary[32]);
void getRT(char rt[3],char binary[32]);

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
                i++;
            }

            // allocate memory for next node
            node->next = malloc(sizeof(*node));
            node = node->next;

            // assign to current node
            // TODO change these from strcpy to function calls, similar to getFunc?
            strcpy(node->machineCode, line);
            strcpy(node->binary, convertHexToBinary(line));

            getOpcode(node->opcode, node->binary);

            node->format = getFormat(node->opcode);

            getFunc(node->format,node->binary,node->func);
            getMIPS(node->instruction,node->opcode,node->format,node->func);
            getRD(node->rd,node->binary,node->format);
            getRS(node->rs,node->binary);
            getRT(node->rt,node->binary);

            printf("\n");
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
        //printf("Opcode: %c \n", integerToHex(x->opcode));
        printf("\n");
        x=x->next;
    }
    return;
}

void getOpcode(char opcode[3], char binary[32]){
    // return hex number
    char opCodeTemp[6];
    char result[2];
    // analyse first 6 bits to determine opcode
    for(int i = 0; i < 6; i++){
        opCodeTemp[i] = binary[i];

    }
    sprintf(result, "%x", binaryToInteger(opCodeTemp));
    strcpy(opcode,result);
}

void getFunc(char format,char binary[32],char func[3]){
    char result[3];
    char binarySet[6];
    int hexAsInt = 0;
    //printf("binary: %s \n", binary);
    // ONLY R instruction format will have func value
    // return func hex
    if(format == 'R'){
        // read last 6 digits of binary
        // convert int value to 2 digit hex string
        for(int i = 0; i < 34; i++){
            //printf("int i: %d \n", i);
            if( i >= 26){
                //printf("setting binarySet[%c] with binary[%c] \n",binarySet[i], binary[i]);
                binarySet[i-26] = binary[i];
            }
        }

        //printf("binarySet %s \n", binarySet);
        hexAsInt = binaryToInteger(binarySet);

        // places HexAsInt as a hex value into result
        sprintf(result, "%x", hexAsInt);
        //printf("result: %s \n", result);
        //return result;
        strcpy(func,result);

    } else {
        // Format is I instruction, which has no function code
        result[0] = '-';
        result[1] = '\0';
        strcpy(func,result);
        //return result;
    }
}

void getMIPS(char instruction[6],char opcode[3],char format,char func[3]){
    // set instruction to operation (addiu, ori, lui, add etc)
    char result[6];
    if(format == 'R'){
        // R format
        // use func
        if (strcmp("20",func) == 0){
            //printf("funcBefore: %s \n", func);
            printf("opcode: %s is instruction add \n",func);
            sprintf(result, "%s", "add");
            strcpy(instruction,result);
            //printf("funcAfter: %s \n", func);
            return;
        } else if(strcmp("21",func) == 0){
                printf("opcode: %s is instruction addu \n",func);
            sprintf(result, "%s", "addu");
            strcpy(instruction,result);
            return;

        } else if(strcmp("24",func) == 0){
                printf("opcode: %s is instruction and \n",func);
            sprintf(result, "%s", "and");
            strcpy(instruction,result);
            return;

        } else if(strcmp("08",func) == 0){
                printf("opcode: %s is instruction jr \n",func);
            sprintf(result, "%s", "jr");
            strcpy(instruction,result);
            return;

        } else if(strcmp("27",func) == 0){
                printf("opcode: %s is instruction nor \n",func);
            sprintf(result, "%s", "nor");
            strcpy(instruction,result);
            return;

        } else if(strcmp("25",func) == 0){
                printf("opcode: %s is instruction or \n",func);
            sprintf(result, "%s", "or");
            strcpy(instruction,result);
            return;

        } else if(strcmp("2a",func) == 0){
                printf("opcode: %s is instruction slt \n",func);
            sprintf(result, "%s", "slt");
            strcpy(instruction,result);
            return;

        } else if(strcmp("2b",func) == 0){
                printf("opcode: %s is instruction sltu \n",func);
            sprintf(result, "%s", "sltu");
            strcpy(instruction,result);
            return;

        } else if(strcmp("00",func) == 0){
                printf("opcode: %s is instruction sll \n",func);
            sprintf(result, "%s", "sll");
            strcpy(instruction,result);
            return;

        } else if(strcmp("02",func) == 0){
                printf("opcode: %s is instruction srl \n",func);
            sprintf(result, "%s", "srl");
            strcpy(instruction,result);
            return;

        } else if(strcmp("22",func) == 0){
                printf("opcode: %s is instruction sub \n",func);
            sprintf(result, "%s", "sub");
            strcpy(instruction,result);
            return;

        } else if(strcmp("23",func) == 0){
                printf("opcode: %s is instruction subu \n",func);
            sprintf(result, "%s", "subu");
            strcpy(instruction,result);
            return;
        }

    } else {
        // I format
        // use opcode
        if (strcmp("9",opcode) == 0){
            printf("opcode: %s is instruction addiu \n",opcode);
            sprintf(result, "%s", "addiu");
            strcpy(instruction,result);
            return;
        } else if(strcmp("8",opcode) == 0){
                printf("opcode: %s is instruction addi \n",opcode);
            sprintf(result, "%s", "addi");
            strcpy(instruction,result);
            return;

        } else if(strcmp("c",opcode) == 0){
                printf("opcode: %s is instruction andi \n",opcode);
            sprintf(result, "%s", "andi");
            strcpy(instruction,result);
            return;

        } else if(strcmp("4",opcode) == 0){
                printf("opcode: %s is instruction beq \n",opcode);
            sprintf(result, "%s", "beq");
            strcpy(instruction,result);
            return;

        } else if(strcmp("5",opcode) == 0){
                printf("opcode: %s is instruction bne \n",opcode);
            sprintf(result, "%s", "bne");
            strcpy(instruction,result);
            return;

        } else if(strcmp("24",opcode) == 0){
                printf("opcode: %s is instruction lbu \n",opcode);
            sprintf(result, "%s", "lbu");
            strcpy(instruction,result);
            return;

        } else if(strcmp("25",opcode) == 0){
                printf("opcode: %s is instruction lhu \n",opcode);
            sprintf(result, "%s", "lhu");
            strcpy(instruction,result);
            return;

        } else if(strcmp("30",opcode) == 0){
                printf("opcode: %s is instruction ll \n",opcode);
            sprintf(result, "%s", "ll");
            strcpy(instruction,result);
            return;

        } else if(strcmp("f",opcode) == 0){
                printf("opcode: %s is instruction lui \n",opcode);
            sprintf(result, "%s", "lui");
            strcpy(instruction,result);
            return;

        } else if(strcmp("23",opcode) == 0){
                printf("opcode: %s is instruction lw \n",opcode);
            sprintf(result, "%s", "lw");
            strcpy(instruction,result);
            return;

        } else if(strcmp("d",opcode) == 0){
                printf("opcode: %s is instruction ori \n",opcode);
            sprintf(result, "%s", "ori");
            strcpy(instruction,result);
            return;

        } else if(strcmp("a",opcode) == 0){
                printf("opcode: %s is instruction slti \n",opcode);
            sprintf(result, "%s", "slti");
            strcpy(instruction,result);
            return;

        } else if(strcmp("b",opcode) == 0){
                printf("opcode: %s is instruction sltiu \n",opcode);
            sprintf(result, "%s", "sltiu");
            strcpy(instruction,result);
            return;

        } else if(strcmp("28",opcode) == 0){
                printf("opcode: %s is instruction sb \n",opcode);
            sprintf(result, "%s", "sb");
            strcpy(instruction,result);
            return;

        } else if(strcmp("38",opcode) == 0){
                printf("opcode: %s is instruction sc \n",opcode);
            sprintf(result, "%s", "sc");
            strcpy(instruction,result);
            return;

        } else if(strcmp("29",opcode) == 0){
                printf("opcode: %s is instruction sh \n",opcode);
            sprintf(result, "%s", "sh");
            strcpy(instruction,result);
            return;

        } else if(strcmp("2b",opcode) == 0){
                printf("opcode: %s is instruction sw \n",opcode);
            sprintf(result, "%s", "sw");
            strcpy(instruction,result);
            return;
        }
    }
}

char getFormat(char opcode[3]){
    char result;
    int hexToInt = (int)strtol(opcode, NULL, 16);
    // return "I" or "R"
    // read opcode values
    // if opcode = 0, it is an R format instruction (and will then have a function)
    if(hexToInt == 0){
        //R format
        result = 'R';
        return result;
    } else {
        result = 'I';
        return result;
    }
}

void getRD(char rd[3],char binary[32],char format){
    // set RD as int value
    char result[3];
    char binarySet[6];
    int binaryAsInt = 0;
    //printf("binary: %s \n", binary);
    // ONLY R instruction format will have RD value
    if(format == 'R'){
        // read digits 16-20 of binary
        // convert int value to 2 digit int string
        int j = 0;
        for(int i = 0; i < 34; i++){
            //printf("int i: %d \n", i);
            if( i >= 16 && i <=20){
                //printf("int i: %d \n", i);
                //printf("int j: %d \n", j);
                //printf("setting binarySet[%d] with binary[%c] \n",binarySet[j], binary[i]);
                binarySet[j] = binary[i];
                //printf("binaryset[%d]: %c\n",binarySet[j],binarySet[i]);
                j++;
            }
        }
        // set last value as null terminator
        binarySet[5] = '\0';

        binaryAsInt = binaryToInteger(binarySet);

        // places binary as integer into rd
        sprintf(result, "%d", binaryAsInt);
        //printf("result: %s \n", result);
        //return result;
        strcpy(rd,result);

    } else {
        // Format is I instruction, which has no rd value
        result[0] = '-';
        result[1] = '\0';
        strcpy(rd,result);
        //return result;
    }
}

void getRS(char rs[3],char binary[32]){

    //TODO ADD CHECK IF INSTRUCTION DOES NOT TAKE RS?

    // will have RS for R and I formats
    // set RS as int value
    char result[3];
    char binarySet[6];
    int binaryAsInt = 0;
    printf("binary: %s \n", binary);

    // read digits 6-10 of binary
    // convert int value to 2 digit int string
    int j = 0;
    for(int i = 0; i < 34; i++){
        //printf("int i: %d \n", i);
        if( i >=6  && i <=10){
            //printf("int i: %d \n", i);
            //printf("int j: %d \n", j);
            //printf("setting binarySet[%d] with binary[%c] \n",binarySet[j], binary[i]);
            binarySet[j] = binary[i];
            //printf("binaryset[%d]: %c\n",binarySet[j],binarySet[i]);
            j++;
        }
    }
    // set last value as null terminator
    binarySet[5] = '\0';

    binaryAsInt = binaryToInteger(binarySet);

    // places binary as integer into rd
    sprintf(result, "%d", binaryAsInt);
    //printf("result: %s \n", result);
    //return result;
    strcpy(rs,result);

}

void getRT(char rt[3],char binary[32]){
    // will have RT for R and I formats
    // set RT as int value
    char result[3];
    char binarySet[6];
    int binaryAsInt = 0;
    printf("binary: %s \n", binary);

    // read digits 6-10 of binary
    // convert int value to 2 digit int string
    int j = 0;
    for(int i = 0; i < 34; i++){
        //printf("int i: %d \n", i);
        if( i >=11  && i <=15){
            printf("int i: %d \n", i);
            printf("int j: %d \n", j);
            printf("setting binarySet[%d] with binary[%c] \n",binarySet[j], binary[i]);
            binarySet[j] = binary[i];
            printf("binaryset[%d]: %c\n",binarySet[j],binarySet[i]);
            j++;
        }
    }
    // set last value as null terminator
    binarySet[5] = '\0';

    binaryAsInt = binaryToInteger(binarySet);

    // places binary as integer into rd
    sprintf(result, "%d", binaryAsInt);
    printf("result: %s \n", result);
    //return result;
    strcpy(rt,result);
}

getImm(){
    // return Immediate value
    //which is last 4 digits of machineCode
    // IE: 24020004 = 0044
}
/*
char integerToHex(const char *s){
  return (int) strtol(s, NULL, 2);
}
*/

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
        //fprintf(fp,"Opcode: %c \n", integerToHex(x->opcode));
        fprintf(fp,"End\n");
    } else while(x!=NULL){
        /*
        fprintf(fp,"machineCode: %s \n", x->machineCode);
        fprintf(fp,"Binary number: %s \n", x->binary);
        fprintf(fp,"Opcode: %c \n", integerToHex(x->opcode));
        fprintf(fp,"\n");
        */
        fprintf(fp,"%s,%s,%s,%s,%s,%c,%s,%s,%s \n", x->machineCode,x->binary,x->opcode,x->func,x->instruction,x->format,x->rd,x->rs,x->rt);
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
