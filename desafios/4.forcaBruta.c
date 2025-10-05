// Incluindo bibliotecas
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void main() {
    char texto[50] = "abcbcbabacbcaacbabacaba";
    char padrao[50];

    printf("Qual padrão deseja procurar? ");
    scanf("%s", padrao);

    int n = strlen(texto); // tamanho do texto
    int m = strlen(padrao); // tamanho do padrao

    for(int i = 0; i <= n-m; i++) {
        int j = 0;

        while(j < m && texto[i+j] == padrao[j]) {
            j += 1;
        }

        if (j == m) {
            printf("Achei uma ocorrência, o padrão começa no índice %d!", i);
            break;
        }
    }
}