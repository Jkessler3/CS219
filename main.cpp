#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

int main(){

    //varaibles
    std::string lineInput; //Reads in an entire line to be paresed, ends at newLine
    std::string operation; //Parsed operation command
    std::string operand1String; //parsed operand1 pre conversion
    std::string operand2String; //parsed operand2 pre conversion
    std::string overflow; //store the value if overflow is found
    uint32_t operand1 = 0; //Used to store the first operand data as int
    uint32_t operand2 = 0; //Used to store the second operand as int
    uint32_t result = 0; // Final result after operation

    //OPEN FILE
    std::ifstream file("Programming-Project-1.txt"); //opens the file

    //Checks if file opens
    if(!file) {
        std::cerr << "File not opened!";
        return 1;
    }
    
    //parsing loop
    while (getline(file, lineInput)){
         std::cout << lineInput;

        // Find the operation
        std::istringstream stream(lineInput);

        stream >> operation >> operand1String >> operand2String;

        if (operation == "ADD" && !operand1String.empty() && !operand2String.empty()) {
            // Convert operands from hex string to uint32_t
            operand1 = strtoul(operand1String.c_str(), NULL, 16);
            operand2 = strtoul(operand2String.c_str(), NULL, 16);

            result = operand1 + operand2;
            std::cout << ": 0x" << std::hex << result << std::endl;
            if((result < operand1) || (result < operand2)){
                overflow = "yes";
            }
            else{
                overflow = "no";
            }
            std::cout << "Overflow: " << overflow << std::endl;
        } 
        else {
            std::cerr << "Error invalid operation or missing operands: " << lineInput << std::endl;
        }
    }

    //CLOSE FILE
    file.close();

    return 0;
}