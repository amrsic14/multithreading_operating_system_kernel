#ifndef OS1_2018_MAINTHRD_H_
#define OS1_2018_MAINTHRD_H_

#include "Thread.h"

class MainThread: public Thread {
public:

	MainThread(int argc, char** argv);

	~MainThread();

	int returned();

private:

	int argc;
	char** argv;

	void run();

	int ret_value;
};

int userMain(int, char**);

#endif
