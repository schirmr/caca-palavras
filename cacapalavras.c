/* GRUPO: Gabriel Lorenson Schirmer e João Pedro Anony*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define TAM 16
#define CONT 20

char mat[TAM][TAM];
int pos[TAM][TAM];

void fix(){
    int i, j, aux;
    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            if(pos[i][j] == 1){
                if(mat[i][j] == mat[i][j+1] && mat[i][j] == mat[i][j+2] ||
                mat[i][j] == mat[i][j-1] && mat[i][j] == mat[i][j-2] ||
                mat[i][j] == mat[i+1][j] && mat[i][j] == mat[i+2][j] ||
                mat[i][j] == mat[i-1][j] && mat[i][j] == mat[i-2][j] ||
                mat[i][j] == mat[i+1][j+1] && mat[i][j] == mat[i+2][j+2] ||
                mat[i][j] == mat[i-1][j-1] && mat[i][j] == mat[i-2][j-2] ||
                mat[i][j] == mat[i-1][j-1] && mat[i][j] == mat[i+1][j+1] ||
                mat[i][j] == mat[i][j-1] && mat[i][j] == mat[i][j+1] ||
                mat[i][j] == mat[i-1][j] && mat[i][j] == mat[i+1][j]){
                aux = mat[i][j];
                while(mat[i][j] == aux){
                    mat[i][j] = 'a' + rand() % 26;}}}}}}

void preenchrandom() {
    int i, j;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            if (mat[i][j] == ' ') {
                mat[i][j] = 'a' + rand() % 26;
                pos[i][j] = 1;
            }}}
}

int permissao(char palavra[], int lin, int col, int dir, int invertida){
    int tam = strlen(palavra), i;
    for(i = 0;i < tam;i++){
    if(invertida){
        if (dir == 0) {
            if (mat[lin][col+tam-i-1] != ' ' && mat[lin][col+tam-i-1] != palavra[i]) return 0;}
        else if (dir == 1) {
            if (mat[lin+tam-i-1][col] != ' ' && mat[lin+tam-i-1][col] != palavra[i]) return 0;}
        else if (dir == 2) {
            if (mat[lin+tam-i-1][col+tam-i-1] != ' ' && mat[lin+tam-i-1][col+tam-i-1] != palavra[i]) return 0;}}
    else if(!invertida){
        if (dir == 0) {
            if (mat[lin][col+i] != ' ' && mat[lin][col+i] != palavra[i]) return 0;}
        else if (dir == 1) {
            if (mat[lin+i][col] != ' ' && mat[lin+i][col] != palavra[i]) return 0;}
        else if (dir == 2) {
            if (mat[lin+i][col+i] != ' ' && mat[lin+i][col+i] != palavra[i]) return 0;}}}
    if (dir == 0) {
        if (col + tam > TAM) return 0;}
    else if (dir == 1) {
        if (lin + tam > TAM) return 0;}
    else if (dir == 2) {
        if (col + tam > TAM || lin + tam > TAM) return 0;}
    return 1;
}

void posicao(char palavra[], int lin, int col, int dir, int invertida){
    int tam = strlen(palavra), i;
    if(invertida){
        for(i = 0; i < tam; i++){
            if (dir == 0) {
                mat[lin][col+tam-i-1] = palavra[i];}
            else if (dir == 1) {
                mat[lin+tam-i-1][col] = palavra[i];}
            else if (dir == 2) {
                mat[lin+tam-i-1][col+tam-i-1] = palavra[i];}
        }
    } else {
        for(i = 0; i < tam; i++){
            if (dir == 0) {
                mat[lin][col+i] = palavra[i];}
            else if (dir == 1) {
                mat[lin+i][col] = palavra[i];}
            else if (dir == 2) {
                mat[lin+i][col+i] = palavra[i];}
        }}}

int main(){
    setlocale(LC_ALL,"Portuguese");
    srand((unsigned)time(NULL));
    char palavras[CONT][11];/*{"gabriel","monique","hique","matheus","polga",
                            "felipe","thiago","julia","teste","avestruz",
                            "lontra","teclado","mouse","alicia","leandro",
                            "jonatan","chico","bernardo","francisco","anony"};*/
    char palavrajogo[11];
    int certos[CONT]={0};
    int i, j, tent = 0, lin, col, dir, acertos, sen, tam, contem = 0;
    printf("Digite 20 palavras com pelo menos 5 letras e no máximo 10 letras: (em minúsculo) \n");
    for(i=0;i<CONT;i++){
        scanf("%s", palavras[i]);
        if(strlen(palavras[i])<5 || strlen(palavras[i])>10){
            printf("Erro palavra não corresponde ao critério.\n");
            i--;
        }}
    for(i = 0; i < TAM; i++) {
        for(j = 0; j < TAM; j++) {
            mat[i][j] = ' ';
        }}
   for (i = 0; i < CONT; i++){
    while (tent<10000){
        lin = rand() % TAM;
        col = rand() % TAM;
        dir = rand() % 3;
        int inserirInvertida = rand() % 10 == 0;

        if(inserirInvertida && permissao(palavras[i], lin, col, dir, inserirInvertida)){
            posicao(palavras[i], lin, col, dir, 1);
            break;
        } else if(permissao(palavras[i], lin, col, dir, inserirInvertida)){
            posicao(palavras[i], lin, col, dir, 0);
            break;
        }
        tent++;
    }
    if (tent == 10000) {
        printf("Nao foi possivel posicionar essa palavra.");
        return 1;
    }
}
    preenchrandom();
    fix();
    for(acertos = 0; acertos<20;){
        printf("Caça Palavras:\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%c ", mat[i][j]);}
        printf("\n");
    }
    while(contem != 1){
    printf("Digite qual palavra você encontrou: ");
    scanf("%s", palavrajogo);
    tam = strlen(palavrajogo);
        for(i=0;i<20;i++){
            if(!strcmp(palavrajogo, palavras[i])){
               if(certos[i] == 1){
                    printf("Essa palavra já foi achada.\n");
                    break;}
                else{
                    contem = 1;
                    break;}}
            else if(i == 19)printf("Essa palavra não contém no caça palavras.\n");}
        }
    printf("Digite a linha da palavra: (0 a 15): ");
    scanf("%d", &lin);
    printf("Digite a coluna da palavra: (0 a 15): ");
    scanf("%d", &col);
    printf("Digite o direção da palavra: (0 - Vertical)(1 - Horizontal)(2 - Diagonal): ");
    scanf("%d", &dir);
    printf("Digite o sentido da palavra: (1 - Invertido) (0 - Normal): ");
    scanf("%d", &sen);
    for(j = 0;j < tam; j++){
        if(sen == 0){
            if(dir == 1){
                if(mat[lin][col+j] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;}}
            else if(dir == 0){
                if(mat[lin+j][col] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;}}
            else if(dir == 2){
                if(mat[lin+j][col+j] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;
             }}}
        else if(sen == 1){
            if(dir == 1){
                if(mat[lin][col-j] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;}}
            else if(dir == 0){
                if(mat[lin-j][col] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;}}
            else if(dir == 2){
                if(mat[lin-j][col-j] == palavras[i][j]){
                    if(j+1 == tam){
                    acertos++;
                    printf("Você acertou!\nPontuação:%d\n", acertos);
                    certos[i] = 1;
                    break;}}
                else{
                    printf("Você errou!\nPontuação:%d\n", acertos);
                    break;}}}
            else printf("Sentido inválido\n");}
    contem = 0;
    if(acertos == 20){
        printf("\nParabens você encontrou todas as palavras!!\n");
        return 0;}}}
