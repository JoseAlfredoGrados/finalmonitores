#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;

// g++ monitorFinal.cpp -lpthread

#define NUM_HILOS 10

queue<char> cola;
const char abededario[27] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int cont=0;

mutex flag;

class Monitor {
	public:
	void producir(int productor){
		flag.lock();	// LOCK
    
		int j = rand() % 26;
		char letra = abededario[j];
		cola.push(letra);
		cout<<"Productor número "<<productor<<" ha producido: "<<letra<<"\n";
    
		flag.unlock();	// UNLOCK		
	}
	
	void consumir(int consumidor){
	  flag.lock();	// LOCK
    
		int j = rand() % 26;
		char letra = abededario[j];
		cola.pop();
		cout<<"Consumidor número "<<consumidor<<" ha consumido: "<<letra<<"\n";
    
		flag.unlock();	// UNLOCK		
	}
};

class Productor {
	private:
		Monitor* monitor;
		thread t;
		int id;
		void run_thread(){			
			for (int i = 1; true; i++) {
			    monitor->producir(id);		//	RUN
			}
		}
			
	public:
		Productor(Monitor* monitor1, int identificadorP){
			id = identificadorP;
			monitor = monitor1;
			t = thread(&Productor::run_thread, this);
		}
		void join_thread(){
			t.join();	// START
		}
		
};

class Consumidor {
	private:
		Monitor* monitor;
		thread t;
		int id;
		void run_thread(){			
			for (int i = 1; true; i++) {
			    monitor->consumir(id);		//	RUN
			}
		}
			
	public:
		Consumidor(Monitor* monitor2, int identificadorC){
			id = identificadorC;
			monitor = monitor2;
			t = thread(&Consumidor::run_thread, this);
		}
		void join_thread(){
			t.join();	// START
		}
		
};


int main() {

	Productor* productor[NUM_HILOS];
	Consumidor* consumidor[NUM_HILOS];
	Monitor* monitor;
	
	int i;
	for(i=0; i < NUM_HILOS; i++) {
		productor[i] = new Productor(monitor, i);
		consumidor[i] = new Consumidor(monitor, i);
	}
	
	for(i=0; i < NUM_HILOS; i++) {
		productor[i]->join_thread();	//	START
	  consumidor[i]->join_thread();	//	START
	}

	return 0;
}