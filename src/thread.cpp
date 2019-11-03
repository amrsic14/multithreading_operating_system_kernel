#include "PCB.h"
#include "dos.h"
#include "lock.h"
#include "thread.h"
#include "SysCall.h"
#include "schedule.h"

Thread::Thread(StackSize stackSize, Time timeSlice): id(0) {
	Arguments* args = new Arguments();
	args->sysCallID = ThreadConstructor;
	args->stackSize = stackSize;
	args->timeSlice = timeSlice;
	args->thread = this;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

Thread::~Thread(){
	Arguments* args = new Arguments();
	args->sysCallID = ThreadDestructor;
	args->threadID = id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

void Thread::wrapper(Thread* running){
	running->run();

	_lock;

	while(!((PCB*)PCB::runningPCB)->blockedPCBs.isEmpty()){
		PCB* unblockedPCB = ((PCB*)PCB::runningPCB)->blockedPCBs.remove();
		unblockedPCB->state = READY;
		Scheduler::put(unblockedPCB);
	}

	PCB::runningPCB->state = FINISHED;
	_unlock;

	dispatch();
}

void Thread::start(){
	Arguments* args = new Arguments();
	args->sysCallID = ThreadStart;
	args->threadID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

void Thread::waitToComplete(){
	Arguments* args = new Arguments();
	args->sysCallID = ThreadWaitToComplete;
	args->threadID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

void Thread::sleep(Time timeToSleep){
	Arguments* args = new Arguments();
	args->sysCallID = ThreadSleep;
	args->timeToSleep = timeToSleep;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

void dispatch(){
	Arguments* args = new Arguments();
	args->sysCallID = Dispatch;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}
