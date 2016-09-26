#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO
// Modificar o fila_remove(deve remover no início), ou utilizar o fila_imprime para a conversão
// Trazer funções utilizadas para este arquivo
// definir valor de chave


/* nó da lista para armazenar valores reais */
struct lista
{
    char info;
    struct lista* prox;
};
typedef struct lista Lista;
/* estrutura da fila */
struct fila
{
    Lista* ini;
    Lista* fim;
};
typedef struct fila Fila;


/*Inicializa a estrutura que armazena a mensagem*/
Fila* fila_cria (void)
{
    Fila *f=(Fila*)malloc(sizeof(Fila));
    f->ini=NULL;
    f->fim=NULL;
    return f;
}

/*Insere a letra na lista*/
void fila_insere(Fila *p, int x)
{
    if (p->ini == NULL)
    {
        Lista *l=(Lista*)malloc(sizeof(Lista));
        l->info=x;
        p->ini=l;
        p->fim=l;
        l->prox=p->fim;
    }
    else
    {
        Lista *l=(Lista*)malloc(sizeof(Lista));
        l->info=x;
        l->prox=p->ini;
        p->fim->prox=l;
        l->prox=p->ini;
        p->fim=l;
    }
}

/*Verifica se há mensagem*/
char fila_vazia(Fila *p)
{
    if (p->ini!=NULL)
    {
        return 0; //não é vazia
    }
    else
    {
        return 1; //é vazia
    }
}

/*Responsável pelo free dos ponteiros*/
void fila_libera(Fila *p)
{
    Lista *l,*aux;
    l=p->ini;
    while (l!=p->fim)
    {
        aux=l;
        l=l->prox;
        free (aux);
    }
    free (p->fim);
    p->ini=p->fim=NULL;
}


/*Imprime na tela a mensagem*/
void fila_imprime(Fila *p)
{
    Lista *aux;
    aux=p->ini;
    printf ("%c",aux->info);
    aux=aux->prox;
    while (aux!=p->ini)
    {
        printf ("%c",aux->info);
        aux=aux->prox;
    }
}


/*Função que lê cada letra inputada pelo usuário e retorna a mensagem em forma de lista de char(chamada aqui de fila)*/
Fila* readString(Fila *mensagem)
{
    char temp = "";
    while(temp != '#')
    {
        temp = getchar();
        if (temp != '#')
        {
            fila_insere(mensagem,temp);
        };
    };
    return mensagem;
};


/*As funções de encriptar e decriptar seguem a mesma lógica, porém com operações inversas*/
Fila* encripta_mensagem(Fila *p, long int chave)
{
    Lista *aux;
    aux=p->ini->prox;   //Início da mensagem.
    long int ascii;      //Armazena o valor da soma chave + letra para saber quantas "voltas" dará no alfabeto.
    while (aux!=p->ini)
    {
            /*CARACTERES ESPECIAIS: (spacebar), Exclamação, Apóstrofo ('), Vírgula, Hífen, Ponto Final, Barra(/), Numerais (0-9), Dois Pontos,
            Ponto e vírgula e Interrogação*/
        if (aux->info == 32 || aux->info == 33 || aux->info == 39 || aux->info == 44 || aux->info == 45 || aux->info == 46
             || aux->info == 47 || aux->info == 48 || aux->info == 49 || aux->info == 50 || aux->info == 51 || aux->info == 52
              || aux->info == 53 || aux->info == 54 || aux->info == 55 || aux->info == 56 || aux->info == 57 || aux->info == 58 || aux->info == 59
               || aux->info == 63)
        {
            aux=aux->prox;
            continue;
        }
        printf("Letra original: %c (%d)\n", aux->info, aux->info);
        printf("Chave original: %d\n", chave);
        ascii = aux->info + chave;
        for (int i = 0; i < chave/26; i++)
        {
            ascii = ascii - 90;
            printf("Corrigindo: %d\n", ascii);          /* Mantém os valores dentro das letras maiúsculas (65-90) */
            ascii = ascii + 64;
            printf("Corrigindo: %d\n", ascii);
        }
        if (ascii > 90)
        {
            ascii = ascii - 90;             /* Esse aqui serve pra assegurar que nenhum escape do range (65-90) das letras */
            ascii = ascii + 64;
        }
        aux->info = ascii;      //Letra encriptada
        printf("Letra encriptada: %c (%d)\n", aux->info, aux->info);
        chave = chave + (ascii - 64);   //Nova chave
        printf("Nova chave: %d\n", chave);
        aux=aux->prox;      //Próxima letra
    }
    return p;   //Retorna mensagem encriptada.
}



void encrypt()
{
    printf("\nDigite o valor da chave: \n");
    long int chave;
    scanf("%d", &chave);
    printf("Digite a mensagem:\n");
    Fila *mensagem = fila_cria();
    mensagem = readString(mensagem); //Lê os dados inputados pelo usuário e armazena em forma de lista
    fila_imprime(mensagem);
    printf("\n");
    Fila *encrypted = fila_cria();
    encrypted = encripta_mensagem(mensagem, chave); //Função recebe a mensagem do usuário e a encripta, retornando a versão encriptada em uma variável
    fila_imprime(encrypted);
    fila_libera(mensagem);
    fila_libera(encrypted);
    printf("\n");
    printf("\n");
    system("PAUSE");
    return;
};


/*As funções de encriptar e decriptar seguem a mesma lógica, porém com operações inversas*/
Fila* decripta_mensagem(Fila *p, long int chave)
{
    Lista *aux;
    aux=p->ini->prox;   //Início da mensagem.
    long int ascii;      //Armazena o valor da soma chave + letra para saber quantas "voltas" dará no alfabeto.
    while (aux!=p->ini)
    {
            /*CARACTERES ESPECIAIS: (spacebar), Exclamação, Apóstrofo ('), Vírgula, Hífen, Ponto Final, Barra(/), Numerais (0-9), Dois Pontos,
            Ponto e vírgula e Interrogação*/
        if (aux->info == 32 || aux->info == 33 || aux->info == 39 || aux->info == 44 || aux->info == 45 || aux->info == 46
             || aux->info == 47 || aux->info == 48 || aux->info == 49 || aux->info == 50 || aux->info == 51 || aux->info == 52
              || aux->info == 53 || aux->info == 54 || aux->info == 55 || aux->info == 56 || aux->info == 57 || aux->info == 58 || aux->info == 59
               || aux->info == 63)
        {
            aux=aux->prox;
            continue;
        }
        printf("Letra original: %c (%d)\n", aux->info, aux->info);
        printf("Chave original: %d\n", chave);
        ascii = aux->info - chave;
        for (int i = 0; i < chave/26; i++)
        {
            ascii = ascii + 90;
            printf("Corrigindo: %d\n", ascii);          /* Mantém os valores dentro das letras maiúsculas (65-90) */
            ascii = ascii - 64;
            printf("Corrigindo: %d\n", ascii);
        }
        if (ascii < 65)
        {
            ascii = ascii + 90;             /* Esse aqui serve pra assegurar que nenhum escape do range (65-90) das letras */
            ascii = ascii - 64;
        }
        chave = chave + (aux->info - 64);   //Nova chave
        printf("Nova chave: %d\n", chave);
        aux->info = ascii;      //Letra decriptada
        printf("Letra decriptada: %c (%d)\n", aux->info, aux->info);
        aux=aux->prox;      //Próxima letra
    }
    return p;   //Retorna mensagem decriptada.
}

void decrypt()
{
    printf("\nDigite o valor da chave: \n");
    long int chave;
    scanf("%d", &chave);
    printf("Digite a mensagem:\n");
    Fila *mensagem = fila_cria();
    mensagem = readString(mensagem);    //Lê os dados inputados pelo usuário e armazena em forma de lista
    fila_imprime(mensagem);
    printf("\n");
    Fila *decrypted = fila_cria();
    decrypted = decripta_mensagem(mensagem, chave); //Função recebe a mensagem do usuário e a decripta, retornando a versão decriptada em uma variável
    fila_imprime(decrypted);
    fila_libera(mensagem);
    fila_libera(decrypted);
    printf("\n");
    printf("\n");
    system("PAUSE");
    return;
};

void menu()
{
    char opt="";
    while (opt != "E" && opt != "D" && opt != "S")
    {
        printf("Digite D para decriptar e E para encriptar e S para sair\n");
        scanf("%c",&opt);
        switch(opt)
        {
        case 'E':
            encrypt();
            break;
        case 'D':
            decrypt();
            break;
        case 'S':
            exit(0);
            break;

        default :
            printf("Opcao invalida\n");
        };
    };
    return;
};


int main()
{
    menu();
    exit(0);

}
