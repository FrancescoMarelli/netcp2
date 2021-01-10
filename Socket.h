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
#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <linux/limits.h> 
/**************************************************************************/
/*  struct sockaddr_in {                                                  */
/*     sa_family_t    sin_family;       siempre debe valer AF_INET        */
/*     in_port_t      sin_port;         número de puerto en               */
/*                                      orden de bytes de la red.         */
/*     struct in_addr sin_addr;         dirección de IP                   */
/*   };                                                                   */
/*                                                                        */
/*      Dirección IP                                                      */
/*   struct in_addr {                                                     */
/*     uint32_t   s_addr;           dirección en orden de bytes de la red.*/
/*   };                                                                   */
/**************************************************************************/
class Socket {
 public:
    struct Message {
    std::array<char, PATH_MAX> filename;  
    std::array<uint8_t, 1024> data; 
    // size_t data_size;
    // size_t file_size;
    };

 private:
  int fd_;

 public:
  explicit Socket(const sockaddr_in& address);
  ~Socket();

  int FdError(int fd);
  int BindError(int result);
  int SendtoError(int result);
  int ReceiveFromError(int result);

  void send_to(void* ptr,  sockaddr_in& address);
  void send_to( std::array<char, PATH_MAX>& data, sockaddr_in& address);
  void receive_from(void* ptr, sockaddr_in& address);
  void receive_from(std::array<uint8_t, 1024>& data, sockaddr_in& address);

  inline int GetFd() { return fd_; }
  void SetMessage(std::string&);
};

sockaddr_in make_ip_address(int port, const std::string& ip_address =
                                                         std::string()) {
    sockaddr_in  local_address{};
    local_address.sin_family = AF_INET;
    local_address.sin_port = port;

    if (ip_address.empty()) {
     local_address.sin_addr.s_addr = htonl(INADDR_ANY);  // IP de router / pc
    } else {
        int ip = stoi(ip_address);
        local_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // 127.0.0.1
    }
    return local_address;
}


#endif  // SOCKET_H_
