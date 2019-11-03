#include "event.h"
#include "dos.h"
#include "SysCall.h"

unsigned off_, sg_;

Event::Event(IVTNo ivtNo): id(0) {
	Arguments* args = new Arguments();
	args->sysCallID = EventConstructor;
	args->ivtNo = ivtNo;
	args->event = this;

#ifndef BCC_BLOCK_IGNORE
	unsigned off_ = FP_OFF(args);
	unsigned sg_ = FP_SEG(args);

	asm	mov cx, off_;
	asm	mov dx, sg_;

	asm int 63h;
#endif
	delete args;
}

Event::~Event(){
	Arguments* args = new Arguments();
	args->sysCallID = EventDestructor;
	args->evID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off_ = FP_OFF(args);
	unsigned sg_ = FP_SEG(args);

	asm	mov cx, off_;
	asm	mov dx, sg_;

	asm int 63h;
#endif
	delete args;
}

void Event::wait(){
	Arguments* args = new Arguments();
	args->sysCallID = EventWait;
	args->evID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off_ = FP_OFF(args);
	unsigned sg_ = FP_SEG(args);

	asm	mov cx, off_;
	asm	mov dx, sg_;

	asm int 63h;
#endif
	delete args;
}

void Event::signal(){
	Arguments* args = new Arguments();
	args->sysCallID = EventSignal;
	args->evID = this->id;

#ifndef BCC_BLOCK_IGNORE
	unsigned off_ = FP_OFF(args);
	unsigned sg_ = FP_SEG(args);

	asm	mov cx, off_;
	asm	mov dx, sg_;

	asm int 63h;
#endif
	delete args;
}
