 
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Transmit.h"

using namespace std;

#define PORT 4506
#define BUFFER 1024 

class Transmit_Data{
    protected: 
        char ReceiveBuffer[BUFFER] = { 0 };
        char SendBuffer[BUFFER] = "Response from sever"; // ?? 
    public: 
        virtual void Send_Data(int Mode) = 0;
        virtual void Receive_Data(int Mode) = 0;
        // virtual void Edit_Send() = 0;
};

class Sever_Data_Stream : public Transmit_Data{
    private:
         int SeverSocket, ClientSocket; // Create socket prototype
         sockaddr_in ServerAddress;
         static Sever_Data_Stream* Object;
         string Name_Object;
         
         // Create socket connection
         Sever_Data_Stream(int Domain, int TypeSocket, int InternetProtocol, string Name){
            SeverSocket = socket(AF_INET, SOCK_STREAM, InternetProtocol); // InternetProtocol = 0, Domain = AF_INET, TypeSocket = SOCK_STREAM,
            Name_Object = Name;
         }
        
    public:
       
        // Prevent Create a Copy of Construction
         Sever_Data_Stream(const Sever_Data_Stream&) = delete;

        // Prevent Assign 
        void operator=(const Sever_Data_Stream&) = delete;

        // Close socket connection
        virtual ~Sever_Data_Stream(){
            close(ClientSocket);
            close(SeverSocket);
            delete Object;
         }
    
    
        // Setting Sever Socket prototype
        virtual void Config_Socket(short InternetProtocol, uint16_t Port, in_addr_t Adress){
            ServerAddress.sin_family = InternetProtocol; // AF_INET
            ServerAddress.sin_port = htons(Port);
            ServerAddress.sin_addr.s_addr = Adress; //INADDR_ANY
        }

        // Binding local socket addresss to socket prototype address
        void Sever_Bind(){
            if((bind(SeverSocket, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress))) < 0){
                 cerr << "Socket Binding Error: " << endl;
                 close(SeverSocket);
                 exit(EXIT_FAILURE);
             }
         }

 
         // Waiting connect from clients
        void Sever_Listen(int NumberConnect){
            if(listen(SeverSocket, NumberConnect) < 0 ){ // max number connects= 0-4095
            cerr << "Sever Listen Error" << endl;
            close(SeverSocket);
            exit(EXIT_FAILURE);
            }
         }

        // Accept Connection with clients
        void Sever_Accept(){
             if((ClientSocket = accept(SeverSocket, nullptr, nullptr)) < 0){
             cerr << "Sever Accept Error" << endl;
             close(SeverSocket);
             exit(EXIT_FAILURE);
            }
        }
        
        // Send Text
        void Send_Data(int Mode) override{
            if((send(ClientSocket, SendBuffer, strlen(SendBuffer), Mode)) < 0){
                cerr << "Send Message Error" << endl;
                return;
            }
            else
                cout << "Sever: " << SendBuffer << endl;
        }
        
        void Receive_Data(int Mode) override{
            if((recv(ClientSocket, ReceiveBuffer, sizeof(ReceiveBuffer), Mode) < 0)){
                cerr << "Receive Message Error: " << endl;
                return;
            }
            else 
                cout << "Client: " << ReceiveBuffer << endl;
        }
        
        // Create Method
        static  Sever_Data_Stream* Create_Object(string Name){
            if(nullptr == Object){
                Object = new Sever_Data_Stream(AF_INET, SOCK_STREAM, 0, Name);
            }
            return Object;
        }

};

// User Golbal Variable
Sever_Data_Stream* Sever_Data_Stream::Object = nullptr;


int main()
{
 
 return 0;
}
 
