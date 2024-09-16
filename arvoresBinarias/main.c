// Fazendo uso de bibliotecas básicas
#include <stdio.h>
#include <stdlib.h>

// estrutura autorreferenciada
typedef struct No{
	int valor;
	int profundidade;
	int altura;
	struct No* esquerda;
	struct No* direita;
}No;

// protótipos
No* criarArvore();
No* criarNo(int valor);
No* inserirNo(No* raiz, int valor);
No* buscarNo(No* raiz, int valor);
No* removerNo(No* raiz, int valor);
No* buscarMenorValor(No* raiz);
void atualizaProfundidadeAltura(No* raiz, No* subArvore);

void imprimirEmOrdem(No* raiz);
void imprimirPreOrdem(No* raiz);
void imprimirPosOrdem(No* raiz);
void imprimirArvoreEmProfundidade(No* raiz);
void imprimirArvore(No* raiz);

void imprimirSubArvore(No* raiz, int valor);
void imprimirPercorrer(No* raiz);

// Função main inicia execução do programa
int main(){
	No* raiz =criarArvore();
    
    raiz = removerNo(raiz, 17);
    imprimirArvoreEmProfundidade(raiz);
    // imprimirPercorrer(raiz);
    // imprimirSubArvore(raiz, 19);
	return 0;
}

/*
    Função para criar uma árvore binária
*/
No* criarArvore(){
    int i; // contador do laço para (for)
	No* raiz = NULL; // declação da raiz da árvore
	int valores[16] = {15, 11, 19, 8, 9, 7, 13, 12, 14, 19, 17, 16, 18, 40, 35,42};// valores a serem inseridos na árvore para teste.

    // inserindo valores na árvore
	for(i = 0; i < 16; i++){
	    raiz = inserirNo(raiz, valores[i]);
	}
	
	return raiz;
}

/*
    Cria novo nó para a árvore, alocando a memória necessária e atribuindo o 
    valor passado pelo usuário
*/
No* criarNo(int valor){
    /*A função malloc utiliza como argumento o número de bytes a serem
    alocados e retorna um ponteiro void para a memória alocada. A função
    malloc é usada normalmente com o operador sizeof. O operador sizeof
    determina o tamanho em bytes da estrutura para a memória que está sendo
    alocada*/
	No* novoNo = (No*)malloc(sizeof(No));
	if(novoNo != NULL){
    	novoNo->valor = valor;
    	novoNo->profundidade = 0;
    	novoNo->altura = 0;
    	novoNo->esquerda = NULL;
    	novoNo->direita = NULL;
    	return novoNo;
    }
    
    printf ( "%d nao inserido. Nao existe memória disponivel. \n",valor);
    return NULL;
}

/*
    Rotina que insere valores na árvore
*/
No* inserirNo(No* raiz, int valor){
	if(raiz == NULL){
		return criarNo(valor);
	}
	
	// Se valor MENOR QUE raiz->valor, inserir valor no filho à esquerda
	if(valor < raiz->valor){
		raiz->esquerda = inserirNo(raiz->esquerda, valor);
		atualizaProfundidadeAltura(raiz, raiz->esquerda);
	}
	// Se valor MAIOR QUE raiz->valor, inserir valor no filho à direita
	else if(valor > raiz->valor){
		raiz->direita = inserirNo(raiz->direita, valor);
		atualizaProfundidadeAltura(raiz, raiz->direita);
	}
	
	// retorna a raiz modifica, exceto se o valor IGUAL A raiz->valor
	return raiz;
}

/*
    Função para atualizar a profundidade de um nó e a altura de uma (sub)árvore.
    Esses campos são utilizados para a impressão formatada da árvore.
*/
void atualizaProfundidadeAltura(No* raiz, No* subArvore){
    if(subArvore == NULL) return;
    
    subArvore->profundidade = raiz->profundidade + 1;
    
    if(raiz->altura <= subArvore->altura)
        raiz->altura = subArvore->altura + 1;
}



/*
    O algoritmo de busca em uma árvore binária de busca se baseia na propriedade 
    da árvore onde, para cada nó, todos os valores na subárvore esquerda são
    menores que o nó, e todos os valores na subárvore direita são maiores.
*/
No* buscarNo(No* raiz, int valor){
    //Se raiz é NULL, retorne NULL
    if(raiz == NULL)
        return NULL;
    //SE raiz->valor é igual a valor, retorne raiz
    if(raiz->valor == valor)
        return raiz;
    //Se valor é menor que raiz->valor, retorne buscarNo da raiz->esquerda
    else if(valor < raiz->valor)
        return buscarNo(raiz->esquerda, valor);

    //Se nenhuma das condições acima for verdadeira, então o valor é maior que raiz->valor. Nesse caso, retorne buscarNo da raiz->direita.
    return buscarNo(raiz->direita, valor);
}

/*
    Função utilizada para remover um determinado valor da árvore.
*/
No* removerNo(No* raiz, int valor){
    
    // Se raiz é NULO, retorne NULO
    if( raiz == NULL ) return NULL;

    // Se valor É MENOR QUE raiz->valor, continua buscando no filho a esquerda
    if(valor < raiz->valor){
        raiz->esquerda = removerNo(raiz->esquerda, valor);
    // Senão se valor É MAIOR QUE raiz->valor, continua buscando no filho a direita
    }else if(valor > raiz->valor){
        raiz->direita = removerNo(raiz->direita, valor);
    }else{ // No caso do valor IGUAL A raiz->valor
        // Encontrou o nó a ser removido
        // Caso 1: Nó sem filhos (folha)
        if(raiz->esquerda == NULL && raiz->direita == NULL){
            // limpa o próprio nó da memória e retorna NULL
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        if(raiz->esquerda == NULL){ // Se o nó à esquerda é NULO
            // Nó à direita assume a posição
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }else if(raiz->direita == NULL){ // Se o nó à direita é NULO
            // Nó à esquerda assume a posição
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 3: Nó com dois filhos
        // busca o nó de menor valor nó filho à direita
        No* menorNo = buscarMenorValor(raiz->direita); 
        raiz->valor = menorNo->valor;
        raiz->direita = removerNo(raiz->direita, menorNo->valor);
    }
    
    return raiz;
}

/*
    Busca o menor valor de uma árvore
*/
No* buscarMenorValor(No* raiz){
    // Se raiz->esquerda NÃO É NULL, buscar menor valor
    if(raiz->esquerda != NULL) 
        return buscarMenorValor(raiz->esquerda);
    
    // Do contrário, retornar o próprio nó (raiz)
    return raiz;
}
