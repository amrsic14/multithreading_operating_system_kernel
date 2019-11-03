#include "sleepQue.h"
#include "SCHEDULE.H"
#include <iostream.h>

sleepQueue::sleepQueue() : front_(0), rear_(0), capacity_(0) {}

//push to Queue
void sleepQueue::put(PCB* t, Time timeToSleep) {

	if(timeToSleep == 0) return;

	if (front_ == 0) {
		front_ = new node(t, timeToSleep);
		rear_ = front_;
	}
	else {
		node* curr = front_;
		node* prev = 0;
		unsigned int time = timeToSleep;

		while((curr != 0) && (curr->time_ < time)){
			time -= curr->time_;
			prev = curr;
			curr = curr->next_;
		}

		if(curr == front_){
			node* newnode = new node(t, timeToSleep, front_);
			front_ = newnode;

			prev = newnode;
			curr->time_ -= prev->time_;

		}else if(curr == 0){
			rear_->next_ = new node(t, time);
			rear_ = rear_->next_;

		}else{
			node* newnode = new node(t, time, curr);
			curr->time_ -= newnode->time_;
			prev->next_ = newnode;
		}

	}

	capacity_++;
}

//pop from Queue
PCB* sleepQueue::get() {

	node *k = 0;

	if (isEmpty()) {
		cout << "sleepQUEQUE EMPTY" << endl;
		return 0;
	}
	else {

		if (front_ == rear_) {
			k = front_;
			front_ = rear_ = 0;
		}
		else {
			k = front_;
			front_ = front_->next_;
		}
		capacity_--;

	}

	PCB* ret = k->data_;
	delete k;
	return ret;
}

//delete Queue
void sleepQueue::clear() {
	while (front_ != 0) {
		node *curr = front_;
		front_ = front_->next_;
		delete curr;
	}

	rear_ = 0;
	front_ = 0;
	capacity_ = 0;
}

void sleepQueue::updateTime(){
	if(front_->time_ > 0) front_->time_--;
}

void sleepQueue::wakeUpAll(){
	while (PCB::sleeping.isEmpty() == 0) {
		PCB* waked_up = PCB::sleeping.get();
		waked_up->state = READY;
		Scheduler::put(waked_up);
	}
}

void sleepQueue::wakeUp(){
	if (capacity_ > 0){
		PCB* waked_up = 0;
		updateTime();
		while ((capacity_ > 0) && (front_->time_ == 0)) {
			waked_up = get();
			waked_up->state = READY;
			Scheduler::put(waked_up);
		}
	}
}

