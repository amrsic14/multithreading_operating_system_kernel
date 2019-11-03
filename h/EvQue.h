#ifndef OS1_2018_Ev_QUEUE_H_
#define OS1_2018_Ev_QUEUE_H_

class KernelEv;

typedef int ID;

class EvQueue {
public:

	struct Elem{
		KernelEv* kEv;
		Elem* next;
		Elem(KernelEv* p){ this ->kEv = p; next = 0; }
	};

	EvQueue();

	void put (KernelEv* p);

	KernelEv* remove();

	KernelEv* get(ID id);

	KernelEv* getByIndx(int index);

	KernelEv* remove(ID id);

	int isEmpty();
	unsigned int QueueSize(){ return capacity;}

private:
	Elem *head, *tail;
	unsigned int capacity;
};

#endif
