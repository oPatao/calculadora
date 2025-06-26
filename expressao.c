#include "expressao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

void inicializarPilhaFloat(PilhaFloat *s) {
    s->topo = -1;
}

void empilharFloat(PilhaFloat *s, float valor) {
    if (s->topo < MAXIMO_PILHA - 1) {
        s->items[++s->topo] = valor;
    } else {
        printf("Erro: Pilha de floats cheia.\n");
        exit(EXIT_FAILURE);
    }
}

float desempilharFloat(PilhaFloat *s) {
    if (s->topo >= 0) {
        return s->items[s->topo--];
    } else {
        printf("Erro: Pilha de floats vazia.\n");
        exit(EXIT_FAILURE);
    }
}

void inicializarPilhaString(PilhaString *s) {
    s->topo = -1;
}

void empilharString(PilhaString *s, char *valor) {
    if (s->topo < MAXIMO_PILHA - 1) {
        s->items[++s->topo] = valor;
    } else {
        printf("Erro: Pilha de strings cheia.\n");
        exit(EXIT_FAILURE);
    }
}

char* desempilharString(PilhaString *s) {
    if (s->topo >= 0) {
        return s->items[s->topo--];
    } else {
        printf("Erro: Pilha de strings vazia.\n");
        exit(EXIT_FAILURE);
    }
}

char* verTopoString(PilhaString *s) {
    if (s->topo >= 0) {
        return s->items[s->topo];
    }
    return NULL;
}

int ehOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

int ehAssociativoEsquerda(char op) {
    return !(op == '^');
}

int ehFuncao(const char *s) {
    return (strcmp(s, "raiz") == 0 || strcmp(s, "sen") == 0 ||
            strcmp(s, "cos") == 0 || strcmp(s, "tg") == 0 || strcmp(s, "log") == 0);
}

// Funções de verificação de caracteres personalizadas
int ehDigito(char c) {
    return (c >= '0' && c <= '9');
}

int ehEspaco(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

int ehLetra(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

float getValorPosFixa(char *strPosFixa) {
    PilhaFloat s;
    inicializarPilhaFloat(&s);

    char *copia_str = strdup(strPosFixa);
    if (copia_str == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }

    char *elemento = strtok(copia_str, " ");
    while (elemento != NULL) {
        if (ehDigito(elemento[0]) || (elemento[0] == '-' && ehDigito(elemento[1]))) {
            empilharFloat(&s, atof(elemento));
        } else if (ehOperador(elemento[0]) || ehFuncao(elemento)) {
            float val2, val1;
            if (strcmp(elemento, "+") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '+'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                empilharFloat(&s, val1 + val2);
            } else if (strcmp(elemento, "-") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '-'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                empilharFloat(&s, val1 - val2);
            } else if (strcmp(elemento, "*") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '*'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                empilharFloat(&s, val1 * val2);
            } else if (strcmp(elemento, "/") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '/'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                if (val2 == 0) { printf("Erro: Divisao por zero.\n"); exit(EXIT_FAILURE); }
                empilharFloat(&s, val1 / val2);
            } else if (strcmp(elemento, "%") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '%'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                if (val2 == 0) { printf("Erro: Modulo por zero.\n"); exit(EXIT_FAILURE); }
                empilharFloat(&s, fmod(val1, val2));
            } else if (strcmp(elemento, "^") == 0) {
                if (s.topo < 1) { printf("Erro: Operandos insuficientes para '^'.\n"); exit(EXIT_FAILURE); }
                val2 = desempilharFloat(&s);
                val1 = desempilharFloat(&s);
                empilharFloat(&s, pow(val1, val2));
            } else if (strcmp(elemento, "raiz") == 0) {
                if (s.topo < 0) { printf("Erro: Operando insuficiente para 'raiz'.\n"); exit(EXIT_FAILURE); }
                val1 = desempilharFloat(&s);
                if (val1 < 0) { printf("Erro: Raiz quadrada de numero negativo.\n"); exit(EXIT_FAILURE); }
                empilharFloat(&s, sqrt(val1));
            } else if (strcmp(elemento, "sen") == 0) {
                if (s.topo < 0) { printf("Erro: Operando insuficiente para 'sen'.\n"); exit(EXIT_FAILURE); }
                val1 = desempilharFloat(&s);
                empilharFloat(&s, sin(val1 * PI / 180.0));
            } else if (strcmp(elemento, "cos") == 0) {
                if (s.topo < 0) { printf("Erro: Operando insuficiente para 'cos'.\n"); exit(EXIT_FAILURE); }
                val1 = desempilharFloat(&s);
                empilharFloat(&s, cos(val1 * PI / 180.0));
            } else if (strcmp(elemento, "tg") == 0) {
                if (s.topo < 0) { printf("Erro: Operando insuficiente para 'tg'.\n"); exit(EXIT_FAILURE); }
                val1 = desempilharFloat(&s);
                double angulo_rad = val1 * PI / 180.0;
                if (fabs(cos(angulo_rad)) < 1e-9) {
                    printf("Erro: Tangente de angulo invalido (proximo de 90/270 graus).\n");
                    exit(EXIT_FAILURE);
                }
                empilharFloat(&s, tan(angulo_rad));
            } else if (strcmp(elemento, "log") == 0) {
                if (s.topo < 0) { printf("Erro: Operando insuficiente para 'log'.\n"); exit(EXIT_FAILURE); }
                val1 = desempilharFloat(&s);
                if (val1 <= 0) { printf("Erro: Logaritmo de numero nao positivo.\n"); exit(EXIT_FAILURE); }
                empilharFloat(&s, log10(val1));
            } else {
                printf("Erro: Operador ou funcao desconhecida: '%s'.\n", elemento);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Erro: Elemento inesperado ou invalido: '%s'.\n", elemento);
            exit(EXIT_FAILURE);
        }
        elemento = strtok(NULL, " ");
    }

    if (s.topo != 0) {
        printf("Erro: Expressao pos-fixada mal formada. Pilha final com %d elementos.\n", s.topo + 1);
        exit(EXIT_FAILURE);
    }

    float resultado = desempilharFloat(&s);
    free(copia_str);
    return resultado;
}

char *getFormaInFixa(char *strPosFixa) {
    static char resultadoInFixa[MAX_EXPRESSAO];
    PilhaString s;
    inicializarPilhaString(&s);

    char *copia_str = strdup(strPosFixa);
    if (copia_str == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }

    char *elemento = strtok(copia_str, " ");
    while (elemento != NULL) {
        if (ehDigito(elemento[0]) || (elemento[0] == '-' && ehDigito(elemento[1]))) {
            empilharString(&s, strdup(elemento));
        } else if (ehOperador(elemento[0])) {
            if (s.topo < 1) { printf("Erro: Operandos insuficientes para '%s'.\n", elemento); exit(EXIT_FAILURE); }
            char *op2 = desempilharString(&s);
            char *op1 = desempilharString(&s);

            char *nova_expr = malloc(MAX_EXPRESSAO);
            if (nova_expr == NULL) {
                printf("Erro de alocacao de memoria.\n");
                exit(EXIT_FAILURE);
            }
            sprintf(nova_expr, "(%s %c %s)", op1, elemento[0], op2);
            
            free(op1);
            free(op2);
            empilharString(&s, nova_expr);
        } else if (ehFuncao(elemento)) {
            if (s.topo < 0) { printf("Erro: Operando insuficiente para '%s'.\n", elemento); exit(EXIT_FAILURE); }
            char *op1 = desempilharString(&s);

            char *nova_expr = malloc(MAX_EXPRESSAO);
            if (nova_expr == NULL) {
                printf("Erro de alocacao de memoria.\n");
                exit(EXIT_FAILURE);
            }
            sprintf(nova_expr, "%s(%s)", elemento, op1);
            
            free(op1);
            empilharString(&s, nova_expr);
        } else {
            printf("Erro: Elemento desconhecido ou invalido em pos-fixada para infixada: '%s'.\n", elemento);
            exit(EXIT_FAILURE);
        }
        elemento = strtok(NULL, " ");
    }

    if (s.topo != 0) {
        printf("Erro: Expressao pos-fixada mal formada para conversao infixada. Pilha final com %d elementos.\n", s.topo + 1);
        exit(EXIT_FAILURE);
    }

    strcpy(resultadoInFixa, desempilharString(&s));
    free(copia_str);

    return resultadoInFixa;
}

char *getFormaPosFixa(char *strInFixa) {
    static char resultadoPosFixa[MAX_EXPRESSAO];
    PilhaString pilhaOperadores;
    inicializarPilhaString(&pilhaOperadores);

    char saida[MAX_EXPRESSAO * 2];
    saida[0] = '\0';

    char *copia_str = strdup(strInFixa);
    if (copia_str == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }

    char *ponteiro = copia_str;
    char buffer_elemento[MAX_EXPRESSAO];
    
    while (*ponteiro != '\0') {
        if (ehEspaco(*ponteiro)) {
            ponteiro++;
            continue;
        }

        if (ehDigito(*ponteiro) || (*ponteiro == '-' && ehDigito(*(ponteiro+1)))) {
            sscanf(ponteiro, "%s", buffer_elemento);
            strcat(saida, buffer_elemento);
            strcat(saida, " ");
            ponteiro += strlen(buffer_elemento);
        } else if (ehOperador(*ponteiro) || *ponteiro == '(' || *ponteiro == ')') {
            buffer_elemento[0] = *ponteiro;
            buffer_elemento[1] = '\0';
            ponteiro++;

            if (buffer_elemento[0] == '(') {
                empilharString(&pilhaOperadores, strdup(buffer_elemento));
            } else if (buffer_elemento[0] == ')') {
                while (pilhaOperadores.topo >= 0 && strcmp(verTopoString(&pilhaOperadores), "(") != 0) {
                    char *operador = desempilharString(&pilhaOperadores);
                    strcat(saida, operador);
                    strcat(saida, " ");
                    free(operador);
                }
                if (pilhaOperadores.topo < 0) {
                    printf("Erro: Parenteses desbalanceados ou ausentes.\n");
                    exit(EXIT_FAILURE);
                }
                free(desempilharString(&pilhaOperadores));

                if (pilhaOperadores.topo >= 0 && ehFuncao(verTopoString(&pilhaOperadores))) {
                    char *operador_funcao = desempilharString(&pilhaOperadores);
                    strcat(saida, operador_funcao);
                    strcat(saida, " ");
                    free(operador_funcao);
                }
            } else {
                while (pilhaOperadores.topo >= 0 && strcmp(verTopoString(&pilhaOperadores), "(") != 0 &&
                       (precedencia(verTopoString(&pilhaOperadores)[0]) > precedencia(buffer_elemento[0]) ||
                        (precedencia(verTopoString(&pilhaOperadores)[0]) == precedencia(buffer_elemento[0]) && ehAssociativoEsquerda(buffer_elemento[0])))) {
                    char *operador = desempilharString(&pilhaOperadores);
                    strcat(saida, operador);
                    strcat(saida, " ");
                    free(operador);
                }
                empilharString(&pilhaOperadores, strdup(buffer_elemento));
            }
        } else if (ehLetra(*ponteiro)) {
            sscanf(ponteiro, "%s", buffer_elemento);
            if (ehFuncao(buffer_elemento)) {
                empilharString(&pilhaOperadores, strdup(buffer_elemento));
                ponteiro += strlen(buffer_elemento);
            } else {
                printf("Erro: Elemento invalido (nao eh operador, operando ou funcao): '%s'.\n", buffer_elemento);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Erro: Caractere invalido na expressao infixada: '%c'.\n", *ponteiro);
            exit(EXIT_FAILURE);
        }
    }

    while (pilhaOperadores.topo >= 0) {
        char *operador = desempilharString(&pilhaOperadores);
        if (strcmp(operador, "(") == 0 || strcmp(operador, ")") == 0) {
            printf("Erro: Parenteses desbalanceados.\n");
            exit(EXIT_FAILURE);
        }
        strcat(saida, operador);
        strcat(saida, " ");
        free(operador);
    }

    if (strlen(saida) > 0 && saida[strlen(saida) - 1] == ' ') {
        saida[strlen(saida) - 1] = '\0';
    }

    strcpy(resultadoPosFixa, saida);
    free(copia_str);

    while (pilhaOperadores.topo >= 0) {
        free(desempilharString(&pilhaOperadores));
    }

    return resultadoPosFixa;
}

float getValorInFixa(char *strInFixa) {
    char *posFixa = getFormaPosFixa(strInFixa);

    char copiaPosFixa[MAX_EXPRESSAO];
    strcpy(copiaPosFixa, posFixa);
    return getValorPosFixa(copiaPosFixa);
}
