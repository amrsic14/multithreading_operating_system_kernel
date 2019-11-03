#include "SysCall.h"
#include <iostream.h>
#include "KrnlThrd.h"
#include "timer.h"
#include "SCHEDULE.h"
#include "lock.h"
#include "dos.h"

volatile unsigned int tmpBP, tmpSP, tmpSS;
volatile PCB* SysCall::runningKernelThread = 0;
Arguments* SysCall::arguments = new Arguments();

void SysCall::initializeRoutine(){
#ifndef BCC_BLOCK_IGNORE
	setvect(0x63, SysCall::systemCall);
	setvect(0x61, SysCall::systemCallReturn);
#endif
}

volatile unsigned offf, sgg;

void interrupt SysCall::systemCall(...){

	Lock::sysCallRoutine = 1;
	asm sti;

#ifndef BCC_BLOCK_IGNORE
	asm	mov offf, cx;
	asm	mov sgg, dx;
	SysCall::arguments = (Arguments*) MK_FP(sgg, offf);
#endif

	asm mov tmpSP, sp;
	asm mov tmpBP, bp;
	asm mov tmpSS, ss;

	PCB::runningPCB->sp = tmpSP;
	PCB::runningPCB->bp = tmpBP;
	PCB::runningPCB->ss = tmpSS;

	if (runningKernelThread == 0){
		cout << "KernelThread not initialized!\n";
	}

	tmpSP = runningKernelThread->sp;
	tmpBP = runningKernelThread->bp;
	tmpSS = runningKernelThread->ss;

	asm mov sp, tmpSP;
	asm mov bp, tmpBP;
	asm mov ss, tmpSS;

}

void interrupt SysCall::systemCallReturn(...){

	asm sti;
	asm mov tmpSP, sp;
	asm mov tmpBP, bp;
	asm mov tmpSS, ss;

	runningKernelThread->sp = tmpSP;
	runningKernelThread->bp = tmpBP;
	runningKernelThread->ss = tmpSS;

	if(Lock::dispatchRequest == 1){
		Lock::dispatchRequest = 0;
		if ((PCB::runningPCB->state != BLOCKED) && (PCB::runningPCB != PCB::idlePCB) && (PCB::runningPCB->state != SLEEPING) && (PCB::runningPCB->state != FINISHED)){
			Scheduler::put((PCB*)PCB::runningPCB);
		}
		PCB::runningPCB = Scheduler::get();
		if ( PCB::runningPCB == 0){
			PCB::runningPCB = PCB::idlePCB;
		}
		Timer::tickCounter = 0;
	}

	tmpSP = PCB::runningPCB->sp;
	tmpBP = PCB::runningPCB->bp;
	tmpSS = PCB::runningPCB->ss;

	asm mov sp, tmpSP;
	asm mov bp, tmpBP;
	asm mov ss, tmpSS;

	Lock::sysCallRoutine = 0;
}
