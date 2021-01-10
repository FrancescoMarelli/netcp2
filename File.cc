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
#include "File.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include "Socket.cc"

File::File(const std::string& filename, bool writeonly = false,
                                        size_t size = 0) {
  std::ifstream file_aux;
  file_aux.open(filename);
  std::string line;
  const char* filename_char = filename.c_str();
  // Bloqueo archivo
  lockf(fd_, F_LOCK, 0);
  // Caso escribir en memoria
  if (writeonly) {
      fd_ = open("ouput.txt", O_WRONLY);
      length_ = lseek(fd_, 0, SEEK_END);
      ftruncate(fd_, size);
      memory_mapped_ = mmap(
        NULL,
        length_,
        PROT_READ,
        MAP_SHARED,
        fd_,
        0);
  } else {
    // Caso leer
      fd_ = open(filename_char, O_RDONLY);
      ftruncate(fd_, size);
      memory_mapped_ = mmap(
        NULL,
        size,
        PROT_READ,
        MAP_SHARED,
        fd_,
        0);
        length_ = size;
  }
}

File::~File() {
  munmap(memory_mapped_, length_);
  lockf(fd_, F_ULOCK, 0);
  close(fd_);
}

