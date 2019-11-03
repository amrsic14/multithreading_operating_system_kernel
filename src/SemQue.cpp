#include "SemQue.h"
#include "KernlSem.h"

SemQueue::SemQueue() : head(0), tail(0), capacity(0) {}

KernelSem* SemQueue::remove(){
	if(head == 0) return 0;

	Elem* old = head;
	if(head == tail) tail = 0;
	head = head->next;
	KernelSem* ret = old->kSem;
	delete old;
	--capacity;

	return ret;
}


KernelSem* SemQueue::getByIndx(int index){
	Elem* curr = head;
	int i = 0;

	while(curr && i < index){
		curr = curr->next;
		i++;
	}

	return (curr ? curr->kSem : 0);
}

KernelSem* SemQueue::get(ID idd){
	Elem* curr = head;

	while(curr){
		if (curr->kSem->id == idd)
			break;
		curr = curr->next;
	}
	if(curr) return curr->kSem;
	return 0;
}

void SemQueue::put(KernelSem* p){

	Elem* newElem = new Elem(p);

	if(head == 0)
		head = newElem;
	else
		tail->next = newElem;

	tail = newElem;
	++capacity;

}

KernelSem* SemQueue::remove(ID id){
	Elem* curr = head;
	Elem* prev = 0;
	KernelSem* returnVal = 0;

	while(curr){
		if (curr->kSem->id == id)
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

	returnVal = curr->kSem;
	--capacity;

	delete curr;

	return returnVal;
}

int SemQueue::isEmpty(){
	return (head == 0) ? 1 : 0;
}
