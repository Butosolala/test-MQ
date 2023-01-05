#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "message.hpp"

int main(int argc, char *argv[])
{
	printf("test main RUNNING\n");
	std::string messageQueueName = std::to_string(getpid());
	
	std::cout << "messageQueueName = " << messageQueueName.c_str() << std::endl;

	try
	{
		boost::interprocess::message_queue mq(
			boost::interprocess::open_only,
			messageQueueName.c_str());

		sleep(3);
		info message(1, "TRANS READY");
		std::stringstream oss;

		boost::archive::text_oarchive oa(oss);
		oa << message;

		std::string serialized_string(oss.str());
		mq.send(serialized_string.data(), serialized_string.size(), 0);
		
		
	}

	catch (boost::interprocess::interprocess_exception &e)
	{
		std::cerr << "client exception: " << e.what() << '\n';
	}

	try
	{
		boost::interprocess::message_queue mq(
			boost::interprocess::open_only,
			messageQueueName.c_str());

		infoAlt message("PRE OK", 1.234, "POST OK");
		std::stringstream oss;

		boost::archive::text_oarchive oa(oss);
		oa << message;

		std::string serialized_string(oss.str());
		mq.send(serialized_string.data(), serialized_string.size(), 0);
		
		
	}

	catch (boost::interprocess::interprocess_exception &e)
	{
		std::cerr << "client exception: " << e.what() << '\n';
	}
	printf("END test main\n");
	return 0;
}
