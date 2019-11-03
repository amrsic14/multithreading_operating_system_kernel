#include <dos.h>
#include "IVTEntry.h"

IVTEntry* IVTEntry::entries[256];

IVTEntry::IVTEntry(IVTNo ivtNo, PInterrupt newInterrupt){
	this->myEvent = 0;
	this->ivtNo = ivtNo;
	this->oldInterrupt = 0;
	this->newInterrupt = newInterrupt;

#ifndef BCC_BLOCK_IGNORE
	this->oldInterrupt = getvect(ivtNo);
	setvect(ivtNo, newInterrupt);
#endif

	IVTEntry::entries[ivtNo] = this;
}

IVTEntry::~IVTEntry(){
	IVTEntry::entries[ivtNo] = 0;
	if(myEvent != 0) delete myEvent;
}

void IVTEntry::signalEvent(){
	myEvent->signal();
}
