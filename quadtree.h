/* 
 * File:   quadtree.h
 * Author: marlon
 *
 * Created on 14 de Março de 2013, 23:14
 */

#ifndef QUADTREE_H
#define	QUADTREE_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* QUADTREE_H */

#include <stdio.h>
#include <stdlib.h>


//Estruturas utilizadas para a implementação da árvore

typedef struct listaPontos_t
{
    double x;
    double y;
    struct listaPontos_t* prox;
} listaPontos;


typedef struct nodeArvore_t
//Cada node da quadtree tem um número máximo de pontos, determinado pela variável
//numPontos, uma localizacao no espaço, determinada por xMin, xMax, ymin, yMax, xMed, yMed  
//e pode ser subdivido em quatro quadrantes, indicados pelos ponteiros 
//*q1, *q2, *q3 e *q4
{
    struct nodeArvore_t *q1;
    struct nodeArvore_t *q2;
    struct nodeArvore_t *q3;
    struct nodeArvore_t *q4;
    unsigned int numPontos;
    unsigned int numMaxPontos;
    listaPontos* lista; //lista encadeada que contem os pontos do quadrante
    double xMin, xMax, yMin, yMax, xMed, yMed; //limites do quadrante no espaço
    int estaFragmentado; //se o node é uma folha da árvore
} nodeArvore;

typedef struct quadTree_t
//*raiz aponta para o primeiro elemento da quadTree, e NULL se ela estiver vazia
{
    nodeArvore *raiz;
    unsigned int tamanho; //número de pontos
    unsigned int numQuad;
    unsigned int numMaxPontosQuad;
    double xMax, yMax;
} quadTree;

//Métodos principais

listaPontos* InserePontoLista(listaPontos* lista, double x, double y);
//Insere ponto na lista de forma ordenada

void LiberaLista(listaPontos* lista);

nodeArvore* CriaNode (unsigned int numMaxPontosQuad, double minX, double maxX, double minY, double maxY);
//Aloca memória para a criação de um nódulo (quadrante) da árvore

void LiberaNode(nodeArvore* node);
//Libera memória alocada na criação de um nódulo da árvore

quadTree* CriaArvore(unsigned int numMaxPontosQuad, double limiteX, double limiteY);
//Cria uma árvore vazia dado o número máximo de pontos por quadrante e os limites do plano xy

void LiberaArvore(quadTree* arvore);
//Libera a memória alocada pela árvore e todas suas estruturas


void InserePonto (quadTree *arvore, double x, double y);
//Insere um ponto na árvore em seu devido quadrante 


void DivideQuad(quadTree* arvore, nodeArvore *node);
//Divide um quadrante cujo limite de pontos tenha sido atingido e realoca os pontos para os nodes filhos

listaPontos* ConsultaArvore(quadTree *arvore, double x1, double y1, double x2, double y2);
//Consulta a quadtree com um retângulo e retorna uma lista com os pontos que estão contidos no retângulo

void ImprimeListaArquivo(FILE* arquivo, listaPontos *lista);
//Imprime os pontos contidos em uma lista em um arquivo

unsigned int numQuad(quadTree* arvore); 
//Dada uma árvore, retorna o número de quadrantes

int numElementosLista(listaPontos* lista);
//Dada uma lista, retorna o número de elementos nela presente

//Métodos auxiliares

int ComparaPontos(listaPontos* p1, listaPontos* p2);
//Compara dois pontos, retorna 0 se o primeiro ponto for o menor, e 1 se o p2 for o menor. 
//Função auxiliar da função InserePontoLista

void LiberaArvoreAux(nodeArvore* q1, nodeArvore* q2, nodeArvore* q3, nodeArvore* q4);

void InserePontoAux(quadTree *arvore, double x, double y, nodeArvore* node);

listaPontos* ConsultaArvoreAux(nodeArvore *node, listaPontos* resposta, double x1, double y1, double x2, double y2);

int FazIntersecao(double intervalo1Inicio, double intervalo1Fim, double intervalo2Inicio, double intervalo2Fim);
//Função auxiliar para a função de consulta. Retorna verdadeiro se a a interseção entre dois conjuntos for diferente de zero