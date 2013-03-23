/* 
 * File:   main.c
 * Author: marlon
 *
 * Created on 13 de Março de 2013, 20:56
 */


#include "quadtree.h"
#include <time.h>



/*Arquivo principal do TP. Lê do arquivo com nome passado no argumento 1 e escreve 
 no arquivo com nome passado no argumento 2. */

int main(int argc, char** argv) {
    
    

    FILE *arqLeitura, *arqEscrita; //arquivos para ler a entrada e imprimir na saída
    int numArvores = 0, cnt, cnt2, cnt3, numPontos, numMaxPontosQuad, numConsultas;
    double xMax, yMax; //Variáveis utilizadas para marcar os limites do plano
    double x, y; //Variáveis utilizadas para inserir os pontos na árvore
    double x1, y1, x2, y2; //Variáveis utilizadas para criar o retângulo de consulta
    quadTree* teste; //Estrutura da quadTree
    listaPontos* resposta; //lista que conterá os pontos resultantes da busca
    clock_t inicio, fim;
    float duration;
    
    if ((arqLeitura = fopen(argv[1], "r") )== NULL )
        //certifica de que o arquivo de leitura foi aberto com sucesso
    {
        printf("Erro ao abrir arquvio de leitura. Certifique-se de que o primeiro "
                "argumento de execucao seja o arquivo txt com os dados a serem mapeados "
                "e o segundo argumento seja o arquivo txt de saida.");
        exit(1);
    }

        if ((arqEscrita = fopen(argv[2], "w") )== NULL )
        //certifica de que o arquivo de leitura foi aberto com sucesso
    {
        printf("Erro ao abrir arquvio de escrita. Certifique-se de que o primeiro "
                "argumento de execucao seja o arquivo txt com os dados a serem mapeados "
                "e o segundo argumento seja o arquivo txt de saida.");
        exit(1);
    }
    
    inicio = clock();
    
    fscanf(arqLeitura, "%d", &numArvores);
    
    for(cnt=0;cnt<numArvores;cnt++)
    {
        fscanf(arqLeitura,"%lf %lf %d %d", &xMax, &yMax, &numMaxPontosQuad, &numPontos );
        teste = CriaArvore(numMaxPontosQuad,xMax,yMax);
        for (cnt2=0;cnt2<numPontos;cnt2++)
        {
            fscanf(arqLeitura, "%lf %lf", &x, &y);
            InserePonto(teste,x,y);  
        }
       fprintf(arqEscrita,"%d\n", numQuad(teste));
       printf("\n%d\n", teste->numQuad);
       printf("\n%d\n", teste->tamanho);
        fscanf(arqLeitura, "%d", &numConsultas);
        for (cnt3=0;cnt3<numConsultas; cnt3++)
        {
            fscanf(arqLeitura, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2); 
            resposta = NULL;
            resposta = ConsultaArvore(teste,x1,y1,x2,y2);
            printf("\n%d\n", numElementosLista(resposta));
            ImprimeListaArquivo(arqEscrita, resposta);
            LiberaLista(resposta);
        }
 
        LiberaArvore(teste);
    }
    
    
    //printf("%d", numConsultas);
    //printf("\n%d, %d %d %lf, %lf %lf %lf\n", numArvores, numMaxPontosQuad, numPontos, xMax, yMax, x, y);
    
    fclose(arqLeitura);
    fclose(arqEscrita);
    //LeArquivo(arqLeitura);
    
   
    
    
    
    
/*
    
    quadTree* arvore = CriaArvore(4, 8, 8);
    InserePonto(arvore, 1, 7);
    InserePonto(arvore, 1, 5);
    InserePonto(arvore, 2, 5);
    InserePonto(arvore, 2, 2);
    InserePonto(arvore, 3, 7);
    InserePonto(arvore, 3, 5);
    InserePonto(arvore, 6, 6);
    InserePonto(arvore, 6, 2);
*/

    

    
    //ImprimeLista(resposta);
   



    
 
/*
    listaPontos* lista1 = NULL;
    lista1 = InserePontoLista(lista1, 4, 8);
    lista1 = InserePontoLista(lista1, 3, 8);
    lista1 = InserePontoLista(lista1, 3, 7);
    lista1 = InserePontoLista(lista1, 4, 7);
    lista1 = InserePontoLista(lista1,3.5,4.5);
    lista1 = InserePontoLista(lista1,5,8);
    lista1 = InserePontoLista(lista1,1,1);
    ImprimeLista(lista1);
    printf("%d", numElementosLista(lista1));
*/
    

    

    
    fim = clock();
    duration = (float)(fim - inicio)/CLOCKS_PER_SEC;
    
    printf("\e[31m%f\e[0ms\n", duration);
    
    
    


    
    
    





    

    
       

    
    
    
        
    
    return 0;
    
    
    
}