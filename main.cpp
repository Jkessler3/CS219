//Author: Jon Kessler
//Date: 11/10/2024
//Purpose: Implementation of HW 3

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define FILE_NAME "Programming-Project-3.txt" //Change this to the test file

int main(){

    //varaibles
    std::string lineInput; //Reads in an entire line to be paresed, ends at newLine
    std::string operation; //Parsed operation command
    std::string operand1String; //parsed operand1 pre conversion
    std::string operand2String; //parsed operand2 pre conversion
    std::string operand3String; //parsed operand3 pre conversion


    bool flags = false; //store the value if overflow is found
    bool nFlag = false;
    bool zFlag = false;
    bool cFlag = false;
    bool vFlag = false;

    uint32_t operand1 = 0; //Used to store the first operand data as uint
    uint32_t operand2 = 0; //Used to store the second operand as uint
    uint32_t operand3 = 0; //Used to store the third operand as uint
    uint32_t result = 0; // Final result after operation
    uint32_t registers[8] = {0}; //Array of registers

    //OPEN FILE
    std::ifstream file(FILE_NAME); //opens the file

    //Checks if file opens
    if(!file) {
        std::cerr << "File not opened!";
        return 1;
    }
    
    //parsing loop
    while (getline(file, lineInput)){
        //std::cout << lineInput <<'\n';

        std::transform(lineInput.begin(), lineInput.end(), lineInput.begin(), toupper);


        // Find the operation
        std::istringstream stream(lineInput);
        stream >> operation >> operand1String >> operand2String >> operand3String;


        // Convert operands from hex string to uint32_t
        if(!operand1String.empty()){
            operand1 = strtoul(operand1String.substr(1).c_str(), NULL, 16);
            }
        if(!operand2String.empty()){
            operand2 = strtoul(operand2String.substr(1).c_str(), NULL, 16);
            }    
        if(!operand3String.empty()){
            operand3 = strtoul(operand3String.substr(1).c_str(), NULL, 16);
            }

        //std::cout << "OPCODE: " << operation << " O1: " << operand1String << " O2: " << operand2String << " O3: " << operand3String << std::endl;
        //std::cout << "OPCODE: " << operation << " O1: " << operand1 << " O2: " << operand2 << " O3: " << operand3 << std::endl;

        

        //Checks to see if there is a need to set flags
        if(operation.length() >3 && operation[3] == 'S'){
            flags = true; //sets flags true
            operation.pop_back(); //parses the operations to remove S
            //std::cout << "Operation: " << operation << " flags: " << flags << '\n';
        }
        else{
            flags = false; //sets flags false
            //std::cout << "Flags: " << flags << '\n';
        }
        
        //determine operation and complete it
        if(operation == "ADD" && !operand1String.empty() && !operand2String.empty() && !operand3String.empty()){
            //ADD
            if(operand3String[0] == '#'){
                result = registers[operand2] + operand3;
                if(flags){
                    cFlag = ((result < registers[operand2]) || (result < operand2));
                    vFlag = (((static_cast<int32_t>(registers[operand2]) > 0) && (static_cast<int32_t>(operand3) > 0) && (static_cast<int32_t>(result) < 0)) || ((static_cast<int32_t>(registers[operand2]) < 0) && (static_cast<int32_t>(operand3) < 0) && (static_cast<int32_t>(result) > 0)));
                }
            }
            else{
                result = registers[operand2] + registers[operand3];
                if(flags){
                    cFlag = ((result < registers[operand2]) || (result < registers[operand3]));
                    vFlag = (((static_cast<int32_t>(registers[operand2]) > 0) && (static_cast<int32_t>(registers[operand3]) > 0) && (static_cast<int32_t>(result) < 0)) || ((static_cast<int32_t>(registers[operand2]) < 0) && (static_cast<int32_t>(registers[operand3]) < 0) && (static_cast<int32_t>(result) > 0)));
                }
            }
            registers[operand1] = result;
        }
        else if(operation == "AND" && !operand1String.empty() && !operand2String.empty() && !operand3String.empty()){
            //AND          
            if(operand3String[0] == '#'){
                result = registers[operand2] & operand3;
            }
            else{
                result = registers[operand2] & registers[operand3];
            }  
            registers[operand1] = result;

        }
        else if(operation == "ASR" && !operand1String.empty() && !operand2String.empty() && !operand3String.empty()){
            //ASR
            if(operand3String[0] == '#'){
                result = static_cast<int32_t>(registers[operand2]) >> operand3;
                if(flags){
                    cFlag = (static_cast<int32_t>(registers[operand2]) & (1 << (operand3 - 1))) != 0;
                }
                
            }
            else{
                result = static_cast<int32_t>(registers[operand2]) >> registers[operand3];
                if(flags){
                    cFlag = (static_cast<int32_t>(registers[operand2]) & (1 << (registers[operand3] - 1))) != 0;
                }
            }
            registers[operand1] = result;

        }
        else if(operation == "LSR" && !operand1String.empty() && !operand2String.empty() && !operand3String.empty()){
            //LSR
            if(operand3String[0] == '#'){
                result = registers[operand2] >> operand3;
                if(flags){
                    cFlag = (registers[operand2] & (1 << (operand3 - 1))) != 0;
                }
            }
            else{
                result = registers[operand2] >> registers[operand3];
                if(flags){
                    cFlag = (registers[operand2] & (1 << (registers[operand3] - 1))) != 0;
                }
            }
            registers[operand1] = result;

        }
        else if(operation == "LSL" && !operand1String.empty() && !operand2String.empty() && !operand3String.empty()){
            //LSL
            if(operand3String[0] == '#'){
                result = registers[operand2] << operand3;
                if(flags){
                    cFlag = (registers[operand2] >> (32 - operand3)) & 1;
                }
            }
            else{
                result = registers[operand2] << registers[operand3];
                if(flags){
                    cFlag = (registers[operand2] >> (32 - registers[operand3])) & 1; // Update Carry (MSB shifted out)
                }
            }
            registers[operand1] = result;
        }
        else if(operation == "NOT" && !operand1String.empty()){
            //NOT
            if(operand2String[0] == '#'){
                result = ~registers[operand2];
            }
            else{
                result = ~operand2;
            }
            registers[operand1] = result;
            operand3String.clear();
        }
        else if(operation == "ORR" && !operand1String.empty() && !operand2String.empty()){
            //ORR
            if(operand3String[0] == '#'){
                result = registers[operand2] | operand3;
            }
            else{
                result = registers[operand2] | registers[operand3];
            }
            registers[operand1] = result;
        }
        else if(operation == "SUB" && !operand1String.empty() && !operand2String.empty()){
            //SUB
            if(operand3String[0] == '#'){
                result = registers[operand2] - operand3;
                if(flags){
                    cFlag = ((result < registers[operand2]) || (result < operand2));
                    vFlag = (static_cast<int32_t>(registers[operand2]) > 0 && static_cast<int32_t>(operand3) < 0 && static_cast<int32_t>(result) < 0) || (static_cast<int32_t>(registers[operand2]) < 0 && static_cast<int32_t>(operand3) > 0 && static_cast<int32_t>(result) > 0);                
                    }
            }
            else{
                result = registers[operand2] - registers[operand3];
                if(flags){
                    cFlag = ((result < registers[operand2]) || (result < registers[operand3]));
                    vFlag = (static_cast<int32_t>(registers[operand2]) > 0 && static_cast<int32_t>(registers[operand3]) < 0 && static_cast<int32_t>(result) < 0) || (static_cast<int32_t>(registers[operand2]) < 0 && static_cast<int32_t>(registers[operand3]) > 0 && static_cast<int32_t>(result) > 0);
                }
            }
            registers[operand1] = result;
        }
        else if(operation == "XOR" && !operand1String.empty() && !operand2String.empty()){
            //XOR
            if(operand3String[0] == '#'){
                result = registers[operand2] ^ operand3;
            }
            else{
                result = registers[operand2] ^ registers[operand3];
            }
            registers[operand1] = result;
        }
        else if(operation == "MOV" && !operand1String.empty() && !operand2String.empty()){
            //MOV
            if(operand2String[0] == '#'){
                result = operand2;
            }
            else{
                result = registers[operand2];
            }
            registers[operand1] = result;
            operand3String.clear();

        }
        else if(operation == "CMP" && !operand1String.empty() && !operand2String.empty()){
            flags = true;
            //CMP
            if(operand2String[0] == '#'){
                result = registers[operand1] - operand2;
                cFlag = ((result < registers[operand1]) || (result < operand2));
                vFlag = (static_cast<int32_t>(registers[operand1]) > 0 && static_cast<int32_t>(operand2) < 0 && static_cast<int32_t>(result) < 0) || (static_cast<int32_t>(registers[operand1]) < 0 && static_cast<int32_t>(operand2) > 0 && static_cast<int32_t>(result) > 0);
            }
            else{
                result = registers[operand1] - registers[operand2];
                cFlag = ((result < registers[operand1]) || (result < registers[operand2]));
                vFlag = (static_cast<int32_t>(registers[operand1]) > 0 && static_cast<int32_t>(registers[operand2]) < 0 && static_cast<int32_t>(result) < 0) || (static_cast<int32_t>(registers[operand1]) < 0 && static_cast<int32_t>(registers[operand2]) > 0 && static_cast<int32_t>(result) > 0);
            }
            
            operand3String.clear();
        }
        else if(operation == "TST" && !operand1String.empty() && !operand2String.empty()){
            flags = true;
            //TST
            if(operand2String[0] == '#'){
                result = registers[operand1] & operand2;
            }
            else{
                result = registers[operand1] & registers[operand2];
            }
            operand3String.clear();  
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
        std::cout << '\t' << operand1String << " " << operand2String << " " << operand3String << ": 0x" << std::hex << std::uppercase << result << '\n';
        for(int i = 0; i < 8; i++){
            std::cout << "R" << i << ": 0x" << registers[i] << '\t';    
        }

        std::cout << std::endl << "N: " << nFlag << " Z: " << zFlag << " C: " << cFlag << " V: " << vFlag << '\n'; 
    }

    //CLOSE FILE
    file.close();

    return 0;
}
