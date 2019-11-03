#include "MainThrd.h"
#include "PCB.h"

MainThread::MainThread(int argc, char** argv) : Thread() {
	this->argc = argc;
	this->argv = argv;
	this->ret_value = -1;
}

void MainThread::run(){
	ret_value = userMain(argc,argv);
}

int MainThread::returned(){
	waitToComplete();
	return ret_value;
}

MainThread::~MainThread(){
	waitToComplete();
}
