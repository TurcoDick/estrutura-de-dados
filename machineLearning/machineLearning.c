#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//+++++++++++++++++++++++++++ Estruturas +++++++++++++++++++++
typedef struct _amostrasTreinamento{
    float nota;
    float horaDeEstudo;
    int status;
}AmostraTreinamento; 

typedef struct _amostraTeste{
    float nota;
    float horasDeEstudo;
    int status;
}AmostraTeste;

typedef struct _vetorEuclidiano{
    float valorEuclidiano;
    int status;
}VetorEuclidiano;

//----------------- Declarações de funções ------------------------
AmostraTreinamento *CriarVetorComAmostraDeTreinamento(int numeroAmostrasTreinamentoM);
AmostraTeste *CriaVetorAmostrasTeste(int numeroAmostrasTesteN);
float CalculoEuclidiano(AmostraTeste teste, AmostraTreinamento amostrasTreinamento);
void Cerebro(int numeroReferenciasK ,int numeroAmostrasTreinamento, int numeroAmostrasTeste, AmostraTeste *teste, AmostraTreinamento *treinamento);
char situacao(int status);
void Imprimir(int numeroAmostrasTeste, AmostraTeste *amostraTeste);

// ---------------- Corpo de Funções --------------------------

AmostraTreinamento *CriarVetorComAmostraDeTreinamento(int numeroAmostrasTreinamentoM){
//    printf("\nCriarVetorComAmostraDeTreinamento");
    AmostraTreinamento *amostraTreinamento = (AmostraTreinamento*)calloc(numeroAmostrasTreinamentoM,sizeof(AmostraTreinamento));

    for(int i = 0; i < numeroAmostrasTreinamentoM; i++){
        scanf("%f", &amostraTreinamento[i].nota);
        scanf("%f", &amostraTreinamento[i].horaDeEstudo);
        scanf("%d", &amostraTreinamento[i].status);
//        printf("\nnota = %2.f, hora treinamento = %2.f, status = %d", amostraTreinamento[i].nota, amostraTreinamento[i].horaDeEstudo, amostraTreinamento[i].status);
    }
    return amostraTreinamento;
}

AmostraTeste *CriaVetorAmostrasTeste(int numeroAmostrasTesteN){

    AmostraTeste *amostraTeste = (AmostraTeste*)calloc(numeroAmostrasTesteN,sizeof(AmostraTeste));
//    printf("\nCriaVetorAmostrasTeste1");
    for(int i = 0; i < numeroAmostrasTesteN; i++){
        scanf("%f", &amostraTeste[i].nota );
        scanf("%f", &amostraTeste[i].horasDeEstudo);
//        printf("\nnota teste = %2.f, hora teste %2.f ",amostraTeste[i].nota, amostraTeste[i].horasDeEstudo);
    }
    return amostraTeste;
}

void Cerebro(int numeroReferenciasK ,int numeroAmostrasTreinamento, int numeroAmostrasTeste, AmostraTeste *teste, AmostraTreinamento *treinamento){
//    printf("\nCerebro");
    int positivo = 0;
    int negativo = 0;
    
    for(int k = 0; k < numeroAmostrasTeste; k++){
        positivo = 0;
        negativo = 0;
        
        VetorEuclidiano substitui;
        
        VetorEuclidiano *vetorEuclidiano = (VetorEuclidiano*) calloc(numeroAmostrasTreinamento,sizeof(VetorEuclidiano));
        
        for(int m = 0; m < numeroAmostrasTreinamento; m++){
            
            vetorEuclidiano[m].valorEuclidiano = sqrt((pow((teste[k].nota - treinamento[m].nota),2) + (pow((teste[k].horasDeEstudo - treinamento[m].horaDeEstudo),2))));
            vetorEuclidiano[m].status = treinamento[m].status;
            
//            printf("\nEuclidiano[%d] = %.2f", m, vetorEuclidiano[m].valorEuclidiano);
//            printf("\nStatus = %d", vetorEuclidiano[m].status);   
        }
        //ordena o vetor euclidiano deixando os menores valores mais proximos
        for(int a = 0; a < numeroAmostrasTreinamento; a++){ 
                
            for(int b = 0; b < numeroAmostrasTreinamento; b++){
                  
                if(vetorEuclidiano[a].valorEuclidiano < vetorEuclidiano[b].valorEuclidiano){
                    substitui = vetorEuclidiano[a];
                    vetorEuclidiano[a] = vetorEuclidiano[b];
                    vetorEuclidiano[b] = substitui;
                }                
            }
        }
//        for(int i = 0; i < numeroAmostrasTreinamento; i++){
//            printf("\nEuclidiano[%d] = %.2f", i, vetorEuclidiano[i].valorEuclidiano);
//            printf("\nStatus = %d", vetorEuclidiano[i].status);
//        }
        
        for(int i = 0; i < numeroReferenciasK; i++){
            if(vetorEuclidiano[i].status != 0){
                positivo++;
            }else{
                negativo++;
            }
            //printf("\nvalores euclidianos aluno [%d] = %.2f",i,vetorEuclidiano[i].valorEuclidiano);
        }
        if(negativo > positivo){
            teste[k].status = 0;
        }else{
            teste[k].status = 1;
        }
        
    }
//    for(int q = 0; q < numeroAmostrasTeste; q++ ){
//        printf("\nAluno %d: (%.2f, %.2f) = %d", q, teste[q].nota, teste[q].horasDeEstudo, teste[q].status);
//        
//    }
}

void Imprimir(int numeroAmostrasTeste, AmostraTeste *teste){
    char aprovado[] = "Aprovado";
    char reprovado[] = "Reprovado";
    char situacao[10] = "";
    
    for(int q = 0; q < numeroAmostrasTeste; q++ ){
      
        if(teste[q].status == 1){
            strcpy(situacao,aprovado);
        }else{
            strcpy(situacao,reprovado);
        }
        printf("Aluno %d: (%.2f, %.2f) = %s\n", q, teste[q].nota, teste[q].horasDeEstudo, situacao);
        
    }
}
// ---------------- MAIN ---------------------------------------
int main() {
    int numeroAmostrasTreinamentoM = 0;
    int numeroAmostrasTesteN = 0;
    int numeroReferenciasK = 0;
    //printf("\nmain");
    scanf("%d", &numeroAmostrasTreinamentoM);
    scanf("%d", &numeroAmostrasTesteN);
    scanf("%d", &numeroReferenciasK);
    AmostraTreinamento *vetorTreinamento = CriarVetorComAmostraDeTreinamento(numeroAmostrasTreinamentoM);
    AmostraTeste *vetorTeste = CriaVetorAmostrasTeste(numeroAmostrasTesteN);

    Cerebro(numeroReferenciasK,numeroAmostrasTreinamentoM,numeroAmostrasTesteN,vetorTeste,vetorTreinamento);
    Imprimir(numeroAmostrasTesteN, vetorTeste);

    return (0);
}

