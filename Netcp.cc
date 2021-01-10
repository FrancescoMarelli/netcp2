// Copyright : Francesco Marelli, Universidad de La Laguna
// University of La Laguna
// Computer Science Degree
// Subject : Sistemas Operativos
// Second Course
// Developer/Student : Francesco Marelli
// email: alu0101161730@ull.edu.es
// Multithreas Netcp : C++ programming practice
// Professor: Jonay Tómas Toledo Carrillo
// Date: 03/01/2021
// Last Modification : 09/01/2021
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <pthread.h>
#include <exception>

#include "Socket.cc"
#include "File.cc"

const bool READ = false;
const bool WRITE = true;

void* sock_send(void* filename) {
    // Creación de Direcciones
    std::string ip = "127.0.0.1";
    sockaddr_in local_address = make_ip_address(0, ip);
    sockaddr_in remote_address = make_ip_address(53551, ip);

    // Creación Sockets
    Socket send_socket(local_address);

    // Conversión void*->string
    std::string *conv_filename = static_cast<std::string*>(filename);
    std::string aux = *conv_filename;
    delete conv_filename;

    File file(aux, READ, 1048576);
    Socket::Message message;
    aux.copy(message.filename.data(), sizeof(filename));
    send_socket.send_to(message.filename, remote_address);  // info inicial
    void *ptr_aux;
    // Mando mensaje a IP remota
    // Bucle for que desmapea y mapea segun se haya superado la memoria ??
    for (int i = 0; i < 1048576; i += 1024) {
        ptr_aux = (char*)file.data() + i;
        send_socket.send_to(ptr_aux, remote_address);
    }
    return 0;
}

void* sock_receive() {
    // Creación de Direcciones
    std::string ip = "127.0.0.1";
    sockaddr_in remote_address = make_ip_address(0, ip);
    sockaddr_in local_address = make_ip_address(53551, ip);
    // Creación Sockets
    Socket receiving_socket(local_address);
    Socket::Message message{};
    File file_write("output.txt", WRITE, sizeof(message));

    receiving_socket.receive_from(message.data, remote_address);
    void* ptr;
    for(int i = 0; i < 1048576; i+= 1024) {
        ptr = (char*)file_write.data() + i;
        receiving_socket.receive_from(ptr, remote_address);
    }
    return 0;
}

int main(int argc, char* argv[]){
    
    std::string filename = argv[1];
    char aux_char[sizeof(filename)];
    strcpy(aux_char, filename.c_str());
    //Socket::Message message = { (char)aux_char };

    pthread_t thread1;
    pthread_create(&thread1, NULL, sock_send, (void*)aux_char); 
    pthread_join(thread1, NULL);
    pthread_t thread2; // (&sock_receive);
    pthread_create(&thread2, NULL, sock_receive, NULL );
    pthread_detach(thread2);

    return 0;
}

// int main(int argc, char* argv[]) {

//      std::string filename = argv[1];
//     // Creación de Direcciones
//     std::string ip = "127.0.0.1";
//     sockaddr_in local_address = make_ip_address(0, ip);
//     sockaddr_in remote_address = make_ip_address(53551, ip);
//     // Creación Sockets
//     Socket send_socket(local_address);
//     Socket receiving_socket(local_address);

//     bool quit = false;
//     while(!quit) {
//         std::vector<std::pair<std::thread *, std::string>> my_threads;
//         std::cout << "Netcp multihilo" << std::endl;
//         std::cout << "1. Envíar el fichero " << std::endl;
//         std::cout << "2. Recibir el fichero" << std::endl;
//         std::cout << "0. Salir del pograma" << std::endl;
//         std::cout << "Introducir un comando: " << std::endl;

//         int command;
//         std::cin >> command;

//         switch(command){
//         case 0 :
//             for( int i = 0; i < my_threads.size(); ++i) {
//                 my_threads[i].first->detach();
//                 my_threads[i].first->join();
//             }
//             quit = true;
//             exit(-1);
//             break;
//         case 1:
//             int fdfile = open (filename.c_str(), O_RDWR, S_IRWXO);
//             std::thread * thread1;
//             std::pair < std::thread *, std::string> aux (std::make_pair(thread1, filename));
//             my_threads.push_back(aux);
//             thread1 = new std::thread(&sockets, send_socket.GetFd(), remote_address, filename, fdfile, thread1);
//             break;
//         default:
//             break;
//         }
//     }
//}
