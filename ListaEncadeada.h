//***********************************************************
// Autor: F. Bruno Duarte
// Em: 07/01/2019
//***********************************************************

#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <iostream>

// definição da classe No
template <class Type>
class No {
public:
	No(){ }

	No(No<Type>* prox, const Type& info){
		this->prox = prox;
		this->info = info;
	}

	void setInfo(Type info){ this->info = info; }
	Type getInfo() const { return info; }
	void setProx(No<Type> *prox){ this->prox = prox; }
	No<Type>* getProx() const { return prox; }
	
	~No(){ }
private:
	Type info;
	No<Type> *prox;
};

// definição da classe ListaEncadeada
template <class Type>
class ListaEncadeada {
public:
	ListaEncadeada(){ criaLista(); }
	void criaLista(){ prim = NULL; }
	void setPrim(const No<Type>& n){ prim = n; }
	No<Type>* getPrim(){ return prim; }

	void add(const Type&);
	void addOrdenado(const Type&);
	void addFim(const Type&);
	void print() const;

	bool isEmpty() const{ return prim == NULL; }

	bool search(const Type&) const;
	int size() const;
	void removeInicio();
	void remove(const Type&);
	void removePosicao(int);
	void removeFim();
	void free();

	~ListaEncadeada<Type>(){ free(); }

private:
	No<Type>* prim;
	
};

// inserção no início
template<class Type>
void ListaEncadeada<Type>::add(const Type& i){
	No<Type>* novo = new No<Type>(prim, i);
	prim = novo;
}

// inserção dos elementos ordenadamente
template<class Type>
void ListaEncadeada<Type>::addOrdenado(const Type& i){
	No<Type>* novo = new No<Type>(prim, i);
	No<Type>* ant = NULL;
	No<Type>* p = prim;

	// procura elemento na lista, guardando anterior
	while(p != NULL && p->getInfo() < i){
		ant = p;
		p = p->getProx();
	}

	// encadeia o elemento
	if(ant == NULL){ // insere o elemento no início
		prim = novo;
	} else { // insere elemento no meio da lista
		novo->setProx(ant->getProx());
		ant->setProx(novo);
	}
}

// inserção no final
template<class Type>
void ListaEncadeada<Type>::addFim(const Type& i){
	No<Type> *novo = new No<Type>(prim, i);

	if(prim == NULL){ // se o nó é o primeiro
		prim = novo;
	} else {
		No<Type> *p = prim;
		// percorre até o fim da lista
		while(p->getProx() != NULL){
			p = p->getProx();
		}

		novo->setProx(NULL);
		p->setProx(novo);
	}
}

// imprime os elementos da lista
template<class Type>
void ListaEncadeada<Type>::print() const{
	if(prim == NULL) return;

	for(No<Type>* n = prim; n != NULL; n = n->getProx())
		std::cout << n->getInfo() << " ";
	std::cout << std::endl;
}

// busca por um elemento na lista
template<class Type>
bool ListaEncadeada<Type>::search(const Type& i) const{
	for(No<Type>* n = prim; n != NULL; n = n->getProx()){
		if(n->getInfo() == i) return true;
	}
	return false; // não achou o elemento
}

// retorna o tamanho da lista
template<class Type>
int ListaEncadeada<Type>::size() const{
	if(prim == NULL) return 0;
	No<Type> *p = prim; int cont = 0;

	while(p != NULL){
		cont += 1;
		p = p->getProx();
	}
	return cont;
}

// remove elemento do início da lista
template<class Type>
void ListaEncadeada<Type>::removeInicio(){
	if(prim == NULL) return;
	No<Type> *temp = prim;
	prim = temp->getProx();
	delete temp;
}

// remove um elemento do meio da lista
template<class Type>
void ListaEncadeada<Type>::remove(const Type& i){
	if(prim == NULL) return;
	
	No<Type> *ant = NULL;
	No<Type> *p = prim;

	// procura elemento na lista, guardando anterior
	while(p != NULL && p->getInfo() != i){
		ant = p;
		p = p->getProx();
	}

	// verifica se achou o elemento
	if(p == NULL){
		// não achou: matém prim da forma com está
		return;
	}

	// retira elemento
	if(ant == NULL){
	// retira elemento do início
		prim = p->getProx();
	} else {
		// retira elemento do meio da lista
		ant->setProx(p->getProx());
	}
	delete p;
}

// remove elemento na posição passada no parâmetro
template<class Type>
void ListaEncadeada<Type>::removePosicao(const int pos){
	if(pos < 0 || pos > size() - 1) return;

	No<Type> *ant = NULL, *p = prim; int cont = 0;

	while(p != NULL && cont < pos){
		ant = p;
		p = p->getProx();
		cont += 1;
	}

	if(pos == 0){
		// retira elemento do início
		prim = p->getProx();
	} else {
		// retira elemento do meio da lista
		ant->setProx(p->getProx());
	}
	delete p;
}

// remove último elemento
template<class Type>
void ListaEncadeada<Type>::removeFim(){
	if(prim == NULL) return;
	No<Type> *ant, *no = prim;

	while(no->getProx() != NULL){
		ant = no;
		no = no->getProx();
	}
	if(no == prim) // remover o primeiro?
		prim = no->getProx();
	else
		ant->setProx(no->getProx());
	delete no;
}

// libera a lista
template<class Type>
void ListaEncadeada<Type>::free(){
	No<Type>* temp;

	while(prim != NULL){
		temp = prim;
		prim = prim->getProx();
		delete temp;
	}
	delete prim;
}

#endif
