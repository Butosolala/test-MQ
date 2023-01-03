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
	sleep(3);
	printf("END test main\n");
	return 0;
}
