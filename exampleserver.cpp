#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <stdlib.h>
#include <string>
#include <boost/process.hpp>
#include <boost/thread.hpp>
#include "message.hpp"

class Server{

public:
void start() {
  std::string command = "./Prog ";
  boost::thread parser(&Server::parseProg, this);
  boost::process::child c(command.c_str(), boost::process::std_out > is);
  c.detach();
  parser.detach();
}

private:

void parseProg (){
  std::string line;
  while (std::getline(is, line))
  {
    std::cout << line << std::endl;
    if (line.find("END test") != std::string::npos)
    {
      break;
    }
  }
}

boost::process::ipstream is;
};

int main()
{
   while (true)
    {
        std::string command;
        std::cout << "Please enter the rpc you want to make (start(0), stop(1)):" << std::endl;
        std::getline(std::cin, command);

        if (command == "0" || command == "start")
        {
            Server Server;
            Server.start();
        }
        else if (command == "1" || command == "stop") 
        {
          break;
        }
    } 

  return 0;
}