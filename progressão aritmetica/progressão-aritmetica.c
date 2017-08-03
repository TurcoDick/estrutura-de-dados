
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * formula aritmetica para PA
 * an = a1 + (n - 1) * r
 * ou de uma maneira melhor para abranger a soma e subtração temos 
 * an = ak + (n - k) * r
 * é para mostrar a fatorial do ultimo termo e a soma dos termos até o ultimo
 * 
 */

int main(int argc, char** argv) {
    int n1, raiz, nQuant, ultimoTermo = 0, soma = 0;
   
   
    scanf("%d", &n1);
    
 
    scanf("%d", &raiz);

 
    scanf("%d", &nQuant);

    ultimoTermo = n1 + (nQuant - 1) * raiz; 
    for(int i = 0; i <= nQuant; i++){
        ultimoTermo = n1 + (i - 1) * raiz;
        if(i != nQuant){
           soma = ultimoTermo + (soma + raiz); 
        }
    };
    printf("%d\n", ultimoTermo);
    printf("%d", soma);
    
    return 0;
}

