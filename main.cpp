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

    bool flags = false; //store the value if overflow is found
    bool nFlag = false;
    bool zFlag = false;
    uint32_t operand1 = 0; //Used to store the first operand data as int
    uint32_t operand2 = 0; //Used to store the second operand as int
    uint32_t result = 0; // Final result after operation

    //OPEN FILE
    std::ifstream file("Programming-Project-2.txt"); //opens the file

    //Checks if file opens
    if(!file) {
        std::cerr << "File not opened!";
        return 1;
    }
    
    //parsing loop
    while (getline(file, lineInput)){
        //std::cout << lineInput <<'\n';

        // Find the operation
        std::istringstream stream(lineInput);
        stream >> operation >> operand1String >> operand2String;

        // Convert operands from hex string to uint32_t
        operand1 = strtoul(operand1String.c_str(), NULL, 16);
        operand2 = strtoul(operand2String.c_str(), NULL, 16);

        //Checks to see if there is a need to set flags
        if(operation.length() >3 && operation[3] == 'S'){
            flags = true; //sets flags true
            operation.pop_back(); //parses the operations to remove S
            //std::cout << "Operation: " << operation << " flags: " << flags << '\n';
        }
        else{
            flags = false; //sets flags false
            nFlag = false;
            zFlag = false;
            //std::cout << "Flags: " << flags << '\n';
        }
        
        //determine operation and complete it
        if(operation == "ADD" && !operand1String.empty() && !operand2String.empty()){
            //ADD
            result = operand1 + operand2;

        }
        else if(operation == "AND" && !operand1String.empty() && !operand2String.empty()){
            //AND            
            result = operand1 & operand2;

        }
        else if(operation == "ASR" && !operand1String.empty() && !operand2String.empty()){
            //ASR
            result = static_cast<int32_t>(operand1) >> operand2;

        }
        else if(operation == "LSR" && !operand1String.empty() && !operand2String.empty()){
            //LSR
            result = operand1 >> operand2;

        }
        else if(operation == "LSL" && !operand1String.empty() && !operand2String.empty()){
            //LSL
            result = operand1 << operand2;
        }
        else if(operation == "NOT" && !operand1String.empty()){
            //NOT
            result = ~operand1;
        }
        else if(operation == "ORR" && !operand1String.empty() && !operand2String.empty()){
            //ORR
            result = operand1 | operand2;
        }
        else if(operation == "SUB" && !operand1String.empty() && !operand2String.empty()){
            //SUB
            result = operand1 - operand2;
        }
        else if(operation == "XOR" && !operand1String.empty() && !operand2String.empty()){
            //XOR
            result = operand1 ^ operand2;
        }
        else{
            std::cout << "Invalid operation!\n";
        }

        // Set flags
        if (flags) {
            nFlag = (static_cast<int32_t>(result) < 0); // Negative flag set if result is negative
            zFlag = (result == 0); // Zero flag set if result is zero
        }

        //Display results
        std::cout << operation;
        if(flags){
            std::cout << 'S';
        }
        std::cout << '\t' << operand1String << " " << operand2String << ": 0x" << std::hex << std::uppercase << result << '\n';
        std::cout << "N: " << nFlag << " Z: " << zFlag << '\n'; 
    }

    //CLOSE FILE
    file.close();

    return 0;
}
