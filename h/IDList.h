#ifndef OS1_2018_TLIST_H_
#define OS1_2018_TLIST_H_

class Thread;

typedef int ID;

class ThreadList{
public:

	struct Elem{
		ID id;
		Elem* next;
		Elem(ID p){ this ->id = p; next = 0; }
	};

	ThreadList();

	void put (ID p);

	ID remove();

	ID get(ID id);

	ID getByIndx(int index);

	ID remove(ID id);

	int isEmpty();

	unsigned int QueueSize(){ return capacity;}

private:
	Elem *head, *tail;
	unsigned int capacity;
};

#endif
