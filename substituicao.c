#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO
// Modificar o fila_remove(deve remover no in�cio), ou utilizar o fila_imprime para a convers�o
// Trazer fun��es utilizadas para este arquivo
// definir valor de chave


/* n� da lista para armazenar valores reais */
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

/*Verifica se h� mensagem*/
char fila_vazia(Fila *p)
{
    if (p->ini!=NULL)
    {
        return 0; //n�o � vazia
    }
    else
    {
        return 1; //� vazia
    }
}

/*Respons�vel pelo free dos ponteiros*/
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


/*Fun��o que l� cada letra inputada pelo usu�rio e retorna a mensagem em forma de lista de char(chamada aqui de fila)*/
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


/*As fun��es de encriptar e decriptar seguem a mesma l�gica, por�m com opera��es inversas*/
Fila* encripta_mensagem(Fila *p, long int chave)
{
    Lista *aux;
    aux=p->ini->prox;   //In�cio da mensagem.
    long int ascii;      //Armazena o valor da soma chave + letra para saber quantas "voltas" dar� no alfabeto.
    while (aux!=p->ini)
    {
            /*CARACTERES ESPECIAIS: (spacebar), Exclama��o, Ap�strofo ('), V�rgula, H�fen, Ponto Final, Barra(/), Numerais (0-9), Dois Pontos,
            Ponto e v�rgula e Interroga��o*/
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
            printf("Corrigindo: %d\n", ascii);          /* Mant�m os valores dentro das letras mai�sculas (65-90) */
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
        aux=aux->prox;      //Pr�xima letra
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
    mensagem = readString(mensagem); //L� os dados inputados pelo usu�rio e armazena em forma de lista
    fila_imprime(mensagem);
    printf("\n");
    Fila *encrypted = fila_cria();
    encrypted = encripta_mensagem(mensagem, chave); //Fun��o recebe a mensagem do usu�rio e a encripta, retornando a vers�o encriptada em uma vari�vel
    fila_imprime(encrypted);
    fila_libera(mensagem);
    fila_libera(encrypted);
    printf("\n");
    printf("\n");
    system("PAUSE");
    return;
};


/*As fun��es de encriptar e decriptar seguem a mesma l�gica, por�m com opera��es inversas*/
Fila* decripta_mensagem(Fila *p, long int chave)
{
    Lista *aux;
    aux=p->ini->prox;   //In�cio da mensagem.
    long int ascii;      //Armazena o valor da soma chave + letra para saber quantas "voltas" dar� no alfabeto.
    while (aux!=p->ini)
    {
            /*CARACTERES ESPECIAIS: (spacebar), Exclama��o, Ap�strofo ('), V�rgula, H�fen, Ponto Final, Barra(/), Numerais (0-9), Dois Pontos,
            Ponto e v�rgula e Interroga��o*/
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
            printf("Corrigindo: %d\n", ascii);          /* Mant�m os valores dentro das letras mai�sculas (65-90) */
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
        aux=aux->prox;      //Pr�xima letra
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
    mensagem = readString(mensagem);    //L� os dados inputados pelo usu�rio e armazena em forma de lista
    fila_imprime(mensagem);
    printf("\n");
    Fila *decrypted = fila_cria();
    decrypted = decripta_mensagem(mensagem, chave); //Fun��o recebe a mensagem do usu�rio e a decripta, retornando a vers�o decriptada em uma vari�vel
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
