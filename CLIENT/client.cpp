#include "client.hpp"

void Authorization(struct DATA_CLIENT *__data__)
{
    std::cout << "Username: " << std::flush;
    std::cin >> __data__->username;
    std::cout << "Password: " << std::flush; 
    std::cin >> __data__->password;
    std::cout << "Weclome "  + __data__->username + "! You can chatting now!\n" << std::flush;
}


int main([[maybe_unused]]int argc,[[maybe_unused]]char **argv)
{
    struct sockaddr_in client_address;
    struct DATA_CLIENT client_data;
    int sock_client = 0;
    int connection_client = 0;
    int send_client = 0;
    int recv_client = 0;
    int close_client = 0;
    const size_t buffer_size = 2048;
    char msg[buffer_size] = {0};


    sock_client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(sock_client < 0)
    {
        std::cerr << "SOCKET CLIENT INIT ERROR\n" << std::flush;
        return -1;
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(8080);
    client_address.sin_addr.s_addr = inet_addr("127.0.0.1");

       
        connection_client = connect(sock_client,(struct sockaddr*)&client_address,sizeof(client_address));
    
        if(connection_client < 0)
        {
            perror((char*)&errno);
            std::cout << "CONNECT CLIENT:ERROR\n" << std::flush;
            return -1;
        } 

        Authorization(&client_data);

  for(;;)
  {     
        //переделать жеско , супер костылек 
        char msg_between[buffer_size];
        std::cout << client_data.username + ": " << std::flush;
        std::cin >> msg;
        std::cin.getline(msg_between,buffer_size);
        strcat(msg,msg_between);


        send_client = send(sock_client,msg,sizeof(msg),0);

        if(send_client < 0)
        {
            std::cout << "SEND CLIENT:ERROR\n" << std::flush;
            return -1;
        }
        recv_client = recv(sock_client,msg,sizeof(msg),0);

        if(recv_client > 0)
        {
            std::cout << "SERVER: " << msg << std::endl;            
        }

  }

       close_client = close(sock_client);

    return 0;
}