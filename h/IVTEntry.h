#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "kernelEv.h"

typedef void interrupt (*PInterrupt)(...);

class IVTEntry {
public:

	IVTEntry(IVTNo ivtNo, PInterrupt newInterrupt);

	~IVTEntry();

	void signalEvent();

	static IVTEntry* entries[256];

	volatile PInterrupt oldInterrupt;
	PInterrupt newInterrupt;

	IVTNo ivtNo;

	KernelEv* myEvent;
};

#endif
