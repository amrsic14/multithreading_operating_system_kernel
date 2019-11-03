#include "Queue.h"
#include "PCB.h"

Queue::Queue() : head(0), tail(0), capacity(0) {}

PCB* Queue::remove(){
	if(head == 0) return 0;

	Elem* old = head;
	if(head == tail) tail = 0;
	head = head->next;
	PCB* ret = old->pcb;
	delete old;
	--capacity;

	return ret;
}


PCB* Queue::getByIndx(int index){
	Elem* curr = head;
	int i = 0;

	while(curr && i < index){
		curr = curr->next;
		i++;
	}

	return (curr ? curr->pcb : 0);
}

PCB* Queue::get(ID id){
	Elem* curr = head;

	while(curr){
		if (curr->pcb->id == id)
			break;
		curr = curr->next;
	}


	return (curr ? curr->pcb : 0);
}

void Queue::put(PCB* p){

	Elem* newElem = new Elem(p);

	if(head == 0)
		head = newElem;
	else
		tail->next = newElem;

	tail = newElem;
	++capacity;

}

PCB* Queue::remove(ID id){
	Elem* curr = head;
	Elem* prev = 0;
	PCB* returnVal = 0;

	while(curr){
		if (curr->pcb->id == id)
			break;
		prev = curr;
		curr = curr->next;
	}

	if(curr == 0) return returnVal;

	if(prev){

		prev->next = curr->next;
		if(curr == tail) tail = prev;

	}else{
		head = head->next;
	}

	returnVal = curr->pcb;
	--capacity;

	delete curr;

	return returnVal;
}

int Queue::isEmpty(){
	return (head == 0) ? 1 : 0;
}


