#ifndef OS1_2018_SLEEPQUE_H_
#define OS1_2018_SLEEPQUE_H_

#include "PCB.h"
#include "thread.h"

class sleepQueue {
public:

	sleepQueue();

	~sleepQueue() { clear(); }

	void put(PCB* t, Time timeToSleep);

	PCB* get();

	int isEmpty() const { return ((capacity_ > 0) ? 0 : 1); }

	int size() const { return capacity_; }

	void updateTime();

	void wakeUpAll();

	void wakeUp();

	struct node;
	node *front_;
	node *rear_;

private:

	typedef struct node {
		PCB* data_;
		Time time_;
		node *next_;
		node(PCB* data, Time timeToSleep, node *next = 0) : data_(data), next_(next), time_(timeToSleep) {}
	} node;

	int capacity_;

	void clear();

	//copy constructor
	sleepQueue(const sleepQueue& t);

	//assignment operator
	sleepQueue& operator=(const sleepQueue &s);
};

#endif
