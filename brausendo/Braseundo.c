

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no_site{
    char nomeSite[150];
    struct _no_site *up;
    struct _no_site *down;
} NoSite;

typedef struct _no_pilha{
    NoSite *topo;
    int quantidade;
} NoPilha;

// DECLARAÇÃO DE FUNÇÕES

int PilhaVazia(NoPilha *pilha); //***************

NoPilha *CriaPilha();  //******************

NoSite *CriaSite(char nomeSite[]);  //***************

void DestroiPilha(NoPilha **pilha); //**************

NoPilha *Pop(NoSite *site);

void Push(NoPilha *pilha, char nomeSite[]);

void Avanca(NoPilha *pilha); //*****************

void Volta(NoPilha *pilha);// ******************

void Imprime(NoPilha *pilha);

NoSite *VoltaParaInicioDaPilha(NoPilha *pilha); //*********

//---------------- MAIN ------------------
int main(){

    char opcao[10];
    char novoNome[200];
    
    NoPilha *pilha = CriaPilha();
    //printf("\n");
    while(strcmp(opcao, "encerra") != 0){     
        scanf(" %s", opcao);  
        if(strcmp(opcao, "avanca") == 0){
            Avanca(pilha);     
        }else if(strcmp(opcao, "imprime") == 0){
            Imprime(pilha);
        }else if(strcmp(opcao, "acessa")== 0 ){
            scanf(" %[^\t\n]s", novoNome);
            Push(pilha, novoNome); 
        }else if(strcmp(opcao, "volta") == 0){
            Volta(pilha);
        }     
    }   
    DestroiPilha(&pilha);
    return (0);
}

//------------- corpo das funções -------- 

NoPilha *CriaPilha(){
    NoPilha *pilha = (NoPilha*)calloc(1, sizeof(NoPilha));
    pilha->quantidade = 0;
    pilha->topo = NULL;
    return pilha;
}

NoSite *CriaSite(char nomeSite[]){
    NoSite *novoSite = (NoSite*) calloc(1,sizeof(NoSite));
    strcpy(novoSite->nomeSite, nomeSite);
    novoSite->down = NULL;
    novoSite->up = NULL;
    return novoSite;
}

void DestroiPilha(NoPilha **pilha){
    
    NoPilha *auxiliarPilha = *pilha;
    
    //lista esta vazia
    if(!PilhaVazia(auxiliarPilha)){
        
        NoSite *destruidorSite = VoltaParaInicioDaPilha(auxiliarPilha);
        int contador = 1;
        
        while(contador <= auxiliarPilha->quantidade){
            NoSite *q = destruidorSite;
            destruidorSite = destruidorSite->up;
            free(q);
            contador++;
        }
        free(destruidorSite);
    }
    free(auxiliarPilha);
    *pilha = NULL;
}

//retira
NoPilha *Pop(NoSite *site){
    
    NoPilha *pilha2 = CriaPilha();
    pilha2->quantidade++;
    
    if(PilhaVazia(pilha2)){
        pilha2->topo = site;
    }else{
        site->up = pilha2->topo;
        pilha2->topo->up = site;
        pilha2->topo = site;
    }
    return pilha2;
}


void Push(NoPilha *pilha, char nomeSite[]){   
    NoSite *novoAcesso = CriaSite(nomeSite);

    if(PilhaVazia(pilha)){       
        pilha->topo = novoAcesso;
        
    }//insere com o topo no meio
    else if(pilha->topo->up != NULL){
        NoSite *exclui = pilha->topo->up;
        NoSite *auxiliarExclui = exclui;
        
        pilha->topo->up = novoAcesso;
        novoAcesso->down = pilha->topo;
        pilha->topo = novoAcesso;
        
        //exclui os outros acessos
        while(exclui != NULL){
            auxiliarExclui = exclui;
            exclui = exclui->up;
            free(auxiliarExclui);
            pilha->quantidade--;
        }
        
    }
    // insere com o topo no alto da pilha
    else{       

        pilha->topo->up = novoAcesso;
        novoAcesso->down = pilha->topo;
        pilha->topo = pilha->topo->up; 
    }
    pilha->quantidade++;
}

void Avanca(NoPilha *pilha){
    if(!PilhaVazia(pilha)){
        if(pilha->topo->up != NULL){
            pilha->topo = pilha->topo->up;
        }
    } 
}

void Volta(NoPilha *pilha){    
    if(pilha->quantidade > 1){
        NoSite *inicio = VoltaParaInicioDaPilha(pilha);
        
        //printf("quantidade = %d\n", pilha->quantidade);
        //printf("topo antes do volta = %s\n", pilha->topo->nomeSite);
        if(pilha->topo != inicio){
            pilha->topo = pilha->topo->down;
        }
        //printf("topo depois do volta = %s\n", pilha->topo->nomeSite);
    }   
}

void Imprime(NoPilha *pilha){
    
    if(pilha->quantidade > 0){ 
        
        NoSite *corredor = VoltaParaInicioDaPilha(pilha);
       
        while(corredor != NULL){
            if(corredor == pilha->topo){
                printf("--> %s\n",corredor->nomeSite);
            }else{
                printf("%s\n", corredor->nomeSite);
            }
            corredor = corredor->up;       
        }
    	printf("\n");
    }   
}



NoSite *VoltaParaInicioDaPilha(NoPilha *pilha){
    
    
    if(!PilhaVazia(pilha)){
        
        NoSite *aux = pilha->topo;
        
        while(aux->down != NULL){
            aux = aux->down;
        }
        
//        do{   
//            aux = aux->down; 
//        }while(aux->down != NULL);
//        
        
        
        return aux;    
    }else{
        return NULL;
    }
    
}

int PilhaVazia(NoPilha *pilha){
    return (pilha->topo == 0);    
}
