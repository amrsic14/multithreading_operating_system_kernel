#include "EvQue.h"
#include "kernelEv.h"

EvQueue::EvQueue() : head(0), tail(0), capacity(0) {}

KernelEv* EvQueue::remove(){
	if(head == 0) return 0;

	Elem* old = head;
	if(head == tail) tail = 0;
	head = head->next;
	KernelEv* ret = old->kEv;
	delete old;
	--capacity;

	return ret;
}


KernelEv* EvQueue::getByIndx(int index){
	Elem* curr = head;
	int i = 0;

	while(curr && i < index){
		curr = curr->next;
		i++;
	}

	return (curr ? curr->kEv : 0);
}

KernelEv* EvQueue::get(ID id){
	Elem* curr = head;

	while(curr){
		if (curr->kEv->id == id)
			break;
		curr = curr->next;
	}


	return (curr ? curr->kEv : 0);
}

void EvQueue::put(KernelEv* p){

	Elem* newElem = new Elem(p);

	if(head == 0)
		head = newElem;
	else
		tail->next = newElem;

	tail = newElem;
	++capacity;

}

KernelEv* EvQueue::remove(ID id){
	Elem* curr = head;
	Elem* prev = 0;
	KernelEv* returnVal = 0;

	while(curr){
		if (curr->kEv->id == id)
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

	returnVal = curr->kEv;
	--capacity;

	delete curr;

	return returnVal;
}

int EvQueue::isEmpty(){
	return (head == 0) ? 1 : 0;
}
