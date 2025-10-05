// Incluindo Bibliotecas
# include <stdio.h>
# include <stdlib.h>


// Função que realiza uma busca binária
int buscaBinaria(int v[], int chave) {
    int esquerda = 0;
    int direita = 2;
   
    while(esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (chave < v[meio]) {
            direita = meio - 1;
        }
        else if (chave > v[meio]) {
            esquerda = meio + 1;
        }
        else {
            return v[meio];
        }
    }
    return -1;
   
}


void main() {
    int vetor[3] = {1, 2, 3};
    int procurado = 3;
   
    int resultado = buscaBinaria(vetor, procurado);
   
    if(resultado != -1) {
        printf("Achei! O valor procurado é %d", resultado);
    }
    else {
        printf("Valor não encontrado");
    }
}
