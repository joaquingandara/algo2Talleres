class Node 
{
public:
	Node* next;
	int data;
};

using namespace std;

//Encapsular comportamiento
//Cada nodo esta enlazado con el siguiente
class LinkedList
{
	public:
		int length; // Long de la lista
		Node* head; // Variable al puntero del primer elemento de la lista. 

		LinkedList();
		~LinkedList();
		void add(int data);
		void print();
}

//Implementacion constructor.
LinkedList::LinkedList(){
	: length(0),head(null){} //Es mejor inicializar las  variables para no abusar de valores por defecto
}


//Implementar una lista de enteros , para resaltar las operaciones new/delete sin lidiar con los problemas de Templates.

/*La idea es que recibimos un dato (data). 
	Paso 1 : encapsular el dato en un nodo.
	Paso 2: "enganchar" ese nodo en la lista
*/
void LinkedList::add (int data){
//Paso 1:
	Node* node = new Node(); // Creo el nodo
	node->data = data; // Asigno el valor al nodo
//Paso 2:
	node->next = this->head; //Que el nodo actual apunte al comienzo de la lista
	this->head = node; // Que el comienzo de la lista sea este nuevo nodo
	this->length++; // Aumentamos el tamaño de la lista.
}

/*Destructor
	*La cantidad de new tiene que ser igual a la cantidad de delete
	*Idea rapida para pensar el destructor.
	*Tener en cuenta que c++ no sabe recorrer este linkedList porque es algo que creamos nosotros y le pusimos un nombre. 
*/
LinkedList::~LinkedList()
{
	Node <T>* temp = head ; // Generamos el temp
	
	while(temp != NULL){
		temp = temp->next // Avanzo en temp
		delete (head); //Estoy borrando el head del heap
		head = temp; // Actualizo head.
	}
}


//Constructor mas util.

class Lista {
	public: 
		Lista();
		~Lista();
		void agregar(const int& x);	
	private:
		void_destruir();
		struc Nodo {
			Nodo(const T& elem);
				int valor;
				Nodo* siguiente;
		};
		Nodo *_primero;
}

void Lista::agregar(const int& x){
	Nodo* nuevo = new Nodo(x)
	nuevo->siguiente= _primero
	_primero=nuevo;
}

Lista::Nodo::(const int& elem)
: valor(elem),prox(NULL){};

//Ejemplo de uso
int main()
{
	lista s;
	s.agregar(40);
	s.agregar(50);
	s.agregar(60);
	cout << s << endl;
	return 0;
}