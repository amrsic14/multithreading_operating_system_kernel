#ifndef _event_h_
#define _event_h_

typedef unsigned char IVTNo;
class KernelEv;
typedef int ID;

class Event {
public:

	Event(IVTNo ivtNo);

	~Event();

	void wait();

protected:

	friend class KernelEv;

	void signal(); // can call KernelEv

private:

	ID id;

	friend KernelEv;
};


#include "IVTEntry.h"

#define PREPAREENTRY(ivtno, routineflag)\
	void interrupt newRoutine##ivtno(...); \
	IVTEntry ivtentry##ivtno(ivtno, newRoutine##ivtno); \
	void interrupt newRoutine##ivtno(...){\
	ivtentry##ivtno.signalEvent(); \
if (routineflag == 1)\
	ivtentry##ivtno.oldInterrupt(); \
}

#endif

