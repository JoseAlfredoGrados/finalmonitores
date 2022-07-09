#include<iostream>

using namespace std;

// g++ monitor00.cpp

#define NUM_HILOS 10

int cont=0;

class Monitor {
	public:
	void inc(){
		for(int i=0; i<10; i++){
			cont++;
		}
		//return cont;
	}
};

class Hilo {
	private:
		Monitor* monitor;
			
	public:
		Hilo(){
			monitor = new Monitor;
		}
		void run(){
			monitor->inc();
			cout<<cont<<endl;
		}
};

int main() {

	Hilo* hilos[NUM_HILOS];
	
	int i;
	for(i=0; i<NUM_HILOS; i++) {
		hilos[i] = new Hilo;
	}
	
	for(i=0; i<NUM_HILOS; i++) {
		hilos[i]->run();
	}

	return 0;
}
