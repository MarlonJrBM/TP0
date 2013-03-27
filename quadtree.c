/*Funções gerais da quadTree*/



#include "quadtree.h"



quadTree* CriaArvore(unsigned int numMaxPontos, double limiteX, double limiteY)
{
    quadTree* arvore;
    if ((arvore = malloc(sizeof(quadTree)))==NULL)
    {
        printf("Erro ao alocar memoria para arvore! Abortando programa...");
        exit(1);
    }
    arvore->numMaxPontosQuad = numMaxPontos;
    arvore->xMax = limiteX;
    arvore->yMax = limiteY;
    arvore->raiz = CriaNode(numMaxPontos,0, limiteX,0, limiteY);;
    arvore->tamanho = 0;
    arvore->numQuad = 1;

    
    return (arvore);
}


unsigned int numQuad(quadTree* arvore)
{
    return arvore->numQuad;
}

void LiberaArvore(quadTree* arvore)
{
    if (arvore->raiz->estaFragmentado)
    {
        LiberaArvoreAux(arvore->raiz->q1, arvore->raiz->q2, arvore->raiz->q3, arvore->raiz->q4);
    }
    if (arvore->numQuad<=1) LiberaNode(arvore->raiz);
    else free(arvore->raiz);
    free(arvore);

}

void LiberaArvoreAux(nodeArvore* q1, nodeArvore* q2, nodeArvore* q3, nodeArvore* q4)
{
    if (!q1->estaFragmentado) LiberaNode(q1);
    else LiberaArvoreAux(q1->q1, q1->q2, q1->q3, q1->q4);
    if (!q2->estaFragmentado) LiberaNode(q2);
    else LiberaArvoreAux(q2->q1, q2->q2, q2->q3, q2->q4);
    if (!q3->estaFragmentado) LiberaNode(q3);
    else LiberaArvoreAux(q3->q1, q3->q2, q3->q3, q3->q4);
    if (!q4->estaFragmentado) LiberaNode(q4);
    else LiberaArvoreAux(q4->q1, q4->q2, q4->q3, q4->q4);    
}

void InserePonto (quadTree *arvore, double x, double y)
{
    if ((x>arvore->xMax) || (x<0)) return;
    if ((y>arvore->yMax) || (y<0)) return;
    InserePontoAux(arvore,x,y,arvore->raiz);
    arvore->tamanho++;
}

listaPontos* ConsultaArvore(quadTree *arvore, double x1, double y1, double x2, double y2)
{
//IMPORTANTE: A consulta só funciona se os pontos passados forem os vértices sudoeste e nordeste do retângulo!
    listaPontos* lista = NULL;
    double x1R = x1, y1R = y1, x2R = x2, y2R = y2;
    if (x1>x2)
    {
        x1R = x2;
        x2R = x1;
        y1R = y2;
        y2R = y1;
    }
 
    lista = ConsultaArvoreAux(arvore->raiz, lista, x1R, y1R, x2R, y2R );
    return lista;
    
}

listaPontos* ConsultaArvoreAux(nodeArvore *node, listaPontos* resposta, double x1, double y1, double x2, double y2)
{
    listaPontos* aux = node->lista;
    
    if (!node->estaFragmentado)
    {
        
        while (aux!=NULL)
        {
            if ((aux->x>=x1)&&
                (aux->x<=x2)&&
                (aux->y>=y1)&&
                (aux->y<=y2))
                resposta = InserePontoLista(resposta,aux->x,aux->y);
            aux = aux->prox;
        }
    }
    else
    {
        if ((FazIntersecao(x1,x2,node->q1->xMin, node->q1->xMax))&&
            (FazIntersecao(y1,y2,node->q1->yMin, node->q1->yMax)))
            resposta = ConsultaArvoreAux(node->q1, resposta, x1, y1, x2, y2);
        if ((FazIntersecao(x1,x2,node->q2->xMin, node->q2->xMax))&&
            (FazIntersecao(y1,y2,node->q2->yMin, node->q2->yMax)))
            resposta = ConsultaArvoreAux(node->q2, resposta, x1, y1, x2, y2);
        if ((FazIntersecao(x1,x2,node->q3->xMin, node->q3->xMax))&&
            (FazIntersecao(y1,y2,node->q3->yMin, node->q3->yMax)))
            resposta = ConsultaArvoreAux(node->q3, resposta, x1, y1, x2, y2);
        if ((FazIntersecao(x1,x2,node->q4->xMin, node->q4->xMax))&&
            (FazIntersecao(y1,y2,node->q4->yMin, node->q4->yMax)))
            resposta = ConsultaArvoreAux(node->q4, resposta, x1, y1, x2, y2);

    }
    
    return resposta;
}

int FazIntersecao(double intervalo1Inicio, double intervalo1Fim, double intervalo2Inicio, double intervalo2Fim)
{
    if (((intervalo1Inicio>=intervalo2Inicio)&&
        (intervalo1Inicio<=intervalo2Fim))||
         ((intervalo2Inicio>=intervalo1Inicio)&&
          (intervalo2Inicio<=intervalo1Fim)))
        return 1;
    else return 0;
            
}