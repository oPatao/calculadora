#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#define MAX_EXPRESSAO 512
#define MAXIMO_PILHA 100

typedef struct {
    float items[MAXIMO_PILHA];
    int topo;
} PilhaFloat;

typedef struct {
    char *items[MAXIMO_PILHA];
    int topo;
} PilhaString;

typedef struct {
    char posFixa[MAX_EXPRESSAO];
    char inFixa[MAX_EXPRESSAO];
    float Valor;
} Expressao;

void inicializarPilhaFloat(PilhaFloat *s);
void empilharFloat(PilhaFloat *s, float valor);
float desempilharFloat(PilhaFloat *s);

void inicializarPilhaString(PilhaString *s);
void empilharString(PilhaString *s, char *valor);
char* desempilharString(PilhaString *s);
char* verTopoString(PilhaString *s);

int ehOperador(char c);
int precedencia(char op);
int ehAssociativoEsquerda(char op);
int ehFuncao(const char *s);


int ehDigito(char c);
int ehEspaco(char c);
int ehLetra(char c);

char *getFormaInFixa(char *strPosFixa);

char *getFormaPosFixa(char *strInFixa);

float getValorPosFixa(char *strPosFixa);

float getValorInFixa(char *strInFixa);

#endif // EXPRESSAO_H
