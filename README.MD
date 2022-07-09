# PROCESO DE IMPLEMENTACIÓN DEL PROBLEMA DEL PRODUCTOR Y CONSUMIDOR A TRAVÉS DE UN MONITOR 
En este readme se mostrará el proceso de implementación para solucionar el problema de productores y consumidores.

## Explicación del problema a resolver
El problema habla de que tenemos un productor que produce letras de la 'a' a la 'z' en orden aleatorio, y un consumidor que consume esas letras. Las letras producidas se almacenan en un buffer y cuando el productor está ingresando una letra al buffer, el consumidor no puede retirar letras del mismo. Para solucionar este problema, en clase se quedó en crear un monitor que lo que hace es hacer de mediador y el monitor sería el que realice las acciones de ingresar o retirar letras en el buffer, mientras el productor y el consumidor piden la realización del proceso. 


## Pasos realizados para la solución del problema
* Lo primero que se hizo es crear una clase monitor que tenga los procesos de producir y consumir que serán los de ingresar y sacar letras del buffer respectivamente. Como podemos ver sus métodos son públicos ya que tiene parámetros externos y al ser privada no se podría acceder a este método. A continuación se muestra como se implementó la clase monitor.

```
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
```

* Luego se crearon las clases Productor y Consumidor que tienen como atributos que usarán al monitor que es al cuál le harán la petición de que realize algún proceso, luego está el thread que ya se sabe que se encarga de ejecutar nuestro hilo. Y finalmente un id que guarda el número de consumidor y productor. Se muestra a continuación las clases Productor y Consumidor:
```
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
```
* Por último tenemos el main, que lo que hace es crear un productor, un consumidor y un monitor. Luego con un for creamos los hilos y con el otro los iniciamos como se ve en las siguientes líneas:

```
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
```

## Sucesos inesperados al realizar la implementación
En este caso primero intenté usar para el buffer la librería **#include <vector>**, pero lamentablemente por errores de memoria terminó siendo ineficiente. Daba el siguiente error.

![Cat](https://github.com/JoseAlfredoGrados/finalmonitores/blob/9ca9b044019885ec281d7c9a5e896792767e9216/CapturaSO.JPG.png)

Por suerte después se encontró la librería **#include <queue>** que es especialista en colas por lo que no iba a tener esos problemas.

## Conclusiones

* Si el problema te lo dan textualmente y te dice que cosas usar, intenta buscar librerías que cumplan los requisitos ya que si usas como yo la librería vector que en sí se especializa en vectores y no en colas, terminarás teniendo un gran desconcierto al ver error en el código.

* Por último decir que este problema es uno muy interesante, ya que se le puede agregar muchas más funcionalidades como un límite de letras que puedan ser producidas o consumidas, entre muchas más.

