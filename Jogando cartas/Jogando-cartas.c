

#include <stdio.h>
#include <stdlib.h>
//************* STRUCTS ****************************
typedef struct _fila{
    struct _carta *inicio;
    //struct _carta *auxiliar;
    struct _carta *fim;
} Fila;

typedef struct _carta{
    int valor;
    struct _carta *anterior;
    struct _carta *proximo;
} Carta;

//**************************************************

//************* DECLARAÇÃO DE FUNÇÕES **************

Carta *CriaCarta(int valorDaCarta);
Fila *CriaFila();
void ImprimeCarta(Fila *fila);
int FilaVazia(Fila *fila);
void DestroyFila(Fila **fila);
void ComecaOJogo(Fila *fila, int quantCartas);

//*************************************************

//************* MAIN *********************
int main() {
    int quantidadeCartas = 1000;
    while(quantidadeCartas != 0){
        //printf("Digite a quantidade de cartas que se deseja usar\n");
        scanf("%d",&quantidadeCartas);

        Fila *fila = CriaFila();
        if(fila->inicio != fila->fim){
            printf("Cartas jogadas: ");
        }
        
        
        ComecaOJogo(fila, quantidadeCartas);
        //printf("\n");
        DestroyFila(&fila);
    }
    
    
    
    return(0);
}

//****************************************


//************* FUNCOES ************************

Carta *CriaCarta(int valorDaCarta){
    Carta *noCarta = (Carta*)calloc(1,sizeof(Carta));
    noCarta->valor = valorDaCarta;
    noCarta->anterior = noCarta;
    noCarta->proximo = noCarta;
    return noCarta;
}

Fila *CriaFila(int quantidadeCarta){
    Fila *novaFila = (Fila*)calloc(1,sizeof(Fila));
    novaFila->fim = NULL;
    //novaFila->auxiliar = NULL;
    novaFila->inicio = NULL;
    return novaFila;
}


void ImprimeCarta(Fila *fila){
    if(!FilaVazia(fila)){
        
        printf("Cartas jogadas: ");
        if(fila->fim != fila->inicio){
            
            do{
                Carta *noCarta = fila->inicio->anterior;  

                if(fila->inicio->anterior != fila->fim){
                    printf("%d, ",fila->inicio->valor);
                }else{
                    printf("%d",fila->inicio->valor);
                }

                free(fila->inicio);

                if(fila->inicio->anterior != fila->fim){
                    fila->inicio = noCarta->anterior;
                    noCarta->proximo = fila->fim;
                    fila->fim->anterior = noCarta;
                    fila->fim = noCarta;

                }else{
                    fila->inicio = noCarta;
                    //printf("\nSobrou %d", fila->inicio->valor);
                } 
            }while(fila->inicio != fila->fim);
        }

        printf("\nCarta restante: %d\n", fila->inicio->valor); 
    }
    
}

void DestroyFila(Fila **fila){
    
    Fila *auxiliarFila = *fila;
       
    if(!FilaVazia(auxiliarFila)){
        
        Carta *destruidorDeCartas = auxiliarFila->inicio;
        
        while(destruidorDeCartas != auxiliarFila->fim){
            destruidorDeCartas = auxiliarFila->inicio;
            free(destruidorDeCartas);
            auxiliarFila->inicio = auxiliarFila->inicio->anterior;
        }
        free(destruidorDeCartas);
    }
    free(auxiliarFila);
    *fila = NULL;
}



void ComecaOJogo(Fila *fila, int quantCartas){
    
    
    for(int i = 1; i <= quantCartas; i++){
        Carta *carta = CriaCarta(i);
        
        //inserir em fila vazia
        if(FilaVazia(fila)){
           //fila->auxiliar = carta;
           fila->fim = carta;
           fila->inicio = carta;
           //printf("inseriu a carta %d no baralho\n", carta->valor);
        }
        //inserir em fila com um elemento
        else if(fila->inicio == fila->fim){
            carta->proximo = fila->inicio;
            fila->inicio->anterior = carta;
            carta->anterior = fila->inicio;
            fila->inicio->proximo = carta;
            fila->fim = carta;
           // printf("inseriu a carta %d no baralho\n", carta->valor);
            
        }//inserir em fila com mais de um elemento
        else {
            carta->proximo = fila->fim;
            carta->anterior = fila->inicio;
            fila->fim->anterior = carta;
            fila->fim = carta;
            
        }  
    }
   
    ImprimeCarta(fila);
}

int FilaVazia(Fila *fila){
    return (fila->inicio == NULL);

}

