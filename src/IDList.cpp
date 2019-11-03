#include "IDList.h"
#include "thread.h"

ThreadList::ThreadList() : head(0), tail(0), capacity(0) {}

ID ThreadList::remove(){
	if(head == 0) return 0;

	Elem* old = head;
	if(head == tail) tail = 0;
	head = head->next;
	ID ret = old->id;
	delete old;
	--capacity;

	return ret;
}


ID ThreadList::getByIndx(int index){
	Elem* curr = head;
	int i = 0;

	while(curr && i < index){
		curr = curr->next;
		i++;
	}

	return (curr ? curr->id : 0);
}

ID ThreadList::get(ID id){
	Elem* curr = head;

	while(curr){
		if (curr->id == id)
			break;
		curr = curr->next;
	}


	return (curr ? curr->id : 0);
}

void ThreadList::put(ID p){

	Elem* newElem = new Elem(p);

	if(head == 0)
		head = newElem;
	else
		tail->next = newElem;

	tail = newElem;
	++capacity;

}

ID ThreadList::remove(ID id){
	Elem* curr = head;
	Elem* prev = 0;
	ID returnVal = 0;

	while(curr){
		if (curr->id == id)
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

	returnVal = curr->id;
	--capacity;

	delete curr;

	return returnVal;
}

int ThreadList::isEmpty(){
	return (head == 0) ? 1 : 0;
}


