#include "MainThrd.h"
#include "IdleThrd.h"
#include "KrnlThrd.h"
#include "pcb.h"
#include "thread.h"
#include "Lock.h"
#include "iostream.h"
#include "timer.h"
#include "intLock.h"
#include "semaphor.h"
#include "user.h"
#include "schedule.h"
#include "SysCall.h"
KernelThread kThread;


int main(int argc, char** argv){

	SysCall::initializeRoutine();
	SysCall::runningKernelThread = kThread.myPCB;
	PCB::kernelMainPCB = new PCB(defaultStackSize,0);
	PCB::runningPCB = PCB::kernelMainPCB;
	Thread* idleThread = new IdleThread();
	PCB::idlePCB = PCB::allPCBs.get(idleThread->id);

	MainThread* userThread = new MainThread(argc,argv);

	idleThread->start();
	Scheduler::get();
	userThread->start();


	Timer::initializeRoutine();

	int ret = userThread->returned();

	delete userThread;

	Timer::restoreRoutine();
	PCB::idlePCB->state = FINISHED;


	delete idleThread;

	return ret;
}
