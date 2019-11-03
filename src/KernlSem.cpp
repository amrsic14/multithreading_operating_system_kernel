#include "lock.h"
#include "KernlSem.h"
#include "PCB.h"
#include "Schedule.h"
#include "Semaphor.h"

SemQueue KernelSem::allSemaphores;
ID KernelSem::semIdGenerator = 0;

KernelSem::KernelSem(int init, Semaphore *mySem){
	value = init;
	id = ++semIdGenerator;
	this->mySem = mySem;
	this->mySem->id = id;
	KernelSem::allSemaphores.put(this);
}

KernelSem::~KernelSem(){
	while(waitList.isEmpty() == 0) unblock(); //unblock blocked threads on this semaphore
	KernelSem::allSemaphores.remove(id);
}

int KernelSem::wait(int toBlock){

	int ret = 0;

	if(toBlock != 0){
		if(--value < 0){
			block();
			ret = 1;
		}
	}
	else{
		if(value <= 0){
			return -1;
		}
		else{
			value--;
		}
	}

	return ret;
}

void KernelSem::signal(){
	if(++value <= 0){
		if(waitList.isEmpty() == 0){
			unblock();
		}
	}
}

void KernelSem::block(){
	waitList.put((PCB*)PCB::runningPCB);
	PCB::runningPCB->state = BLOCKED;
	Lock::dispatchRequest = 1;
}

void KernelSem::unblock(){
	if(waitList.isEmpty() == 0){
		PCB* unblockedPCB = waitList.remove();
		if(unblockedPCB != 0){
			unblockedPCB->state = READY;
			Scheduler::put(unblockedPCB);
		}
	}
}

