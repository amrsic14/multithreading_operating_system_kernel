#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "event.h"
#include "PCB.h"
#include "EvQue.h"

typedef unsigned char IVTNo;
typedef int ID;

class KernelEv {
public:

	KernelEv(IVTNo ivtNo, Event* myEv);

	~KernelEv();

	void wait();

	void signal();

	void deblock();

	void block();

	static EvQueue allEvents;

	ID id;

private:

	static ID evIdGenerator;
	unsigned int value;
	IVTNo ivtNo;
	Event* myEv;
	PCB* myThread;
	PCB* blockedThread;
};

#endif
