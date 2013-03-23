/*
 Funções relativas aos nódulos (quadrantes)da árvore e inserção de pontos
 */


#include "quadtree.h"

nodeArvore* CriaNode (unsigned int numMaxPontosQuad, double minX, double maxX, double minY, double maxY)
{
    nodeArvore* node;
    if ((node = malloc(sizeof(nodeArvore)))==NULL)
    {
        printf("Erro ao alocar memoria para nodulo! Abortando programa...");
        exit(1);
    }
    node->q1 = NULL;
    node->q2 = NULL;
    node->q3 = NULL;
    node->q4 = NULL;
    node->numPontos = 0;
    node->numMaxPontos = numMaxPontosQuad;
    node->xMin = minX;
    node->xMax = maxX;
    node->yMin = minY;
    node->yMax = maxY;
    node->xMed = (double)(node->xMin + node->xMax)/2;
    node->yMed = (double)(node->yMin + node->yMax)/2;
    node->lista = NULL;
    node->estaFragmentado = 0;
    

    
    return node;
}

void LiberaNode(nodeArvore *node)
{
    LiberaLista(node->lista);
    free(node);
}



void InserePontoAux(quadTree *arvore, double x, double y, nodeArvore* node)
{
    if ((node->numPontos<node->numMaxPontos)&&(!node->estaFragmentado))
    {
        node->lista = InserePontoLista(node->lista,x,y);
        node->numPontos++;
    }
    else
    {
        if (!node->estaFragmentado) DivideQuad(arvore, node);
        if ((x>=node->xMed)&&
            (x<=node->xMax)&&
            (y>=node->yMed)&&
            (y<=node->yMax) )
        {
            InserePontoAux(arvore, x, y, node->q1);
        }
        else
            if  ((x>=node->xMin) &&
                (x<node->xMed) &&
                (y>=node->yMed) &&
                (y<=node->yMax))
            {
                InserePontoAux(arvore,x,y,node->q2);
            }
            else
                if ((x>=node->xMin)&&
                    (x<node->xMed)&&
                     (y>=node->yMin)&&
                     (y<node->yMed))
                {
                    InserePontoAux(arvore,x,y,node->q3);
                }
                else
                {
                    InserePontoAux(arvore,x,y,node->q4);
                }
        
        
    }
}

void DivideQuad(quadTree* arvore, nodeArvore *node)
{
    arvore->numQuad+=3;
    node->estaFragmentado = 1;
    node->q1 = CriaNode(node->numMaxPontos, node->xMed, node->xMax, node->yMed, node->yMax );
    node->q2 = CriaNode(node->numMaxPontos, node->xMin, node->xMed,node->yMed, node->yMax );
    node->q3 = CriaNode(node->numMaxPontos, node->xMin, node->xMed,node->yMin, node->yMed );
    node->q4 = CriaNode(node->numMaxPontos, node->xMed, node->xMax,node->yMin, node->yMed );
    //Agora ele percorerrá a lista de pontos e os realocará para os quadrantes alocados acima
    listaPontos *aux = node->lista;
    while (aux!=NULL)
    {
        if ((aux->x>=node->xMed)&&
            (aux->x<=node->xMax)&&
            (aux->y>=node->yMed)&&
            (aux->y<=node->yMax) )
        {
            node->q1->lista = InserePontoLista(node->q1->lista,aux->x,aux->y);
            node->q1->numPontos++;
        }
            
        else
            
            if ((aux->x>=node->xMin) &&
                (aux->x<node->xMed) &&
                (aux->y>=node->yMed) &&
                (aux->y<=node->yMax))
            {
               node->q2->lista = InserePontoLista(node->q2->lista,aux->x,aux->y);
               node->q2->numPontos++;
            }
            
            else
                
                if ((aux->x>=node->xMin)&&
                    (aux->x<node->xMed)&&
                     (aux->y>=node->yMin)&&
                     (aux->y<node->yMed))
                {
                  node->q3->lista = InserePontoLista(node->q3->lista,aux->x,aux->y);
                  node->q3->numPontos++;  
                }
                    
                else
                {
                  node->q4->lista = InserePontoLista(node->q4->lista,aux->x,aux->y);
                  node->q4->numPontos++;  
                }
                         
        aux=aux->prox;
    }
    
    
    LiberaLista(node->lista);
    node->numPontos = 0;
}