// Copyright : Francesco Marelli, Universidad de La Laguna
// University of La Laguna
// Computer Science Degree
// Subject : Sistemas Operativos
// Second Course
// Developer/Student : Francesco Marelli
// email: alu0101161730@ull.edu.es
// Netcp : c++ programming practice
// Professor: Jonay Tómas Toledo Torres
// Date: 09/12/2020
// Last Modification : 09/12/2020
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <string>

#include "Socket.cc"
#include "File.cc"

const bool WRITE = true;

int main(int argc, char* argv[]) {
    std::string ip = "127.0.0.1";

    sockaddr_in local_address = make_ip_address(53551, ip);
    sockaddr_in remote_address = make_ip_address(0, ip);
   // Creación Socket de recepción 
    Socket receiving_socket(local_address);

    receiving_socket.receive_from(message.data, local_address);
    void* ptr;
    for( int i = 0; i < 1048576; i+= 1024) {
        ptr = (char*)file_write.data() + i;
        receiving_socket.receive_from(ptr, local_address);
    }

    // Creo fichero para escribir, dimension del fichero
    File file_write("output.txt", WRITE, 10000000);

return 0;
}
