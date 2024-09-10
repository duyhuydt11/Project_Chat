

#ifndef TRANSMIT_H
#define TRANSMIT_H

// User Libraries
#include<iostream>


// User Define
#define PORT 4506
#define BUFFER 1024 

// set namespace
using namespace std;

class Transmit_Data{
    protected: 
        char ReceiveBuffer[BUFFER] = { 0 };
        char SendBuffer[BUFFER] = "Response from sever"; // ?? 
    public: 
        virtual void Send_Data(int Mode) = 0;
        virtual void Receive_Data(int Mode) = 0;
        // virtual void Edit_Send() = 0;
};

#endif

