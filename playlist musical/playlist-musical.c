#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no_musica{
	char NOME_DA_MUSICA[150];
	struct _no_musica *proximo;
	struct _no_musica *anterior;
} NoMusica;

typedef struct _playList{
	NoMusica *fim;
	NoMusica *inicio;
	NoMusica *cursor;
	int quantidadeMusicas;
} PlayList;

//********************** declarações da funções ******************************************
NoMusica *CriaMusica(char nomeNovaMusica[]);
PlayList *CriaPlayList();
int ListaEstaVazia(PlayList *playList);
//void CopiaString(NoMusica *novaMusica, char stringOriginal[]);
int SotemUmElemento(PlayList *playList);
void InsereMusica(PlayList *playList, char nomeNovaMusica[]);
void removendo(PlayList *playList, char NOME_DA_MUSICA[]);
void toca(PlayList *playList);
void volta(PlayList *playList);
void final(PlayList *playList);
int comparaString(char *string1, char *string2);
//char pegaString(PlayList *playList);
void inverte(PlayList *playList);
void Imprime(PlayList *playList);
void InsereMusicaParaInversao(PlayList *playList, char NOME_DA_MUSICA[]);
void DestroiLista(PlayList **Lista);
void printLista(PlayList *playlis);
void printInvertido(PlayList *playlis);

//****************************************************************************************

// MAIN ****************************
int main() {
    int numeroDeOperacoes = 1;
    char titulo[128];
    char opcao[50];
    
    
    
    scanf("%d", &numeroDeOperacoes);
    
    while(numeroDeOperacoes != 0) {
        PlayList *playlist = CriaPlayList();
        
        // temos numeroDeOperacoes para manipular a playlist que criamos
        for (int i = 0; i < numeroDeOperacoes; i++) {
            scanf("%s", opcao);
            
            if (strcmp(opcao, "insere") == 0) {
                // comando insere
                scanf(" %[^\t\n]s", titulo);
                InsereMusica(playlist, titulo);
                
            }
            else if (strcmp(opcao, "remove") == 0) {
                // comando remove
                scanf(" %[^\t\n]s", titulo);
//                printLista(playlist);
//                printInvertido  (playlist);;
                removendo(playlist, titulo);
            }
            else if (strcmp(opcao, "toca") == 0) {
                // comando toca
                toca(playlist);
            }
            else if (strcmp(opcao, "volta") == 0) {
                // comando volta
                volta(playlist);
            }
            else if (strcmp(opcao, "final") == 0) {
                // comando final
                final(playlist);
            }
            else if (strcmp(opcao, "inverte") == 0) {
                // comando inverte
                inverte(playlist);
            }
        }
        
        
        DestroiLista(&playlist);
        scanf("%d", &numeroDeOperacoes);
        if (numeroDeOperacoes != 0) {
            printf("\n");
        }
    }
    
    
    return 0;
}


//**********************************

// CONSTRUÇÃO DAS FUNÇÕES

void Imprime(PlayList *playList){
    printf("\nimprime");
    if(playList != NULL){
        NoMusica *farejador = playList->inicio;
        //só tem um elemento na lista
        if(playList->inicio == playList->fim){
            //printf("\n nome da musica é %s ",farejador->NOME_DA_MUSICA);
        }else{
            do{
                //printf("\n nome da musica é %s ", farejador->NOME_DA_MUSICA);
                farejador = farejador->proximo;    
            }while(farejador != playList->inicio);
        }
    }
}

void InsereMusica(PlayList *playList, char nomeNovaMusica[]){
    NoMusica *novaMusica = CriaMusica(nomeNovaMusica);
    
    //lista vazia
    if(playList->inicio == NULL){
        playList->inicio = novaMusica;
        playList->cursor = novaMusica;
        playList->fim = novaMusica;
         
    }//lista com elementos
    else{
        //somente um elemento
        if(playList->inicio == playList->fim){
            
            novaMusica->anterior = playList->inicio;
            novaMusica->proximo = playList->inicio;
            playList->inicio->proximo = novaMusica;
            playList->inicio->anterior = novaMusica;
            playList->fim = novaMusica;
            
        }
        //com o cursor no fim da lista
        else if(playList->cursor == playList->fim){
            novaMusica->anterior = playList->cursor;
            novaMusica->proximo = playList->inicio;
            playList->fim->proximo = novaMusica;
            playList->inicio->anterior = novaMusica;
            playList->fim = novaMusica;
            
        }
        //com o cursor no inicio da lista
        else if(playList->inicio == playList->cursor){
    
            novaMusica->anterior = playList->cursor;
            novaMusica->proximo = playList->cursor->proximo;
            playList->cursor->proximo->anterior = novaMusica;
            playList->cursor->proximo = novaMusica;
            
            //com o cursor em outro lugar
        }else{
            novaMusica->proximo = playList->cursor->proximo;
            novaMusica->anterior = playList->cursor;
            playList->cursor->proximo->anterior = novaMusica;
            playList->cursor->proximo = novaMusica;
        }
    }
    //printf("\nFoi inserido a musica '%s' na lista",novaMusica->NOME_DA_MUSICA);
}

int ListaEstaVazia(PlayList *playList){
    if(playList->inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

void removendo(PlayList *playList, char NOME_DA_MUSICA[]){
    
    //se a lista estiver vazia não faz nada
    if(!ListaEstaVazia(playList)){
        NoMusica *p = playList->inicio;

        do {
            if (strcmp(p->NOME_DA_MUSICA, NOME_DA_MUSICA) == 0) {   
                // soh tem um elemento
                if (playList->inicio == playList->fim) {
                    playList->inicio = playList->fim = playList->cursor = NULL;
                }
                else {
                    if (playList->cursor == p) {
                        playList->cursor = playList->cursor->anterior;
                    }
                    if (playList->inicio == p) {
                        playList->inicio = playList->inicio->proximo;
                    }
                    if (playList->fim == p) {
                        playList->fim = playList->fim->anterior;
                    }
                }
                
                
                p->anterior->proximo = p->proximo;
                p->proximo->anterior = p->anterior;
                free(p);
                break;
            }
            else {
                p = p->proximo;
            }
        } while(p != playList->inicio);   
    }    
}

NoMusica *CriaMusica(char nomeNovaMusica[]){
	NoMusica *novaMusica = (NoMusica*)calloc(1,sizeof(NoMusica));
	//CopiaString(novaMusica, nomeNovaMusica);
        strcpy(novaMusica->NOME_DA_MUSICA, nomeNovaMusica);
	novaMusica->proximo = novaMusica;
	novaMusica->anterior = novaMusica;
	return novaMusica;
}

PlayList *CriaPlayList(){
	PlayList *playList = (PlayList*)calloc(1,sizeof(PlayList));
	playList->inicio = NULL;
	playList->fim = NULL;
	playList->cursor = NULL;
	playList->quantidadeMusicas = 0;
	return playList;
}

void toca(PlayList *playList){
    if(!ListaEstaVazia(playList)){
        printf("%s\n", playList->cursor->NOME_DA_MUSICA);
        playList->cursor = playList->cursor->proximo;
    }else{
        printf("\n");
    }
    
}

void volta(PlayList *playList){
    if(!ListaEstaVazia(playList)){
        playList->cursor = playList->cursor->anterior;
    }
}

void final(PlayList *playList){
    //lista não esta vazia, faz tudo 
    if(!ListaEstaVazia(playList)){

        do{
            printf("%s\n", playList->cursor->NOME_DA_MUSICA);
            playList->cursor = playList->cursor->proximo;
            
        }while(playList->cursor != playList->inicio);
        playList->cursor = playList->cursor->anterior;

        
    }// lista vazia imprime "\n"
    else{
        printf("\n");
    }
}

//int comparaString(char string1[], char string2[]){
//    return strcmp(string1,string2);
//}

void DestroiLista(PlayList **Lista){
    PlayList *auxiliarLista = *Lista;
    
    if(auxiliarLista != NULL){
        //lista vazia
        if(ListaEstaVazia(auxiliarLista)){
            NoMusica *p = auxiliarLista->inicio;
            
            while (p != auxiliarLista->fim) {
                NoMusica *q = p;
                p = p->proximo;
                free(q);
            }
            free(p);
        }
        free(auxiliarLista);
        *Lista = NULL;
    }  
}

void inverte(PlayList *playList){

    if(!ListaEstaVazia(playList)){
        NoMusica *auxiliar = playList->fim;
        NoMusica *auxiliar2 = playList->fim->anterior;
        do{
            //printf("Inverteu = %s ",auxiliar->NOME_DA_MUSICA);
            auxiliar->anterior = auxiliar->proximo;
            auxiliar->proximo = auxiliar2;
            auxiliar = auxiliar->proximo;
            auxiliar2 = auxiliar2->anterior;
        
        }while(auxiliar != playList->fim);
    
        NoMusica *ancoraFim = playList->fim;
        NoMusica *ancoraInicio = playList->inicio;
    
        playList->inicio = ancoraFim;
        playList->fim = ancoraInicio;
    }  
}



void printLista(PlayList *playlist) {
    if (!ListaEstaVazia(playlist)) {
        NoMusica *p = playlist->inicio;
        
        do {
            printf("%s -> ", p->NOME_DA_MUSICA);
            p = p->proximo;
        } while (p != playlist->inicio);
        puts("NULL\n");
    }
}


void printInvertido(PlayList *playlist) {
    if (!ListaEstaVazia(playlist)) {
        NoMusica *p = playlist->fim;
        
        do {
            printf("%s -> ", p->NOME_DA_MUSICA);
            p = p->anterior;
        } while (p != playlist->fim);
        puts("NULL\n");
    }
}



