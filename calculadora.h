#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512]; // Expressão na forma pós-fixada, como 3 12 4 + *
    char preFixa[512]; // Expressão na forma prefixada, como + 3 * 4 12
    float valor; // Valor numérico da expressão
} Expressao;

char *getFormaPreFixa(char *Str); // Retorna a forma prefixada de Str (pós-fixada)
float getValor(char *Str); // Calcula o valor de Str (na forma pós-fixada)

#endif