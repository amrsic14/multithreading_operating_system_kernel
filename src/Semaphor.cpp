#include "Semaphor.h"
#include "SysCall.h"
#include "dos.h"

Semaphore::Semaphore(int init): id(0) {
	Arguments* args = new Arguments();
	args->sysCallID = SemaphoreConstructor;
	args->semInit = init;
	args->sem = this;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

Semaphore::~Semaphore(){
	Arguments* args = new Arguments();
	args->sysCallID = SemaphoreDestructor;
	args->semID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}


void Semaphore::signal(){
	Arguments* args = new Arguments();
	args->sysCallID = SemaphoreSignal;
	args->semID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif
	delete args;
}

int Semaphore::wait(int toBlock){
	Arguments* args = new Arguments();
	args->sysCallID = SemaphoreWait;
	args->toBlock = toBlock;
	args->semID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif

	int ret = args->semRet;
	delete args;
	return ret;
}

int Semaphore::val() const{
	Arguments* args = new Arguments();
	args->sysCallID = SemaphoreVal;
	args->semID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off = FP_OFF(args);
	unsigned sg = FP_SEG(args);

	asm	mov cx, off;
	asm	mov dx, sg;

	asm int 63h;
#endif

	int ret = args->semRet;
	delete args;
	return ret;
}

