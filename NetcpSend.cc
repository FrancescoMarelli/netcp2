// Copyright : Francesco Marelli, Universidad de La Laguna
// University of La Laguna
// Computer Science Degree
// Subject : Sistemas Operativos
// Second Course
// Developer/Student : Francesco Marelli
// email: alu0101161730@ull.edu.es
// Netcp : c++ programming practice
// Professor: Jonay Tómas Toledo Carrillo
// Date: 09/12/2020
// Last Modification : 09/12/2020
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <string>
#include <vector>
#include <array>

#include "Socket.cc"
#include "File.cc"

const bool READ = false;

int main(int argc, char* argv[]) {
   // Creación de Direcciones
    std::string ip = "127.0.0.1";
    sockaddr_in local_address = make_ip_address(0, ip);
    sockaddr_in remote_address = make_ip_address(53551, ip);

    // Creación Socket de envío
    Socket send_socket(local_address);
     
    // Gestión fichero
    std::string input = argv[1];
    File file(input, READ, 1048576);
    Socket::Message message;
    // Inicializar messages
    send_socket.send_to(message.filename, remote_address);  // info inicial
    void *ptr;

    //  Mando mensaje a IP remota
    // Bucle for que desmapea y mapea segun se haya superado la memoria 
    for (int i = 0; i < 1048576; i += 1024) {
        ptr = (char*)file.data() + i;
        send_socket.send_to(ptr, remote_address);
    }
return 0;
}
