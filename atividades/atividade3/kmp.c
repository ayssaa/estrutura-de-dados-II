// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void main() {
    char texto[100] = "ABCDABDABDABCDABCDABC";
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
    int indice = -1;
    int comparacoes = 0;
    j = -1;
    for (int i = 0; i < n; i++) {
        while (j > -1 && padrao[j + 1] != texto[i]) {
            comparacoes += 1;
            j = aux[j];
        }
        
        comparacoes += 1;
        
        if (padrao[j + 1] == texto[i]) {
            j++;
        }

        if (j == m-1) {
            indice = i - m + 1;
            printf("Encontrado no índice %d!\n", indice); // índice da ocorrência
            achou = 1;
        }
    }

    FILE *resultados = fopen("resultados.txt", "w");
    if (resultados == NULL) {
        printf("Erro ao criar arquivo!\n");
    }

    if(achou == 0) {
        fprintf(resultados, "Não encontrei o padrão!\n");
    }
    
    else {
        fprintf(resultados, "indice = %d\ncomparacoes = %d\n", indice, comparacoes);
    }

    fclose(resultados);

    printf("Resultado está salvo em 'resultados.txt'!\n");
    printf("Tivemos um total de %d comparações!\n", comparacoes);
}
