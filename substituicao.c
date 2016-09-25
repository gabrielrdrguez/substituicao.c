#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
//TODO
// Modificar o fila_remove(deve remover no início), ou utilizar o fila_imprime para a conversão
// Trazer funções utilizadas para este arquivo
// definir valor de chave



Fila* readString(Fila *mensagem){
    char temp = "";
    while(temp != '#'){
        temp = getchar();
        if (temp != '#'){
            fila_insere(mensagem,temp);
        };
    };
    return mensagem;
};

int encripta_char(int valor_anterior, char c){ // para ser utilizar no encrypt, char a char, aritmética com a chave
}

void encrypt(){
    printf("\n Digite o valor da chave: \n")
    int chave = scanf(" %d", &chave);
    printf("Digite a mensagem:\n");
    Fila *mensagem = fila_cria();
    mensagem = readString(mensagem);
    fila_imprime(mensagem);
    system("PAUSE");
    return;
};
void decrypt(){

};

void menu(){
    char opt="";
    while (opt != "E" && opt != "D" && opt != "S") {
    printf("Digite D para decriptar e E para encriptar e S para sair\n");
    scanf("%c",&opt);
        switch(opt){
            case 'E':
                encrypt();
                break;
            case 'D':
                printf("decrypt");
                //decrypt();
                break;
            case 'S':
                exit(0);
                break;

            default : printf("Opcao invalida");
        };
    };
    return;
};


int main(){
    menu();
    exit(0);

}
