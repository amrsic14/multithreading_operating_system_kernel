#include "event.h"
#include "kernelEv.h"
#include "dos.h"
#include "lock.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"

ID KernelEv::evIdGenerator = 0;
EvQueue KernelEv::allEvents;

KernelEv::KernelEv(IVTNo ivtNo, Event* myEv){
	id = ++evIdGenerator;
	this->myEv = myEv;
	this->myEv->id = id;
	this->value = 0;
	this->ivtNo = ivtNo;
	this->myThread = (PCB*)PCB::runningPCB;
	this->blockedThread = 0;
	IVTEntry::entries[ivtNo]->myEvent = this;
	KernelEv::allEvents.put(this);
}

KernelEv::~KernelEv(){
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, IVTEntry::entries[ivtNo]->oldInterrupt);
#endif

	if(IVTEntry::entries[ivtNo] != 0) IVTEntry::entries[ivtNo]->myEvent = 0;
	KernelEv::allEvents.remove(id);
}

void KernelEv::wait(){
	if(myThread == PCB::runningPCB){
		if(value == 1){
			value = 0;
		}
		else{
			block();
		}
	}
}

void KernelEv::signal(){
	if(blockedThread == 0){
		value = 1;
	}
	else{
		deblock();
	}
}

void KernelEv::deblock(){
	if(blockedThread != 0){
		blockedThread->state= READY;
		Scheduler::put(blockedThread);
		blockedThread = 0;
		Lock::dispatchRequest = 1;
		if(!Lock::sysCallRoutine) dispatch();
	}
}

void KernelEv::block(){
	PCB::runningPCB->state = BLOCKED;
	blockedThread = (PCB*)PCB::runningPCB;
	Lock::dispatchRequest = 1;
}
