// Copyright : Francesco Marelli, Universidad de La Laguna
// University of La Laguna
// Computer Science Degree
// Subject : Sistemas Operativos
// Second Course
// Developer/Student : Francesco Marelli
// email: alu0101161730@ull.edu.es
// Multithreas Netcp : C++ programming practice
// Professor: Jonay Tómas Toledo Torres
// Date: 03/01/2021
// Last Modification : 09/01/2021
#ifndef SOCKET_CC_
#define SOCKET_CC_

#include "Socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <string>
#include <sys/mman.h>


Socket::Socket(const sockaddr_in& address) {
    fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    FdError(fd_);
    std::string ip;
    make_ip_address(htons(0), ip);
    int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
                      sizeof(address));
    BindError(result);
}

Socket::~Socket() {
    close(fd_);
}

int Socket::FdError(int fd) {
    if (fd < 0) {
      std::cerr << "no se pudo crear el socket: " << strerror(errno) << '\n';
      return 3;
    }
    return fd;
}

int Socket::BindError(int result) {
    if (result < 0) {
        std::cerr << "falló bind: " << '\n';
        return 5;
    }
    return result;
}

int Socket::SendtoError(int result) {
  if (result < 0) {
        std::cerr << "falló sendto: " << std::strerror(errno) << '\n';
        return 6;
    }
    return result;
}

int Socket::ReceiveFromError(int result) {
    if (result < 0) {
      std::cerr << "falló recvfrom: " << std::strerror(errno) << '\n';
      return 8;
    }
    return result;
}

// Send all message
void Socket::send_to(void* ptr, sockaddr_in& address) {
    int result = sendto(fd_, &ptr, sizeof(ptr), 0,
                 reinterpret_cast<const sockaddr*>(&address), sizeof(address));
    SendtoError(result);
}

// // Send message info
void Socket::send_to(std::array<char, PATH_MAX>& data, sockaddr_in& address) {
    int result = sendto(fd_, &data, sizeof(data), 0,
                 reinterpret_cast<const sockaddr*>(&address), sizeof(address));
    SendtoError(result);
 }

// Receive message
void Socket::receive_from(void* ptr, sockaddr_in& address) {
    socklen_t src_len = sizeof(address);
    int result = recvfrom(fd_, &ptr, sizeof(ptr), 0, reinterpret_cast<sockaddr*>(&address), &src_len);
    // Convert la dirección IP como entero de 32 bits a  una cadena
    char* remote_ip = inet_ntoa(address.sin_addr);
    // Recuperamos el puerto del remitente en el orden adecuado para nuestra CPU
     int remote_port = ntohs(address.sin_port);
    // std::cout << "El sistema " << remote_ip << " : ";
    // std::cout << remote_port << " envió el mensaje " << ptr << std::endl;
}

// Receive file info
void Socket::receive_from(std::array<uint8_t, 1024>& data, sockaddr_in&  address) {
    socklen_t src_len = sizeof(address);
    int result = recvfrom(fd_, &data, sizeof(data), 0, reinterpret_cast<sockaddr*>(&address), &src_len);
    // Convert la dirección IP como entero de 32 bits a  una cadena
    char* remote_ip = inet_ntoa(address.sin_addr);
    // Recuperamos el puerto del remitente en el orden adecuado para nuestra CPU
    int remote_port = ntohs(address.sin_port);
    // std::cout << "El sistema " << remote_ip << " : ";
    // std::cout << remote_port << " envió el mensaje " << data << std::endl;
}

#endif  // SOCKET_CC_

