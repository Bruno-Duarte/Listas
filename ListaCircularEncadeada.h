//***********************************************************
// Autor: F. Bruno Duarte
// Em: 07/01/2019
//***********************************************************

#ifndef LISTACIRCULARENCADEADA_H
#define LISTACIRCULARENCADEADA_H

#include <iostream>

// definição da classe NoCircular
template <class Type>
class NoCircular {
public:
	NoCircular(){ }
	NoCircular(NoCircular<Type>* prox, const Type& info){
		this->prox = prox;
		this->info = info;
	}

	Type getInfo() const{ return info; }
	void setInfo(Type info){ this->info = info; }
	NoCircular<Type>* getProx() const{ return prox; }
	void setProx(NoCircular<Type> *prox){ this->prox = prox; }

	~NoCircular(){ }
private:
	Type info;
	NoCircular<Type> *prox;
};

// definição da classe ListaCircularEncadeada
template <class Type>
class ListaCircularEncadeada {
public:
	ListaCircularEncadeada() { prim = NULL; }

	NoCircular<Type>* getPrim() { return prim; }

	void add(const Type&);
	void addOrdenado(const Type&);
	void addFim(const Type&);
	void print() const;

	bool isEmpty() const{ prim == NULL; }

	bool search(const Type&) const;
	int size() const;
	void removeInicio();
	void remove(const Type&);
	void removePosicao(int);
	void removeFim();
	void free();

	~ListaCircularEncadeada<Type>(){ free(); }
private:
	NoCircular<Type>* prim;
};

// inserção no início
template<class Type>
void ListaCircularEncadeada<Type>::add(const Type& i){
	NoCircular<Type> *novo = new NoCircular<Type>(prim, i);

	if(prim == NULL){ // lista vazia: insere início
		prim = novo;
		novo->setProx(novo); // aponta para si própio
	} else {
		NoCircular<Type> *aux = prim;

		while(aux->getProx() != prim)
			aux = aux->getProx();

		aux->setProx(novo);
		//novo->setProx(prim);
		prim = novo;
	}
}

// adiciona elementos ordenadamente
template<class Type>
void ListaCircularEncadeada<Type>::addOrdenado(const Type& i){
	NoCircular<Type> *novo = new NoCircular<Type>(prim, i);

	if(prim == NULL) { // insere no início
		prim = novo;
		novo->setProx(novo);
	} else { // continua procurando
		if(prim->getInfo() > i){ // insere no início
			NoCircular<Type> *atual = prim;

			while(atual->getProx() != prim) // procura o último
				atual = atual->getProx();
			atual->setProx(novo);
			prim = novo;
		}
	}
	NoCircular<Type> *ant = prim, *atual = prim->getProx();

	while(atual != prim && atual->getInfo() < i){
		ant = atual;
		atual = atual->getProx();
	}
	ant->setProx(novo);
	novo->setProx(atual);
}

// adiciona no final da lista
template<class Type>
void ListaCircularEncadeada<Type>::addFim(const Type& i){
	NoCircular<Type> *novo = new NoCircular<Type>(prim, i);

	if(prim == NULL){ // lista está vazia
		prim = novo;
		novo->setProx(novo);
	} else {
		NoCircular<Type> *aux = prim;

		while (aux->getProx() != prim)
			aux = aux->getProx();

		aux->setProx(novo);
		//novo->setProx(prim);
	}
}

// imprime os elementos da lista
template<class Type>
void ListaCircularEncadeada<Type>::print() const{
	if(prim == NULL) return;

	NoCircular<Type> *aux = prim;

	do {
		std::cout << aux->getInfo() << " ";
		aux = aux->getProx();
	} while(aux != prim);
	std::cout << std::endl;
}

// busca por um elemento na lista
template<class Type>
bool ListaCircularEncadeada<Type>::search(const Type& i) const{
	NoCircular<Type> *aux = prim;

	do {
		aux = aux->getProx();
		if(aux->getInfo() == i)
			return true;
	} while(aux != prim);
	return false; // não achou o elemento
}

// imprime os elementos da lista
template<class Type>
int ListaCircularEncadeada<Type>::size() const{
	if(prim == NULL) return 0;

	NoCircular<Type> *aux = prim;
	int cont = 0;

	do {
		cont += 1;
		aux = aux->getProx();
	} while(aux != prim);

	return cont;
}

// remove elemento do início da lista
template<class Type>
void ListaCircularEncadeada<Type>::removeInicio(){
	if(prim == NULL) return;

	if(prim == prim->getProx()){ // lista fica vazia
		delete prim;
		prim = NULL;
	} else {

		NoCircular<Type> *atual = prim;

		while(atual->getProx() != prim) // procura o último
			atual = atual->getProx();

		NoCircular<Type> *temp = prim;
		atual->setProx(temp->getProx());
		prim = temp->getProx();
		delete temp;
	}
}

// remove um elemento qualquer da lista
template <class Type>
void ListaCircularEncadeada<Type>::remove(const Type& i){
	if(prim == NULL) return;

	NoCircular<Type> *no = prim;

	if(no->getInfo() == i){
		removeInicio();
	} else {

		NoCircular<Type> *atual = prim;
		do {
			atual = atual->getProx();
		} while(atual->getProx() != prim); // procura o último

		NoCircular<Type> *no = prim;
		atual->setProx(no->getProx());
		prim = no->getProx();
		delete no;
		return;
	}

	NoCircular<Type> *ant = no;
	no = no->getProx();

	while(no != prim && no->getInfo() != i){
		ant = no;
		no = no->getProx();
	}

	if(no == prim) return; // não encontrado
	ant->setProx(no->getProx());
	delete no;
}

// remove elemento na posição passada no parâmetro
template<class Type>
void ListaCircularEncadeada<Type>::removePosicao(const int pos){
	if(pos < 0 || pos > size() - 1)
		return;

	if(pos == 0){
		removeInicio();
	} else if (pos == size() - 1){
		removeFim();
	} else {
		NoCircular<Type> *ant = NULL, *p = prim;
		int cont = 0;

		while(cont < pos){
			ant = p;
			p = p->getProx();
			cont += 1;
		}
		ant->setProx(p->getProx());
		delete p;
	}
}

// remove elemento do final da lista
template<class Type>
void ListaCircularEncadeada<Type>::removeFim(){
	if(prim == NULL) return;

	if(prim == prim->getProx()){ // lista fica vazia
		delete prim;
		prim = NULL;
	} else {

		NoCircular<Type> *ant, *no = prim;

		while (no->getProx() != prim){ // procura o último
			ant = no;
			no = no->getProx();
		}

		ant->setProx(no->getProx());
		delete no;
	}
}

// libera a lista
template<class Type>
void ListaCircularEncadeada<Type>::free(){
	if(prim == NULL) return;

	// Inicia temp apontando para o início
	NoCircular<Type> *temp = prim;

	// Faz temp pular elementos da lista até que aponte para
	// o elemento anterior a prim
	while(temp->getProx() != prim)
		temp = temp->getProx();

	// Desaloca tudo enquanto temp não aponta para prim
	while(temp != prim){
		temp->setProx(prim->getProx());
		delete prim;
		prim = temp->getProx();
	}

	// Saiu do loop, temp finalmente aponta para prim
	// Agora só precisa desalocar o último elemento
	delete prim;
	prim = NULL;
}

#endif
