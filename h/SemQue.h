#ifndef OS1_2018_SEM_QUEUE_H_
#define OS1_2018_SEM_QUEUE_H_

class KernelSem;

typedef int ID;

class SemQueue {
public:

	struct Elem{
		KernelSem* kSem;
		Elem* next;
		Elem(KernelSem* p){ this ->kSem = p; next = 0; }
	};

	SemQueue();

	void put (KernelSem* p);

	KernelSem* remove();

	KernelSem* get(ID id);

	KernelSem* getByIndx(int index);

	KernelSem* remove(ID id);

	int isEmpty();

	unsigned int QueueSize(){ return capacity;}

private:

	Elem *head, *tail;
	unsigned int capacity;
};

#endif
