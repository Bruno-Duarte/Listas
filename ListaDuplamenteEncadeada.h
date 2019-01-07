//***********************************************************
// Autor: F. Bruno Duarte
// Em: 07/01/2019
//***********************************************************

#ifndef LISTADUPLAMENTEENCADEADA_H
#define LISTADUPLAMENTEENCADEADA_H

#include <iostream>

// definição da class NoDuplo
template <class Type>
class NoDuplo {
public:	
	NoDuplo(){ }
	
	NoDuplo(NoDuplo<Type> *ant, NoDuplo<Type> *prox, 
					const Type& info){
		this->ant = ant;
		this->prox = prox;
		this->info = info;
    	}
    	
	void setInfo(Type info){ this->info = info; }
	Type getInfo() const{ return info; }
	void setAnt(NoDuplo<Type> *ant) { this->ant = ant; }
	NoDuplo<Type>* getAnt() const{ return ant; };
	void setProx(NoDuplo<Type> *prox){ this->prox = prox; }
	NoDuplo<Type>* getProx() const{ return prox; }

	~NoDuplo(){ };
private:
	Type info;
	NoDuplo<Type> *ant, *prox;
};

// definição da classe ListaDuplamenteEncadeada
template<class Type>
class ListaDuplamenteEncadeada {
public:
	ListaDuplamenteEncadeada() { criaLista(); }

	void criaLista(){ inicio = NULL; fim = NULL; }
	
	NoDuplo<Type>* getInicio(){ return inicio; }
	
	void add(const Type&);
	void addOrdenado(const Type&);
	void addFim(const Type&);
	void print() const;
	void reversePrint() const;
	
	bool isEmpty() const{ return inicio == NULL; }
	
 	bool search(const Type&) const;
	int size() const;
	void removeInicio();
	void remove(const Type&);
	void removePosicao(int);
	void removeFim();
	void free();

	~ListaDuplamenteEncadeada<Type>(){ free(); }
private:
	NoDuplo<Type> *inicio, *fim;
};

// inserção no início
template<class Type>
void ListaDuplamenteEncadeada<Type>::add(const Type& i){
	NoDuplo<Type> *novo = new NoDuplo<Type>(NULL, inicio, i);

	if(inicio == NULL)
		inicio = fim = novo;
	else {
		inicio->setAnt(novo);
		inicio = novo;
	}
}

// inserção dos elementos ordenadamente
template<class Type>
void ListaDuplamenteEncadeada<Type>::addOrdenado(const Type& i){
	NoDuplo<Type> *novo = new NoDuplo<Type>(NULL, inicio, i);

	if(isEmpty())
		inicio = fim = novo;
	else { // procura onde inserir
		NoDuplo<Type> *ant = NULL, *atual = inicio;

		while(atual != NULL && atual->getInfo() < i){
			ant = atual;
			atual = atual->getProx();
		}

		if(atual == inicio){ // insere início
			inicio->setAnt(novo);
			inicio = novo;
		} else {
			novo->setProx(ant->getProx());
			novo->setAnt(ant);
			ant->setProx(novo);
			fim = novo;
			if(atual != NULL){
				atual->setAnt(novo);
				fim = atual;
			}
		}
	}
}

// inserção no final
template<class Type>
void ListaDuplamenteEncadeada<Type>::addFim(const Type& i){
	NoDuplo<Type> *novo = new NoDuplo<Type>(inicio, NULL, i);

	if(inicio == NULL){ // se a lista estiver vazia
		inicio = novo;
		fim = novo;
	} else {
		novo->setAnt(fim);
		fim->setProx(novo);
		fim = novo;
	}
}

// imprime os elementos da lista
template<class Type>
void ListaDuplamenteEncadeada<Type>::print() const{
	if(inicio == NULL) return;

	NoDuplo<Type> *aux = inicio;

	while(aux != NULL){
		std::cout << aux->getInfo() << " ";
		aux = aux->getProx();
	}
	std::cout << std::endl;
}

// imprime os elementos da lista na ordem inversa
template<class Type>
void ListaDuplamenteEncadeada<Type>::reversePrint() const{
	if(fim == NULL) return;

	NoDuplo<Type> *aux = fim;

	while(aux != NULL){
		std::cout << aux->getInfo() << " ";
		aux = aux->getAnt();
	}
	std::cout << std::endl;
}

// busca por um elemento na lista
template<class Type>
bool ListaDuplamenteEncadeada<Type>::search(const Type& i) const{
	for(NoDuplo<Type>* n = inicio; n != NULL; n = n->getProx()){
		if(n->getInfo() == i) return true;
	}
	return false; // não achou o elemento
}

// retorna o tamanho da lista
template<class Type>
int ListaDuplamenteEncadeada<Type>::size() const {
	if(inicio == NULL) return 0;

	int cont = 0;
	NoDuplo<Type> *p = inicio;

	while(p != NULL){
		cont++;
		p = p->getProx();
	}
	return cont;
}

// remove um elemento do início da lista
template<class Type>
void ListaDuplamenteEncadeada<Type>::removeInicio(){
	if(inicio == NULL){
		return;
	}
	NoDuplo<Type> *temp = inicio;
	inicio = temp->getProx();
	if(temp->getProx() != NULL)
		temp->getProx()->setAnt(NULL);
	delete temp;
}

// remove um elemento do meio lista
template<class Type>
void ListaDuplamenteEncadeada<Type>::remove(const Type& i){
	NoDuplo<Type> *ant = NULL;
	NoDuplo<Type> *p = inicio;

	// procura elemento na lista, guardando anterior
	while(p != NULL && p->getInfo() != i){
		ant = p;
		p = p->getProx();
	}

	if(p == NULL){
		return; // não achou o elemento: lista permanece inalterada
	}

	// retira elemento do encadeamento
	if(inicio == p){
		// retira elemento do início
		inicio = p->getProx();
	} else {
		// remove elemento do meio da lista
		ant->setProx(p->getProx());
	}

	// verifica se é o último elemento
	if(p->getProx() != NULL)
		p->getProx()->setAnt(ant);
	delete p;
}

// remove elemento na posição passada no parâmetro
template<class Type>
void ListaDuplamenteEncadeada<Type>::removePosicao(int pos){
	if(pos < 0 || pos > size() - 1) return;

	NoDuplo<Type> *ant = NULL, *p = inicio; int cont = 0;

	while(p != NULL && cont < pos){
		ant = p;
		p = p->getProx();
		cont += 1;
	}

	if(pos == 0){
		// retira elemento do início
		inicio = p->getProx();
	} else {
		// retira elemento do meio da lista
		ant->setProx(p->getProx());
	}

    // verifica se é o último elemento
	if(p->getProx() != NULL)
		p->getProx()->setAnt(ant);

	delete p;
}

// remove último elemento
template<class Type>
void ListaDuplamenteEncadeada<Type>::removeFim(){
	if(inicio == NULL){
		return;
	}
	NoDuplo<Type> *temp = fim;
	if(temp == inicio){ // se tiver somente um nó
		temp = inicio;
		inicio = temp->getProx();
		fim = temp->getAnt();
	} else {
		fim = temp->getAnt();
		fim->setProx(NULL);
	}
	delete temp;
}

// libera a lista
template<class Type>
void ListaDuplamenteEncadeada<Type>::free(){
	while(inicio != NULL){
		NoDuplo<Type> *temp = inicio;
		inicio = inicio->getProx();
		delete temp;
	}
	delete inicio;
}

#endif
