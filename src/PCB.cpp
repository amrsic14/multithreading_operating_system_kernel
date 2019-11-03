#include <dos.h>
#include "PCB.h"
#include "lock.h"
#include "schedule.h"

ID PCB::idGenerator = 1;
Queue PCB::allPCBs;
sleepQueue PCB::sleeping;

volatile PCB* PCB::runningPCB = 0;
PCB* PCB::idlePCB = 0;
PCB* PCB::kernelMainPCB = 0;


PCB::PCB(StackSize stackSize, Time timeSlice, Thread* myThread){
	bp = sp = ss = 0;
	id = idGenerator++;

	this->stackSizeInBytes = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	this->myKernelThread = 0;
	this->myThread->id = id;

	PCB::allPCBs.put(this);
	stack = 0;
	state = NEW;
}

PCB::PCB(StackSize stackSize, Time timeSlice){
	bp = sp = ss = 0;
	id = idGenerator++;

	this->stackSizeInBytes = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = 0;
	this->myKernelThread = 0;

	PCB::allPCBs.put(this);
	stack = 0;
	state = NEW;
}

PCB::PCB(StackSize stackSize, Time timeSlice, KernelThread* myKernelThread){
	bp = sp = ss = 0;
	id = idGenerator++;

	this->stackSizeInBytes = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = 0;
	this->myKernelThread = myKernelThread;

	stack = 0;
	state = NEW;
}

PCB::~PCB(){
	PCB::allPCBs.remove(id);
	if (stack != 0) delete[] stack;
}

void PCB::createStack(){

	unsigned stackElementNum = stackSizeInBytes / sizeof(unsigned);
	stack = new unsigned[stackElementNum];

#ifndef BCC_BLOCK_IGNORE
	stack[stackElementNum -1] = FP_SEG(myThread);
	stack[stackElementNum -2] = FP_OFF(myThread);
	stack[stackElementNum -5] = 0x200; // PSWI = 1
	stack[stackElementNum -6] = FP_SEG(Thread::wrapper); // SEGMENT off return address; address: SEG*16 + OFF
	stack[stackElementNum -7] = FP_OFF(Thread::wrapper); // OFFSET off return address
	stack[stackElementNum -16] = 0; // start value of base pointer
	sp = FP_OFF(stack + stackElementNum -16);
	bp = FP_OFF(stack + stackElementNum -16);
	ss = FP_SEG(stack + stackElementNum -16);
#endif
	
}

void PCB::createKernelStack(){

	unsigned stackElementNum = stackSizeInBytes / sizeof(unsigned);
	stack = new unsigned[stackElementNum];

#ifndef BCC_BLOCK_IGNORE
	stack[stackElementNum -1] = FP_SEG(myKernelThread);
	stack[stackElementNum -2] = FP_OFF(myKernelThread);
	stack[stackElementNum -5] = 0x200; // PSWI = 1
	stack[stackElementNum -6] = FP_SEG(KernelThread::kernelWrapper); // SEGMENT off return address; address: SEG*16 + OFF
	stack[stackElementNum -7] = FP_OFF(KernelThread::kernelWrapper); // OFFSET off return address
	stack[stackElementNum -16] = 0; // start value of base pointer
	sp = FP_OFF(stack + stackElementNum -16);
	bp = FP_OFF(stack + stackElementNum -16);
	ss = FP_SEG(stack + stackElementNum -16);
#endif

}

void PCB::start(){
	if (this->state == NEW){
		this->createStack();
		this->state = READY;
		Scheduler::put(this);
	}
}

void PCB::waitToComplete(){
	if (this != PCB::runningPCB && this->state != FINISHED){
		this->blockedPCBs.put((PCB*)PCB::runningPCB);
		PCB::runningPCB->state = BLOCKED;
		Lock::dispatchRequest = 1;
	}
}

void PCB::sleep(Time timeToSleep){
	PCB::runningPCB->state = SLEEPING;
	PCB::sleeping.put((PCB*)PCB::runningPCB, timeToSleep);
	Lock::dispatchRequest = 1;
}
