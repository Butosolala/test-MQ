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

boost::process::ipstream is;

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

void start() {
  std::string command = "./Prog ";
  
  boost::process::child c(command.c_str(), boost::process::std_out > is);
  boost::thread parser(&parseProg);

  c.detach();
  parser.detach();
}

int main()
{
   while (true)
    {
        std::string command;
        std::cout << "Please enter the rpc you want to make (start(0), stop(1)):" << std::endl;
        std::getline(std::cin, command);

        if (command == "0" || command == "start")
        {
            std::cout << "start" << std::endl;
            start();
        }
        else if (command == "1" || command == "stop") 
        {
          std::cout << "stop" << std::endl;
          break;
        }
    } 

  return 0;
}