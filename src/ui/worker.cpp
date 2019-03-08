#include "worker.h"
#include <iostream>

Worker::Worker()
{
}

Worker::~Worker()
{

}

void Worker::process(void)
{
	int iret = g_gameboy->run();
	if (EXIT_FAILURE == iret)
	{
		error("Gameboy run failed");
	}
	emit finished();
}
