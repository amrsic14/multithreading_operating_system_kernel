#ifndef _KERNEL_THREAD_H_
#define _KERNEL_THREAD_H_

class KernelThread {
public:

	KernelThread();

	~KernelThread();

	void run();

	friend class PCB;

	static void kernelWrapper(KernelThread* running);

	PCB* myPCB;
};

#endif
