// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void main() {
    char texto[100] = "abcbcbabacbcaacbabacaba";
    char padrao[50];

    printf("Digite o padrão que você deseja buscar: ");
    scanf("%s", padrao);

    // implementando a busca boyer moore
    

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
