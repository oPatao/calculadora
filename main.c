#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculadora.h"

int main() {
    Expressao expr;

    printf("Digite a expressao em notacao pos-fixada: ");
    fgets(expr.posFixa, sizeof(expr.posFixa), stdin);
    expr.posFixa[strcspn(expr.posFixa, "\n")] = '\0';

    // Calcula o valor da expressão com copia para não mudar a string original
    char posFixaCopia[512];
    strcpy(posFixaCopia, expr.posFixa);
    expr.valor = getValor(posFixaCopia);
    printf("Valor da expressao: %.2f\n", expr.valor);

    // Mostra pré fixada
    strcpy(posFixaCopia, expr.posFixa);
    strcpy(expr.preFixa, getFormaPreFixa(posFixaCopia));
    printf("Forma prefixada: %s\n", expr.preFixa);

    system("pause"); // Pausa para ver o resultado antes de fechar o console

    return 0;
}