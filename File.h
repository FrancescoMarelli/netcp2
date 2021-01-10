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
#ifndef FILE_H_
#define FILE_H_

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Socket.cc"

class File {
 private:
    std::string message_;
    Socket::Message message_m_;
    int fd_;
    size_t length_;
    void* memory_mapped_;
 public:
    explicit File(const std::string& filename, bool writeonly, size_t size);
    ~File();
    void* data() { return memory_mapped_ ; }
    std::string GetMessage() { return message_;}
    size_t GetSize() { return length_; }
};
#endif  // FILE_H_
