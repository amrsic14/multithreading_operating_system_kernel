#include "SysCall.h"
#include "KernlSem.h"
#include <iostream.h>
#include "lock.h"

KernelThread::KernelThread() {
	myPCB = new PCB(4096, 0, this);
	myPCB->createKernelStack();
}

KernelThread::~KernelThread() {
	if(myPCB != 0) delete myPCB;
}

void KernelThread::kernelWrapper(KernelThread* runningthrd) {
	runningthrd->run();
}

void KernelThread::run() {

	while (1) {
		switch (SysCall::arguments->sysCallID) {
		case ThreadConstructor: {
			new PCB(SysCall::arguments->stackSize, SysCall::arguments->timeSlice, SysCall::arguments->thread);
			break;
		}
		case ThreadDestructor: {
			PCB::allPCBs.get(SysCall::arguments->threadID)->waitToComplete();
			PCB* toDelete = PCB::allPCBs.remove(SysCall::arguments->threadID);
			delete toDelete;
			break;
		}
		case ThreadStart: {
			PCB::allPCBs.get(SysCall::arguments->threadID)->start();
			break;
		}
		case ThreadWaitToComplete: {
			PCB::allPCBs.get(SysCall::arguments->threadID)->waitToComplete();
			break;
		}
		case ThreadSleep: {
			PCB::sleep(SysCall::arguments->timeToSleep);
			break;
		}
		case Dispatch: {
			Lock::dispatchRequest = 1;
			break;
		}
		case SemaphoreConstructor: {
			new KernelSem(SysCall::arguments->semInit, SysCall::arguments->sem);
			break;
		}
		case SemaphoreDestructor: {
			KernelSem* toDelete = KernelSem::allSemaphores.remove(SysCall::arguments->semID);
			delete toDelete;
			break;
		}
		case SemaphoreWait: {
			SysCall::arguments->semRet = KernelSem::allSemaphores.get(SysCall::arguments->semID)->wait(SysCall::arguments->toBlock);
			break;
		}
		case SemaphoreSignal: {
			KernelSem::allSemaphores.get(SysCall::arguments->semID)->signal();
			break;
		}
		case SemaphoreVal: {
			SysCall::arguments->semRet = KernelSem::allSemaphores.get(SysCall::arguments->semID)->value;
			break;
		}
		case EventConstructor: {
			new KernelEv(SysCall::arguments->ivtNo, SysCall::arguments->event);
			break;
		}
		case EventDestructor: {
			KernelEv* toDelete = KernelEv::allEvents.remove(SysCall::arguments->evID);
			delete toDelete;
			break;
		}
		case EventWait: {
			KernelEv::allEvents.get(SysCall::arguments->evID)->wait();
			break;
		}
		case EventSignal: {
			KernelEv::allEvents.get(SysCall::arguments->evID)->signal();
			break;
		}
		default: {
			cout << "InvalidOperation error!\n";
			break;
		}
		}

		SysCall::systemCallReturn();
	}
}
