#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <stdlib.h>
#include <string>
#include <boost/process.hpp>
#include "message.hpp"



void start() {
  std::string command = "./Prog ";
  boost::process::ipstream is;
  boost::process::child c(command.c_str(), boost::process::std_out > is);
  std::string messageQueueName = std::to_string(c.id());

  std::cout << "Server: messageQueueName = " << messageQueueName.c_str() << std::endl;
  c.detach();
  boost::interprocess::message_queue::remove(messageQueueName.c_str());
    try
    {
      
      boost::interprocess::message_queue mq(
          boost::interprocess::create_only,
          messageQueueName.c_str(), 100, 1000);//
      boost::interprocess::message_queue::size_type recvd_size;
      unsigned int priority;

      info message;

      std::stringstream iss;
      std::string serialized_string;
      serialized_string.resize(1000);
      mq.receive(&serialized_string[0], 1000, recvd_size, priority);

      iss << serialized_string;

      boost::archive::text_iarchive ia(iss);

      ia >> message;
      std::cout << message.number << std::endl;
      std::cout << message.text << std::endl;
    }
    catch (boost::interprocess::interprocess_exception &e)
    {
      boost::interprocess::message_queue::remove(messageQueueName.c_str());
      std::cerr << "server exception: " << e.what() << '\n';
    }

    try
    {
      
      boost::interprocess::message_queue mq(
          boost::interprocess::open_only,
          messageQueueName.c_str());//
      boost::interprocess::message_queue::size_type recvd_size;
      unsigned int priority;

      infoAlt message;

      std::stringstream iss;
      std::string serialized_string;
      serialized_string.resize(1000);
      mq.receive(&serialized_string[0], 1000, recvd_size, priority);

      iss << serialized_string;

      boost::archive::text_iarchive ia(iss);

      ia >> message;
      std::cout << message.preText << std::endl;
      std::cout << message.number << std::endl;
      std::cout << message.postText << std::endl;
    }
    catch (boost::interprocess::interprocess_exception &e)
    {
      boost::interprocess::message_queue::remove(messageQueueName.c_str());
      std::cerr << "server exception: " << e.what() << '\n';
    }
    
  boost::interprocess::message_queue::remove(messageQueueName.c_str());

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