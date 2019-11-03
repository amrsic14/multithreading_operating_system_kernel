#include "idleThrd.h"
#include <iostream.h>

IdleThread::IdleThread() : id(0), Thread() {}

void IdleThread::run(){
	volatile unsigned useless = 100;
	/*while(useless){
		for(int i = 10; i < 10000; i++, useless++ ){
			i--;
			useless--;
			for(int j = 0; j < 10000; j++){
				j++;
				j--;
			}
		}
	}*/
	while(1);
}

