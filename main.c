/* 
 * File:   main.c
 * Author: marlon
 *
 * Created on 13 de Março de 2013, 20:56
 */


#include "quadtree.h"




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

    
    if ((arqLeitura = fopen(argv[1], "r") )== NULL )
        //certifica de que o arquivo de leitura foi aberto com sucesso
    {
        printf("Erro ao abrir arquvio de entrada. Certifique-se de que o primeiro "
                "argumento de execucao seja o arquivo txt com os dados a serem mapeados "
                "e o segundo argumento seja o arquivo txt de saida.");
        exit(1);
    }

        if ((arqEscrita = fopen(argv[2], "w") )== NULL )
        //certifica de que o arquivo de leitura foi aberto com sucesso
    {
        printf("Erro ao abrir arquvio de saida. Certifique-se de que o primeiro "
                "argumento de execucao seja o arquivo txt com os dados a serem mapeados "
                "e o segundo argumento seja o arquivo txt de saida.");
        exit(1);
    }
    
    
    
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
        fscanf(arqLeitura, "%d", &numConsultas);
        for (cnt3=0;cnt3<numConsultas; cnt3++)
        {
            fscanf(arqLeitura, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2); 
            resposta = NULL;
            resposta = ConsultaArvore(teste,x1,y1,x2,y2);
            ImprimeListaArquivo(arqEscrita, resposta);
            LiberaLista(resposta);
        }
 
        LiberaArvore(teste);
    }
    
    
    
    fclose(arqLeitura);
    fclose(arqEscrita);


    
    
    return 0;
    
    
    
}
