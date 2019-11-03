#ifndef OS1_2018_THREAD_H_
#define OS1_2018_THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;

typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms

typedef int ID;

class IdleThread;
class PCB; // Kernel's implementation of a user's thread

class Thread{
public:

	void start();

	void waitToComplete();

	virtual ~Thread();

	static void sleep(Time timeToSleep);

protected:

	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

	virtual void run() {}

	friend class PCB;

private:

	static void wrapper(Thread* running);

	ID id;

	friend class IdleThread;
	friend class ThreadList;
	friend int main(int argc, char** argv);
};

void dispatch();

#endif
