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
	sleep(5);

	boost::interprocess::message_queue MQ(boost::interprocess::open_only, // open message queue
                                        "Message_queue"// name
                                       );
	int sent_number = 123;
	MQ.send (&sent_number, sizeof(sent_number), 0);

	printf("END test main\n");
	return 0;
}
