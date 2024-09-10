 
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

#define PORT 4506
#define BUFFER 1024 

class Client_Data_Stream{
    private: 
        int ClientSocket; 
        static sockaddr_in ClientAddress;
        
    public:

        // Config Client Socket
        void Config_Socket(short InternetProtocol, uint16_t Port, in_addr_t Adress){
            ClientAddress.sin_family = InternetProtocol; // AF_INET
            ClientAddress.sin_port = htons(Port);
            ClientAddress.sin_addr.s_addr = Adress; //INADDR_ANY
            
        }
        
        // Create Socket
        Client_Data_Stream(int Domain, int TypeSocket, int InternetProtocol){
            ClientSocket = socket(Domain, TypeSocket, InternetProtocol);// InternetProtocol = 0, Domain = AF_INET, TypeSocket = SOCK_STREAM,
        }
        //using Sever_Data_Stream::Sever_Data_Stream
        
        ~Client_Data_Stream(){
            close(ClientSocket);
        }
        
        void Client_Conneted(){
            if((connect(ClientSocket, (struct sockaddr*)&ClientAddress, sizeof(ClientAddress))) < 0){
                cerr << "Client Connected Error: " << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        
        
};

int main()
{



 return 0;
}
 
