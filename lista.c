/*
 Funções relativas a lista de pontos da quadTree
 */

#include "quadtree.h"

listaPontos* InserePontoLista(listaPontos* lista, double x, double y)
{
    listaPontos* novo = malloc(sizeof(listaPontos));
    novo->x = x;
    novo->y = y;
    novo->prox = NULL;
    if(lista==NULL) 
    {
    lista = novo;
    return lista;
    }
    else
    {
        listaPontos* aux = lista;
        if (numElementosLista(lista)==1)
        {
            if (ComparaPontos(novo,aux)) aux->prox = novo;
            else
            {
                novo->prox = aux;
                lista = novo;
                return lista;
            }
        }
        else {
            if (!ComparaPontos(novo,aux)) 
            {
                novo->prox = aux;
                lista = novo;
                return lista;
            }
            else
            {
                listaPontos* aux2 = lista->prox;
                while (aux2!=NULL)
                {
                    if ((ComparaPontos(novo,aux))&&(!ComparaPontos(novo,aux2)))
                    {
                        aux->prox = novo;
                        novo->prox = aux2;
                        return lista;
                    }
                    aux = aux2;
                    aux2 = aux->prox;
                }
                aux->prox = novo;
                
            }
            
        }
 	return lista;
    }

}

int ComparaPontos(listaPontos* p1, listaPontos* p2)
{
    if (p1->x<p2->x) return 0;
    if (p1->x>p2->x) return 1;
    else
    {
        if (p1->y<p2->y) return 0;
        else return 1;
    }
}

void LiberaLista(listaPontos* lista)
{
    listaPontos* aux = lista;
    listaPontos* aux2;
    while (aux!=NULL)
    {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
}

void ImprimeListaArquivo(FILE* arquivo, listaPontos *lista)
{
    listaPontos* aux = lista;
    if (lista==NULL) return;
    while (aux->prox!=NULL)
    {
        fprintf(arquivo,"%.1lf %.1lf, ", aux->x, aux->y);
        aux = aux->prox;
    }
    fprintf(arquivo,"%.1lf %.1lf\n", aux->x, aux->y);
}

int numElementosLista(listaPontos* lista)
{
    listaPontos* aux = lista;
    int numElem = 0;
    while (aux!=NULL)
    {
        numElem++;
        aux = aux->prox;
    }
    return numElem;
}
