#ifndef REGISTERS_H
#define REGISTERS_H

class Registers
{
    private:
        uint32_t memory;
        char flags[3];
    public:
        Registers();

        //setters
        void setFlags(char*);
        void setValue(uint32_t);

    
    //getters
        char* getFlag() const;
        uint32_t getValue() const;
};

#endif