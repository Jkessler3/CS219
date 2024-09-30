#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

void add()


int main(){

    //varaibles
    char *lineInput; //Reads in an entire line to be paresed, ends at newLine
    char *operation; //Parsed operation command
    char *operand1String //parsed operand1 pre conversion
    char *operand2String //parsed operand2 pre conversion
    uint32_t operand1 = 0; //Used to store the first operand data as int
    uint32_t operand2 = 0; //Used to store the second operand as int
    uint32_t result = 0; // Final result after operation

    //OPEN FILE
    std::ifstream file("Programming-Project-1.txt") //opens the file

    //Checks if file opens
    if(!file {
        std::cerr << "File not opened!";
        return 1;
    })

    //parsing loop
    //while (getline(file, ))

    //Converts strings into uint32_t
    operand1 = strtoul(operand1String, NULL, 16);
    operand2 = strtoul(operand2String, NULL, 16);

    //adds
    result = operand1 + operand2;

    //DETERMINE OPERATION

    //CLOSE FILE

    return 0;
}