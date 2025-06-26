#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expressao.h"

int main() {
    Expressao expr;
    char buffer_entrada[MAX_EXPRESSAO];

    printf("--- Avaliacao de Pos-fixada e Conversao para Infixada ---\n");
    printf("Digite a expressao em notacao pos-fixada (ex: 3 4 + 5 *): ");
    fgets(buffer_entrada, sizeof(buffer_entrada), stdin);
    buffer_entrada[strcspn(buffer_entrada, "\n")] = '\0';

    strcpy(expr.posFixa, buffer_entrada);

    char copiaPosFixa1[MAX_EXPRESSAO];
    strcpy(copiaPosFixa1, expr.posFixa);
    expr.Valor = getValorPosFixa(copiaPosFixa1);
    printf("Valor da expressao pos-fixada: %.2f\n", expr.Valor);

    char copiaPosFixa2[MAX_EXPRESSAO];
    strcpy(copiaPosFixa2, expr.posFixa);
    strcpy(expr.inFixa, getFormaInFixa(copiaPosFixa2));
    printf("Forma infixada (da pos-fixada): %s\n\n", expr.inFixa);

    printf("--- Conversao de Infixada para Pos-fixada e Avaliacao ---\n");
    printf("Digite a expressao em notacao infixada (ex: (3 + 4) * 5): ");
    fgets(buffer_entrada, sizeof(buffer_entrada), stdin);
    buffer_entrada[strcspn(buffer_entrada, "\n")] = '\0';

    strcpy(expr.inFixa, buffer_entrada);

    char copiaInFixa1[MAX_EXPRESSAO];
    strcpy(copiaInFixa1, expr.inFixa);
    strcpy(expr.posFixa, getFormaPosFixa(copiaInFixa1));
    printf("Forma pos-fixada (da infixada): %s\n", expr.posFixa);

    char copiaInFixa2[MAX_EXPRESSAO];
    strcpy(copiaInFixa2, expr.inFixa);
    expr.Valor = getValorInFixa(copiaInFixa2);
    printf("Valor da expressao infixada: %.2f\n\n", expr.Valor);

    printf("--- Exemplo com Operador de Modulo (%%) ---\n");
    char teste_modulo_posfixa[] = "10 3 %";
    printf("Expressao pos-fixada: %s\n", teste_modulo_posfixa);
    printf("Valor: %.2f\n\n", getValorPosFixa(teste_modulo_posfixa));

    printf("Pressione Enter para sair...\n");
    getchar();
    getchar();

    return 0;
}
