/* nó da lista para armazenar valores reais */
struct lista {
	char info;
	struct lista* prox;
};
typedef struct lista Lista;
/* estrutura da fila */
struct fila {
	Lista* ini;
	Lista* fim;
};
typedef struct fila Fila;

Fila* fila_cria (void){
	Fila *f=(Fila*)malloc(sizeof(Fila));
	f->ini=NULL;
	f->fim=NULL;
	return f;
}

void fila_insere(Fila *p, int x){
	if (p->ini == NULL){
		Lista *l=(Lista*)malloc(sizeof(Lista));
		l->info=x;
		p->ini=l;
		p->fim=l;
		l->prox=p->fim;
	}
	else{
		Lista *l=(Lista*)malloc(sizeof(Lista));
		l->info=x;
		l->prox=p->ini;
		p->fim->prox=l;
		l->prox=p->ini;
		p->fim=l;
	}
}
char fila_retira(Fila *p){

	if (p->ini!=NULL){
		if (p->ini == p->fim){
			char aux2=p->ini->info;
			free(p->ini);
			p->fim=NULL;
			p->ini=NULL;
			return aux2;
		}
		else{
			Lista *aux;
			char valor;
			aux=p->ini;
			valor = aux->info;
			p->ini=p->ini->prox;
			free (aux);
			p->fim->prox=p->ini;
			return valor;

		}
	}
}
char fila_vazia(Fila *p){
	if (p->ini!=NULL){
		return 0; //não é vazia
	}
	else{
		return 1; //é vazia
	}
}
void fila_libera(Fila *p){
	Lista *l,*aux;
	l=p->ini;
	while (l!=p->fim){
		aux=l;
		l=l->prox;
		free (aux);
	}
	free (p->fim);
	p->ini=p->fim=NULL;
}

void fila_imprime(Fila *p){
	Lista *aux;
	aux=p->ini;
	printf ("%c ",aux->info);
	aux=aux->prox;
	while (aux!=p->ini){
		printf ("%c ",aux->info);
		aux=aux->prox;
	}
}
