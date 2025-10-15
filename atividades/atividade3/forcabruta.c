// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void main() {
    char texto[100] = "EugostodecursarcomputacaooporqueemuitodivertidoEugostodoSamuelEusouaAyssa";
    char padrao[100];
    int indice;

    printf("Qual padrão deseja procurar? ");
    scanf("%s", padrao);

    int n = strlen(texto); // tamanho do texto
    int m = strlen(padrao); // tamanho do padrao
    int comparacoes = 0;
    int achou = 0;

    for(int i = 0; i <= n-m; i++) {
        int j = 0;
        
        while(j < m && texto[i+j] == padrao[j]) {
            comparacoes += 1; // se entrei aqui, é porque texto[i+j] == padrao[j], logo, comparei +1
            j += 1;
        }
        if (j == m) { // se entrei aqui, é porque j == m, então não devo comparar nada!
            printf("Achei uma ocorrência, o padrão começa no índice %d!\n", i);
            indice = i;
            achou = 1;
            break;
        }
        else {
            comparacoes += 1; // se entrei aqui, é porque o j != m && texto[i+j] != padrao[j], logo, comparei +1
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