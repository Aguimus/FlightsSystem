#ifndef _LISTA
#define _LISTA
#include <iostream>

using namespace std;

template <class T>
struct nodo{
	T info;
	nodo<T> *sig;
};

template <class T>
class Lista{
	nodo<T> *cab;
	int tam;
	public: Lista(){
		cab = NULL;
		tam = 0;
	}
	bool listaVacia();
	int tamLista();
	void insertarInicio(T inf);
	void insertarFinal(T inf);
	bool eliminar(int pos);
	bool insertar_pos(T inf, int pos);
	T *buscar(int pos);
	void imprimirLista();
	bool limpiarLista();
};

template <class T>
bool Lista<T>::listaVacia(){
		return tam==0;
	}
	
template <class T>
int Lista<T>::tamLista(){
		return tam;
	}

template <class T>
void Lista<T>::insertarInicio(T inf){
		nodo<T> *p = new nodo<T>;
		p-> info = inf;
		p->sig = NULL;
		if(cab==NULL)
			cab=p;
		else{
			p->sig = cab;
			cab = p;			
		}
		tam++;
	}
	
template <class T>
void Lista<T>::insertarFinal(T inf){
		nodo<T> *p = new nodo<T>, *aux;
		p-> info = inf;
		p-> sig = NULL;
		if(cab==NULL)
			cab=p;
		else{
			aux = cab;
			while(aux->sig!=NULL)
				aux=aux->sig;
			aux->sig=p;			
		}
		tam++;
	}
	
template <class T>
bool Lista<T>::eliminar(int pos){
		if(listaVacia())
			return false;
		nodo<T> *aux = cab, *aux2;
		if(pos==1){
			cab=cab->sig;
			delete aux;
		}
		for(int i=1; i<pos-1; i++){
			aux = aux->sig;
		}
		aux2= aux->sig;
		aux->sig = aux2->sig;
		delete aux2;
		tam--;
		return true;
	}
	
template <class T>
bool Lista<T>::insertar_pos(T inf, int pos){
		nodo<T> *aux = new nodo<T>, *aux2 = new nodo<T>;
		if(listaVacia()){
			insertarFinal(inf);
			return true;
		}
		if(pos>=tam){
			insertarFinal(inf);
			return true;
		}
		
		for(int i=1; i<pos-1; i++){
			aux = aux->sig;
		}
		aux2->info = inf;
		aux2->sig= aux->sig;
		aux->sig = aux2;
		tam++;
		
		return true;
	}
	
template <class T>
T *Lista<T>::buscar(int pos){
	nodo<T> *aux = cab;
	
	if(listaVacia())
		return NULL;
	
	if(pos>=tam)
		pos=tam;
	
	for(int i=1; i<=pos-1; i++)
		aux = aux->sig;
	return &(aux->info);
}

template <class T>
void Lista<T>::imprimirLista(){
	nodo<T> *aux = cab;
	for(int i=0; i<tam; i++){
		cout<<aux->info<<" ";
		aux = aux->sig;
	}
	cout<<"\n";	
}

template <class T>
bool Lista<T>::limpiarLista(){
		if(listaVacia())
			return false;
		cab->sig=NULL;
		cab = NULL;
		tam=0;
		return true;
	}
#endif
