#include <iostream>
#include <iomanip>
#include "server_socket.hpp"


int main(int argc, const char* argv[]) {
  ServerSocket server = ServerSocket(8003, 0); //INADDR_ANY == int(0)
  server.run_socket();
  return 0;
}