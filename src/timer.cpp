#include <dos.h>
#include "pcb.h"
#include "lock.h"
#include "timer.h"
#include <iostream.h>
#include "IdleThrd.h"
#include "schedule.h"
#include "KernlSem.h"


void interrupt (*Timer::oldRoutine)(...) = 0;

void Timer::initializeRoutine(){
#ifndef BCC_BLOCK_IGNORE
	Timer::oldRoutine = getvect(0x8);
	setvect(0x8,Timer::timer);
#endif
}

void Timer::restoreRoutine(){
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,Timer::oldRoutine);
#endif
}

extern void tick();

volatile unsigned int tempBP, tempSP, tempSS;
PCB* waked_up = 0;
unsigned int Timer::tickCounter = 0;

void interrupt Timer::timer(...){

	tick();

	if (PCB::runningPCB->timeSlice) Timer::tickCounter++;

	if (Lock::dispatchRequest == 0) Timer::oldRoutine();

	if ((!Lock::sysCallRoutine)&&(Lock::dispatchRequest || ((PCB::runningPCB->timeSlice == tickCounter) && PCB::runningPCB->timeSlice))){
		asm mov tempSP, sp;
		asm mov tempBP, bp;
		asm mov tempSS, ss;

		PCB::runningPCB->sp = tempSP;
		PCB::runningPCB->bp = tempBP;
		PCB::runningPCB->ss = tempSS;

		if ((PCB::runningPCB->state != BLOCKED) && (PCB::runningPCB != PCB::idlePCB) && (PCB::runningPCB->state != SLEEPING) && (PCB::runningPCB->state != FINISHED)){
			Scheduler::put((PCB*)PCB::runningPCB);
		}

		if ( !(PCB::runningPCB = Scheduler::get()) ){
			PCB::runningPCB = PCB::idlePCB;
		}

		tempSP = PCB::runningPCB->sp;
		tempBP = PCB::runningPCB->bp;
		tempSS = PCB::runningPCB->ss;

		asm mov sp, tempSP;
		asm mov bp, tempBP;
		asm mov ss, tempSS;

		PCB::runningPCB->state = RUNNING;
		tickCounter = 0;

	}

	//wake up sleeping threads
	if(Lock::dispatchRequest == 0){
		PCB::sleeping.wakeUp();
	}

	if(!Lock::sysCallRoutine) Lock::dispatchRequest = 0;
	else Lock::dispatchRequest = 1;
}

