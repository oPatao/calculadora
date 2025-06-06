#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXIMO 100

#ifndef PI
#define PI 3.141592
#endif

typedef struct {
    float items[MAXIMO];
    int top;
} Pilha;

typedef struct {
    char *items[MAXIMO];
    int top;
} StringPilha;

void colocaNaPilha(Pilha *s, float value) {
    if (s->top < MAXIMO - 1) {
        s->items[++s->top] = value;
    } else {
        printf("Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

float tiraDaPilha(Pilha *s) {
    if (s->top >= 0) {
        return s->items[s->top--];
    } else {
        printf("Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void colocaNaPilhaString(StringPilha *s, char *value) {
    if (s->top < MAXIMO - 1) {
        s->items[++s->top] = value;
    } else {
        printf("Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

char* tiraDaPilhaString(StringPilha *s) {
    if (s->top >= 0) {
        return s->items[s->top--];
    } else {
        printf("Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

float getValor(char *Str) {
    Pilha Pilha = {.top = -1};
    char *verificaEspaco = strtok(Str, " ");
    while (verificaEspaco != NULL) {
        if (isdigit(verificaEspaco[0]) || (verificaEspaco[0] == '-' && isdigit(verificaEspaco[1]))) {
            colocaNaPilha(&Pilha, atof(verificaEspaco));
        } else {
            if (strcmp(verificaEspaco, "+") == 0) {
                if (Pilha.top < 1) {
                    printf("Erro: Operando faltando para a operacao '+'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                float a = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, a + b);
            } else if (strcmp(verificaEspaco, "-") == 0) {
                if (Pilha.top < 1) {
                    printf("Erro: Operando faltando para a operacao '-'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                float a = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, a - b);
            } else if (strcmp(verificaEspaco, "*") == 0) {
                if (Pilha.top < 1) {
                    printf("Erro: Operando faltando para a operacao '*'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                float a = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, a * b);
            } else if (strcmp(verificaEspaco, "/") == 0) {
                if (Pilha.top < 1) {
                    printf("Erro: Operando faltando para a operacao '/'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                float a = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, a / b);
            } else if (strcmp(verificaEspaco, "^") == 0) {
                if (Pilha.top < 1) {
                    printf("Erro: Operando faltando para a operacao '^'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                float a = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, pow(a, b));
            } else if (strcmp(verificaEspaco, "raiz") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operando faltando para a operacao 'raiz'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, sqrt(b));
            } else if (strcmp(verificaEspaco, "sen") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operando faltando para a operacao 'sen'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, sin(b * PI / 180.0));
            } else if (strcmp(verificaEspaco, "cos") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operando faltando para a operacao 'cos'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, cos(b * PI / 180.0));
            } else if (strcmp(verificaEspaco, "tg") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operando faltando para a operacao 'tg'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, tan(b * PI / 180.0));
            } else if (strcmp(verificaEspaco, "log") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operando faltando para a operacao 'log'.\n");
                    exit(EXIT_FAILURE);
                }
                float b = tiraDaPilha(&Pilha);
                colocaNaPilha(&Pilha, log10(b));
            } else {
                printf("Operador desconhecido: %s\n", verificaEspaco);
                exit(EXIT_FAILURE);
            }
        }
        verificaEspaco = strtok(NULL, " ");
    }
    if (Pilha.top != 0) {
        printf("Erro: A pilha deveria conter apenas um valor final, mas contem %d valores.\n", Pilha.top + 1);
        exit(EXIT_FAILURE);
    }
    return tiraDaPilha(&Pilha);
}

char *getFormaPreFixa(char *Str) {
    static char preFixa[512];
    StringPilha Pilha = {.top = -1};
    char *verificaEspaco = strtok(Str, " ");
    while (verificaEspaco != NULL) {
        if (isdigit(verificaEspaco[0]) || (verificaEspaco[0] == '-' && isdigit(verificaEspaco[1]))) {
            char *operand = malloc(strlen(verificaEspaco) + 1);
            strcpy(operand, verificaEspaco);
            colocaNaPilhaString(&Pilha, operand);
        } else {
            if (strcmp(verificaEspaco, "log") == 0 || strcmp(verificaEspaco, "sen") == 0 || 
                strcmp(verificaEspaco, "cos") == 0 || strcmp(verificaEspaco, "tg") == 0 || strcmp(verificaEspaco, "raiz") == 0) {
                if (Pilha.top < 0) {
                    printf("Erro: Operandos faltando para a operacao '%s'.\n", verificaEspaco);
                    exit(EXIT_FAILURE);
                }
                char *a = tiraDaPilhaString(&Pilha);
                char *expr = malloc(strlen(a) + strlen(verificaEspaco) + 3);
                sprintf(expr, "%s %s", verificaEspaco, a);
                free(a);
                colocaNaPilhaString(&Pilha, expr);
            } else {
                if (Pilha.top < 1) {
                    printf("Erro: Operandos faltando para a operacao '%s'.\n", verificaEspaco);
                    exit(EXIT_FAILURE);
                }
                char *b = tiraDaPilhaString(&Pilha);
                char *a = tiraDaPilhaString(&Pilha);
                char *expr = malloc(strlen(a) + strlen(b) + strlen(verificaEspaco) + 4);
                sprintf(expr, "%s %s %s", verificaEspaco, a, b);
                free(a);
                free(b);
                colocaNaPilhaString(&Pilha, expr);
            }
        }
        verificaEspaco = strtok(NULL, " ");
    }
    if (Pilha.top != 0) {
        printf("Erro: A pilha deveria conter apenas um valor final, mas contem %d valores.\n", Pilha.top + 1);
        exit(EXIT_FAILURE);
    }
    strcpy(preFixa, tiraDaPilhaString(&Pilha));
    return preFixa;
}
