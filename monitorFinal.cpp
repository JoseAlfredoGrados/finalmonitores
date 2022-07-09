#include<iostream>
#include<thread>
#include<mutex>
#include <vector>

using namespace std;

// g++ monitorFinal.cpp -lpthread

#define NUM_HILOS 10

vector<char> cola;
const char abededario[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int contador = 0;
mutex flag;

class Monitor {
	public:
	void producir(int productor){
		flag.lock();	// LOCK
		int j = rand() % 26;
		char producido=abededario[j];
		cola.push_back(producido);
		cout<<"Productor número "<<productor<<" ha producido: "<<producido<<"\n";
		flag.unlock();	// UNLOCK		
	}
	
	void consumir(int consumidor){
	  flag.lock();	// LOCK
		int aleatorio;
		aleatorio = rand() % 26;
		char consumido=abededario[aleatorio];
		cola.pop_back();
		cout<<"Consumidor ->"<<consumidor<<"<- consumió: "<<consumido<<endl;
		flag.unlock();	// UNLOCK		
	}
};

class Productor {
	private:
		Monitor* monitor;
		thread t;
		int id;
		void run_thread(){			
			for (int i=1; true; i++) {
			    monitor->producir(id);		//	RUN
			}
		}
			
	public:
		Productor(Monitor* mon, int idd){
			id = idd;
			monitor = mon;
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
			for (int i=1; true; i++) {
			    monitor->consumir(id);		//	RUN
			}
		}
			
	public:
		Consumidor(Monitor* mon, int idd){
			id = idd;
			monitor = mon;
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
	for(i=0; i<NUM_HILOS; i++) {
		productor[i] = new Productor(monitor, i);
		consumidor[i] = new Consumidor(monitor, i);
	}
	
	for(i=0; i<NUM_HILOS; i++) {
		productor[i]->join_thread();	//	START
	    consumidor[i]->join_thread();	//	START
	}

	return 0;
}