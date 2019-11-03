#ifndef OS1_2018_QUEUE_H_
#define OS1_2018_QUEUE_H_

class PCB;

typedef int ID;

class Queue{
public:

	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p){ this ->pcb = p; next = 0; }
	};

	Queue();

	void put (PCB* p);

	PCB* remove();

	PCB* get(ID id);

	PCB* getByIndx(int index);

	PCB* remove(ID id);

	int isEmpty();

	unsigned int QueueSize(){ return capacity;}

private:
	Elem *head, *tail;
	unsigned int capacity;
};

#endif
