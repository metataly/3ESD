/*Construa o programa a seguir.
a. Faça a função horario que receba um parâmetro (inteiro por valor) com o total de
minutos de um evento e receba também dois parâmetros (inteiros por referência) no
qual deve preencher a quantidade de hora e de minutos equivalente. Por exemplo:
145 minutos equivale a 2 h e 25 min. Esta função deverá OBRIGATORIAMENTE chamar
a função DivisaoInteira
b. Faça um programa que leia o tempo de treino (em minutos) de 10 atletas, mostrando
a cada um, o tempo de treino no formato hh:mm. (utilize a função do item a).
No final deve ser exibido o maior tempo de treino e quantos atletas o fizeram */

/*Passar min para horas na exibição final?*/

#include <stdio.h>
#include <string.h>
#define TAM 2

//definição de tipos
typedef struct{
    int codigo, tempo;
    char nome[25];
} TAtleta;

//protótipos da função
int Divisaoint (int dividendo, int divisor, int *quociente, int *resto);
void horario (int minutoTotal, int *horas, int *minutos);
void LeAtleta (TAtleta atletas[], int tamanho);
void trocar (TAtleta atletas[], int i, int j);
void exibir (TAtleta [], int tamanho, int contador, int maiorTempo);

//função main
int main (void){
    TAtleta at[TAM], aux;
    int i, j, maiorT, cont = 1, pos;

    //chamando a função para preencher os dados dos atletas
    LeAtleta (at, TAM);


    maiorT = at[0].tempo;

    // achando o maior tempo
    for (i = 1; i < TAM; i++) {
        if (at[i].tempo > maiorT) {
            maiorT = at[i].tempo;
            cont = 1;
        } 
        else if (at[i].tempo == maiorT) {
            cont++;
        }
    }

    // ordenando os atletas
    for (i=0; i<TAM; i++) {
        for (j=1; j<TAM; j++) {
            // ordenando primeiro pelo tempo e em caso de empate pelo nome
            if ((at[i].tempo < at[j].tempo) || (at[i].tempo == at[j].tempo && strcmp(at[i].nome, at[j].nome) > 0)) {
                trocar(at, i, j);
            }
        }
    }

    exibir (at, TAM, cont, maiorT);
    
}

//funções auxiliares
void LeAtleta (TAtleta atletas[], int tamanho){

    int i, h, min;

    //preenchendo a struct com os 10 atletas
    for(i=0; i<tamanho; i++){
        printf("Digite o nome do Atleta: \n");
        fgets(atletas[i].nome, 25, stdin);

        // removendo o '\n' que fica no final da string
        atletas[i].nome[strcspn(atletas[i].nome, "\n")] = '\0';

        printf("Digite o codigo do Atleta: \n");
        scanf("%d", &atletas[i].codigo);
        getchar(); //limpando o buffer

        printf("Digite o tempo em minutos do Atleta: \n");
        scanf("%d", &atletas[i].tempo);
        getchar();

        horario (atletas[i].tempo, &h, &min); //deveria trocar o tempo por hh:mm ?
        printf("O tempo de treino em hh:mm: \n[Atleta: %s | cod: %d ] => %dh %dmin \n", atletas[i].nome, atletas[i].codigo, h, min);
        printf("________________________________________\n\n");
    }

}

int Divisaoint (int dividendo, int divisor, int *quociente, int *resto){

    if (divisor==0){
        if (dividendo==0){
            return -1; //indeterminado
        } 
        else{
            return 0; //impossivel
        }
    }
    else{
        *quociente = dividendo / divisor;
        *resto = dividendo % divisor;

        return 1;
    }
}

void horario (int minutoTotal, int *horas, int *minutos){
    Divisaoint (minutoTotal, 60, horas, minutos);
}

void trocar(TAtleta atletas[], int i, int j) {
    TAtleta aux;
    aux = atletas[i];
    atletas[i] = atletas[j];
    atletas[j] = aux;
}

void exibir (TAtleta atletas[], int tamanho, int contador, int maiorTempo){
    int i, h, min;

    printf("Hanking de Atletas\n\n");
    printf("[ NOME ]      [ COD ]     [ TEMPO ]  \n");

    for (i=0; i<tamanho; i++){
        //exibindo em horas? ou pode ficar em minutos?
        horario(atletas[i].tempo, &h, &min);
        printf("%s\t\t", atletas[i].nome);
        printf("%d\t\t", atletas[i].codigo);
        printf("%dh %dmin", h, min);
        printf("\n--------------------------------------\n");
    }
    
    horario(maiorTempo, &h, &min);
    printf("[ %d ] Atleta(s) realizou/realizaram o Maior Tempo de Treino de %dh %dmin\n", contador, h, min);
}