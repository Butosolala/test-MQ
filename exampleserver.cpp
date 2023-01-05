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

class Server
{

public:
  void start()
  {
    boost::interprocess::message_queue::remove("Message_queue");            // erase Previous Message Queue
    boost::interprocess::message_queue MQ(boost::interprocess::create_only, // create message queue
                                          "Message_queue",                  // name
                                          1,                                // max message number
                                          4                                 // max message size
    );

    std::string command = "./Prog ";
    boost::thread parser(&Server::parseProg, this);
    boost::process::child c(command.c_str(), boost::process::std_out > is);
    c.detach();
    
    int received_number = 0;
    unsigned int priority;
    boost::interprocess::message_queue::size_type received_size;
    MQ.receive(&received_number, sizeof(received_number), received_size, priority);
    std::cout << "received_number = " << received_number
              << ", received_size = " << received_size
              << ", priority = " << priority << std::endl;
  }

private:
  void parseProg()
  {
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
      Server server;
      server.start();
    }
    else if (command == "1" || command == "stop")
    {
      break;
    }
  }

  return 0;
}