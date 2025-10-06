// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void main() {
    char texto[100] = "abcbcbabacbcaacbabacaba";
    char padrao[50];

    printf("Digite o padrão que você deseja buscar: ");
    scanf("%s", padrao);

    // preciso implementar uma "funcao" prefixo/sufixo
    int n = strlen(texto); // tamanho do texto
    int m = strlen(padrao); // tamanho do padrao
    int j = -1;
    int aux[50];
    aux[0] = j;

    for (int i = 1; i < m; i++) {
        while (j > -1 && padrao[j + 1] != padrao[i]) {
            j = aux[j];
        }
        if (padrao[i] == padrao[j + 1]) {
            j++;
        }
        aux[i] = j;
    }

    // agora que temos nosso vetor aux formado, vamos de fato usar o algoritmo KMP
    int achou = 0;
    j = -1;
    for (int i = 0; i < n; i++) {
        while (j > -1 && padrao[j + 1] != texto[i]) {
            j = aux[j];
        }
        
        if (padrao[j + 1] == texto[i]) {
            j++;
        }

        if (j == m-1) {
            printf("Encontrado no índice %d!\n", i - m + 1); // índice da ocorrência
            achou = 1;
        }
    }

    if(achou == 0) {
        printf("Não encontrei o padrão :(");
    }
}
