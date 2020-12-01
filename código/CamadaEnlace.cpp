#include <string>
using namespace std;

#include <stdexcept>
#include <iostream>
#include <bits/stdc++.h>
#include <bitset>
#include <stdlib.h>
#include <array>
#include <cmath>

#include "CamadaFisica.h"
#include "CamadaEnlace.h"

// CODIFICAÇÃO RELATIVA AO TRABALHO 2
// (implementação de camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace
// (repositório privado na entrega do trabalho)

//---------------------------------------------------------

// CODIFICAÇÃO RELATIVA AO TRABALHO 3
// (implementação de detecção de erros na camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Deteccao_Correcao_de_Erros
// (repositório privado na entrega do trabalho)


// TRANSMISSÃO
//-----------------------------------------------------

void CamadaEnlaceDadosTransmissora(int quadro[])
{
  // se recebe o fluxo bruto da string transformada em um vetor de 0 e 1
  cout << "\033[1;34mCamada de Enlace de dados Transmissora\033[0m\n";

  int i;
  int size = find_size(quadro);

  int *quadro_novo;

  // coloca o enquadramento
  quadro_novo = CamadadeEnlaceTransmissoraEnquadramento(quadro);

  int *quadro_final;

  quadro_final = CamadaEnlaceDadosTransmissoraControledeErro(quadro_novo);


  int x;

  

  int size2 = find_size(quadro_final);



  // manda para a camada física transmissora mandar a mensagem com enquadramento
  CamadaFisicaTransmissora(quadro_final);
}

// CONTROLE DE ERROS (Transmissão)
//-----------------------------------------------------

int *CamadaEnlaceDadosTransmissoraControledeErro(int quadro[]){

  int tipo_de_erro = TIPO_DE_ERRO;
  int *quadroControle;

  int size;

  switch (tipo_de_erro){
    case 0:

      cout << "\033[1;36mControle de erro: Paridade Par  \033[0m\n";


      size = find_size(quadro);
      quadroControle = new (nothrow) int[size+1];

      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroBitParidePar(quadro);

      break;

    case 1:

      cout << "\033[1;36mControle de erro: Paridade Impar  \033[0m\n";

      size = find_size(quadro);
      quadroControle = new (nothrow) int[size+1];

      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroBitParideImpar(quadro);

      break;

    case 2:


      cout << "\033[1;36mControle de erro: Erro CRC  \033[0m\n";

      size = find_size(quadro);
      quadroControle = new (nothrow) int[size+1];

      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
      break;


    case 3:

      cout << "\033[1;36mControle de erro: Codigo de Hamming  \033[0m\n";
      
      size = find_size(quadro);
      quadroControle = new (nothrow) int[size+1];

      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCodigodeHamming(quadro);
      break;
      

  }

  printf("\n");

  int sizenovo = find_size(quadroControle);

  int i; 
  for (i = 0; i < sizenovo; i++)
  {
    printf("%d", quadroControle[i]);
  }
  printf("\n");

  return (quadroControle);

}

int *CamadaEnlaceDadosTransmissoraControleDeErroBitParideImpar(int quadro[]){

  int size = find_size(quadro);

  int *fluxoCodificado;

  fluxoCodificado = new (nothrow) int[size+4];

  int x;

  int acumulador = 0;

  int resultado = 0;

  for (x = 0; x < size; x++){

    fluxoCodificado[x] = quadro[x];

    if(quadro[x] == 1){

      acumulador++;

    }

  }

  resultado = (acumulador % 2);

  if(resultado == 0){
    // par

    fluxoCodificado[size+3] = 1;

  }
  else{

    fluxoCodificado[size+3] = 0;

  }

  fluxoCodificado[size] = 0;
  fluxoCodificado[size+1] = 0;
  fluxoCodificado[size+2] = 0;

  fluxoCodificado[size+4] = 2;

  /*

  printf("\nPARIDADE IMPAR\n");

  for (x = 0; x < (size+1); x++){

    printf("%d", fluxoCodificado[x]);

  }

  printf("\n");

  */

  return (fluxoCodificado);

}

int *CamadaEnlaceDadosTransmissoraControleDeErroBitParidePar(int quadro[]){

  int size = find_size(quadro);

  int *fluxoCodificado;

  fluxoCodificado = new (nothrow) int[size+4];

  int x;

  int acumulador = 0;

  int resultado = 0;

  for (x = 0; x < size; x++){

    fluxoCodificado[x] = quadro[x];

    if(quadro[x] == 1){

      acumulador++;

    }

  }

  resultado = (acumulador % 2);

  if(resultado == 0){
    // par

    fluxoCodificado[size+3] = 0;

  }
  else{

    fluxoCodificado[size+3] = 1;

  }

  fluxoCodificado[size] = 0;
  fluxoCodificado[size+1] = 0;
  fluxoCodificado[size+2] = 0;

  fluxoCodificado[size+4] = 2;

  //printf("\nPARIDADE PAR\n");

  //for (x = 0; x < (size+1); x++){

    //printf("%d", fluxoCodificado[x]);

  //}

  //printf("\n");



  return (fluxoCodificado);

}


// 0000001001000001

int *CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){

  // código gerador
  // G(x) = 1101

  int size = find_size(quadro);

  size = size + 4;

  int *fluxoCodificado;

  int aux[4];

  int gx[4] = {1, 1, 0, 1};

  fluxoCodificado = new (nothrow) int[size];

  int i, j = 0;
  int auxi = quadro[0];

  int *quadro_final;

  quadro_final = new (nothrow) int[size];

  for (i=0; i<size-4; i++){
    quadro_final[i] = quadro[i]; 
  
  }
  
  quadro_final[size-1] = 0;
  quadro_final[size-2] = 0;
  quadro_final[size-3] = 0;
  quadro_final[size-4] = 0;

  /*

  for (i=0; i<size; i++){
    
    printf("%d", quadro_final[i]); 
  
  }

  */

  for(i = 0; i < 4; i++){

    if(auxi == 0){

      aux[i] = (quadro_final[i] ^ 0);

    }else{

      aux[i] = (quadro_final[i] ^ gx[i]);

    }

  }

  for(i = 4; i < size; i++){

      for(j = 0; j < 3; j++){

        aux[j] = aux[j+1];

      }

      aux[3] = quadro_final[i];

   

    /*
    for(j = 0; j < 4; j++){
      printf("%d", aux[j]);
    }
    */

    auxi = aux[0];
    for(j = 0; j < 4; j++){

      if(auxi == 0){

        aux[j] = (aux[j] ^ 0);

      } else {

        aux[j] = (aux[j] ^ gx[j]);

      }
    }

  }

  /*
  printf("resposta\n");
  for(i = 0; i < 4; i++){
    printf("%d", aux[i]);
  }
  printf("\n");
  */

  int remainder = 0;
  j = 4;

  for(i = (size - 1); i >= 0; i--){

    if(j > 0){

      auxi = quadro_final[i] + aux[j-1] + remainder;
      j--;

    } else {

      auxi = quadro_final[i] + remainder;

    }

    if(auxi == 3){

      fluxoCodificado[i] = 1;
      remainder = 1;

    } else if(auxi == 2) {

      fluxoCodificado[i] = 0;
      remainder = 1;

    } else {

      fluxoCodificado[i] = auxi;
      remainder = 0;

    }

  }

  fluxoCodificado[size] = 2;

  return fluxoCodificado;

}

int *CamadaEnlaceDadosTransmissoraControleDeErroCodigodeHamming(int quadro[]){


  int size = find_size(quadro);

  int *fluxoCodificado;

  int x, pot; 

  pot = 2; 

  int conta_espaco_novo = 0; 

  while(pot < size){

    pot *= 2;   
    conta_espaco_novo++; 

  }

  fluxoCodificado = new (nothrow) int[size+conta_espaco_novo];

  return 0;

}



//-----------------------------------------------------

int *CamadadeEnlaceTransmissoraEnquadramento(int quadro[])
{

  // se escolhe o tipo de enquadramento
  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroEnquadrado;
  int i, size;

  // se enquadra o fluxo de bits passado
  switch (tipoDeEnquadramento)
  {
  case 0:

    cout << "\033[1;36mContagem de Caracteres:\n \033[0m\n";

    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);

    break;

  case 1:

    cout << "\033[1;36mInsercao de Bytes:\n \033[0m\n";

    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);

    break;

  case 2:

    cout << "\033[1;36mInsercao de Bits:\n \033[0m\n";

    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(quadro);

    break;
  }

  size = find_size(quadroEnquadrado);
  for (i = 0; i < size; i++)
  {
    printf("%d", quadroEnquadrado[i]);
  }
  printf("\n\n");

  // retornamos o fluxo de bits enquadrado
  return quadroEnquadrado;
}

// Enquadramentos
//-----------------------------------------------------

int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(int quadro[])
{

  // flag 011111110

  int size = find_size(quadro);

  int tamanho_fluxo;

  int flag[8] = {0, 1, 1, 1, 1, 1, 1, 0};

  int divisao = ((size / 40)); // quantidade de grupos inteiros que se forma com o numero de bits passado
  int resto = ((size % 40) / 8); // qntd de bytes que tem q entrar

  int quantidade_total_quadros;

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 40);
  }
  else
  {
    quantidade_total_quadros = (size / 40) + 1; // o mais 1 indica que não teremos um quadro com o tamanho inteiro como os outros
  }

  int *fluxoCodificado;
  int tam_bits_adicionais = (quantidade_total_quadros * 16) + ((quantidade_total_quadros)*5) + resto;
  tamanho_fluxo = size + tam_bits_adicionais;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado
  int *vetor_aux;
  vetor_aux = new (nothrow) int[quantidade_total_quadros];

  int i, i_aux, x, y;

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      vetor_aux[x] = resto;

    }
    else
    {

      vetor_aux[x] = 5;

    }
  }

  i = 0;
  i_aux = 0;
  int k = 0;
  int cont_um = 0;

  while (i < size)
  {

    // copia a flag
    for (x = 0; x < 8; x++)
    {
      fluxoCodificado[i_aux + x] = flag[x];
    }

    i_aux = i_aux + 8;

    // se aloca a quantidade de bits certa dependendo do que o vetor auxiliar indica
    for (y = 0; y < (vetor_aux[k] * 8); y++)
    {

      if( y == 4){
      if ((quadro[i + y] == 1) && (quadro[i + y - 1] == 1) && (quadro[i + y - 2] == 1) && (quadro[i + y - 3] == 1) && (quadro[i + y - 4] == 1))
        {
          // caso ocorra uma sequencia grande de 1's, se adiciona um zero
          fluxoCodificado[i_aux + y] = 0;
          i_aux++;
        }
      }
      fluxoCodificado[i_aux + y] = quadro[i + y];
    }

    // atualizamos de acordo as variaveis que irão iterar por cada vetor
    cont_um = 0;
    i = i + (vetor_aux[k] * 8);
    i_aux = i_aux + (vetor_aux[k] * 8);

    // coloca a flag denovo delimitando este grupo
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i_aux + x] = flag[x];
    }

    i_aux = i_aux + 8;

    k++;
  }

  // se passa adiante o fluxo com o tamanho correto

  fluxoCodificado[i_aux] = 2;

  int *FluxoLegal;

  FluxoLegal = new (nothrow) int[i_aux];

  for(int f = 0; f < i_aux ; f++){
    FluxoLegal[f] = fluxoCodificado[f];
  }

  FluxoLegal[i_aux] = 2;

  return FluxoLegal;
}

int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[])
{

  // flag 00001111

  int size = find_size(quadro);

  int tamanho_fluxo;

  int flag[8] = {0, 0, 0, 0, 1, 1, 1, 1};

  int resto = ((size % 40) / 8); // qntd de bytes que tem q entrar

  // se aloca o novo tamanho do bloco de mensagem dependendo da
  // quantidade de grupos que se aloca em um tamanho certo entre as flags

  if (size < 40)
  {

    tamanho_fluxo = size + 16;
  }
  else if (resto == 0)
  {

    tamanho_fluxo = size + (size / 40) * 16;
  }
  else
  {
    tamanho_fluxo = size + (((size / 40) * 16) + 16);
  }

  int quantidade_total_quadros;

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 40);
  }
  else
  {
    quantidade_total_quadros = (size / 40) + 1;
  }

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado
  int *vetor_aux;
  vetor_aux = new (nothrow) int[quantidade_total_quadros];

  int i, i_aux, x, y;

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      vetor_aux[x] = resto;
    }
    else
    {

      vetor_aux[x] = 5;
    }
  }

  i = 0;
  i_aux = 0;
  int k = 0;

  while (i < tamanho_fluxo)
  {

    // se coloca a flag no começo do grupo de bits
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i + x] = flag[x];
    }

    i = i + 8;

    // se coloca a quantidade correta de bits dentro do fluxo enquadrado
    // de acordo com o vetor auxiliar
    for (y = 0; y < (vetor_aux[k] * 8); y++)
    {

      fluxoCodificado[i + y] = quadro[i_aux + y];

    }

    // atualizamos de acordo as variaveis que irão iterar por cada vetor
    i = i + (vetor_aux[k] * 8);
    i_aux = i_aux + (vetor_aux[k] * 8);

    // se bota a flag novamente delimitando tamanho
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i + x] = flag[x];
    }

    i = i + 8;

    k++;
  }

  // se determina o final e passa adiante o fluxo enquadrado

  fluxoCodificado[tamanho_fluxo] = 2;

  return fluxoCodificado;
}

int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[])
{

  int i, j, x = 0;
  int cont = 0;
  int i_aux = 0;
  int tamanho_fluxo;
  int size = find_size(quadro);
  int tam_quadro = 4;

  int quatro_binario[8] = {0, 0, 0, 0, 0, 1, 0, 0};
  int tres_binario[8] = {0, 0, 0, 0, 0, 0, 1, 1};
  int dois_binario[8] = {0, 0, 0, 0, 0, 0, 1, 0};

  int num_quadros = (size / ((tam_quadro - 1) * 8));
  int resto = ((size % ((tam_quadro - 1) * 8)) / 8);

  if (resto == 0)
  {

    tamanho_fluxo = (size + (8 * num_quadros));
  }
  else
  {

    tamanho_fluxo = ((size) + (8 * (num_quadros + 1)));
  }

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  int quantidade_total_quadros;

  // se aloca a quantidade total de quadros para se determinar quantos grupos de tamanho especifico podem ser criados
  // para que então se faça um grupo com o resto

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 24);
  }
  else
  {
    quantidade_total_quadros = (size / 24) + 1;
  }

  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado

  int *aux;
  aux = new (nothrow) int[quantidade_total_quadros];

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      aux[x] = resto;
    }
    else
    {

      aux[x] = 3;
    }
  }

  int k = 0;

  i = 0;
  x = 0;
  while (i < tamanho_fluxo)
  {

    // se coloca a "flag", nesse caso
    // o tamanho do bloco que se esta colocando em um quadro

    if (x == 0)
    {

      if (aux[k] == 3)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = quatro_binario[j];
        }
      }
      if (aux[k] == 2)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = tres_binario[j];
        }
      }

      if (aux[k] == 1)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = dois_binario[j];
        }
      }

      x = 1;
      i = i + 8;
    }

    // dependendo do tamanho, se coloca a quantidade de bits certa na mensagem

    if (x == 1)
    {

      for (cont = 0; cont < (aux[k] * 8); cont++)
      {

        fluxoCodificado[cont + i] = quadro[cont + i_aux];
      }
      // atualizamos de acordo as variaveis que irão iterar por cada vetor
      i = i + (aux[k] * 8);
      x = 0; // a variavel x acaba fazendo com que os dois ifs neste loop se alternem
      i_aux = i_aux + (aux[k] * 8);
    }

    k++;
  }

  // se delimita o final e passa o fluxo correto adiante

  fluxoCodificado[tamanho_fluxo] = 2;

  // passa a codificação a diante

  return fluxoCodificado;
}

// RECEPÇÃO
//-----------------------------------------------------


void CamadaEnlaceDadosReceptora(int quadro[])
{

  cout << "\033[1;35mCamada de Enlade de dados receptora\n\033[0m";

  int i = find_size(quadro);

  int *quadro_controle;

  quadro_controle = new (nothrow) int[i-1];

  quadro_controle = CamadaDeEnlaceReceptoraControleDeErro(quadro);

  //-------------------------------------

  //int i = find_size(quadro);

  int *quadro_novo;

  quadro_novo = new (nothrow) int[i-1];

  // tira do enquadramento
  quadro_novo = CamadaDeEnlaceReceptoraEnquadramento(quadro_controle);

  int *quadroFinal;
  int l = find_size(quadro_novo);

  quadroFinal = new (nothrow) int[l];

  for(int x = 0; x<l; x++){
    quadroFinal[x] = quadro_novo[x];
  }
  quadroFinal[l] = 2;

  // passa adiante para a camada receptora transformar os bits em strings
  CamadaDeAplicacaoReceptora(quadroFinal);
}

int *CamadaDeEnlaceReceptoraControleDeErro(int quadro[]){

  int tipo_de_erro = TIPO_DE_ERRO;
  int size; 
  int *quadro_controle;

  switch(tipo_de_erro){

    case 0:

      cout << "\033[1;36mBit de Paridade Par:\n \033[0m\n";

      quadro_controle = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
      break;

    case 1:

      cout << "\033[1;36mBit de Paridade Impar:\n \033[0m\n";

      quadro_controle = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(quadro);
      break;

    case 2:

      cout << "\033[1;36mControle de Erro CRC:\n \033[0m\n";
      quadro_controle = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
      break;

    case 3:

      //quadro_controle = CamadaEnlaceDadosReceptoraControleDeErroCodigodeHamming(quadro);
      break;

  }

  int i; 

  printf("\n");

  size = find_size(quadro_controle);

  for (i = 0; i < size; i++)
  {
    printf("%d", quadro_controle[i]);
  }
  printf("\n");

  return (quadro_controle);

}

// CONTROLE DE ERROS (Recepção)
//-----------------------------------------------------

int *CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(int quadro[]){


  int size = find_size(quadro);

  int *fluxoCodificado;

  fluxoCodificado = new (nothrow) int[size-4];

  int x;

  int acumulador = 0;

  int resultado = 0;

  for (x = 0; x < size; x++){

    if(quadro[x] == 1){
      acumulador++;
    }

  }

  resultado = (acumulador % 2);

  //printf("\nresultado:%d\n", resultado);

  if(resultado == 1){

    //printf("\nDEBOA\n");

    // certo

    for (x = 0; x < size-4; x++){

      fluxoCodificado[x] = quadro[x];

    }

  }
  else{

    cout << "\033[1;31m \nAtenção! Um erro foi encontrado ao se checar o Bit de Paridade Impar!\nO programa será encerrado agora.\n \033[0m\n";

    exit(0);

  }


  //printf("\nACHANDO A PARIDADE IMPAR\n");

  //for (x = 0; x < (size-4); x++){

    //printf("%d", fluxoCodificado[x]);

  //}

  //printf("\n");

  fluxoCodificado[size-4] = 2;

  return (fluxoCodificado);




}


int *CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(int quadro[]){

  int size = find_size(quadro);

  int *fluxoCodificado;

  fluxoCodificado = new (nothrow) int[size-4];

  int x;

  int acumulador = 0;

  int resultado = 0;

  for (x = 0; x < size; x++){

    if(quadro[x] == 1){
      acumulador++;
    }

  }

  resultado = (acumulador % 2);

  //printf("\nresultado:%d\n", resultado);

  if(resultado == 0){

    //printf("\nDEBOA\n");

    // certo

    for (x = 0; x < size-4; x++){

      fluxoCodificado[x] = quadro[x];

    }

  }
  else{

    cout << "\033[1;31m \nAtenção! Um erro foi encontrado ao se checar o Bit de Paridade Par!\nO programa será encerrado agora.\n \033[0m\n";

    exit(0);

  }


  //printf("\nACHANDO A PARIDADE PAR\n");

  //for (x = 0; x < (size-4); x++){

    //printf("%d", fluxoCodificado[x]);

  //}

  //printf("\n");

  fluxoCodificado[size-4] = 2;

  return (fluxoCodificado);


}


int *CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]){

  int size = find_size(quadro);

  int *fluxoCodificado;

  int aux[4];
  int gx[4] = {1, 1, 0, 1};

  fluxoCodificado = new (nothrow) int[size];

  int i, j = 0;
  int auxi = quadro[0];

  for(i = 0; i < 4; i++){

    if(auxi == 0){

      aux[i] = (quadro[i] ^ 0);

    }else{

      aux[i] = (quadro[i] ^ gx[i]);

    }
  }

  for(i = 4; i < size; i++){

    //if(i != size - 1){

      for(j = 0; j < 3; j++){

        aux[j] = aux[j+1];

      }
      aux[3] = quadro[i];

    //}

    for(j = 0; j < 4; j++){
      //printf("%d", aux[j]);
    }

    auxi = aux[0];
    for(j = 0; j < 4; j++){

      if(auxi == 0){

        aux[j] = (aux[j] ^ 0);

      } else {

        aux[j] = (aux[j] ^ gx[j]);

      }
    }

  }

  //printf("resposta\n");
  //for(i = 0; i < 4; i++){

    //printf("%d", aux[i]);

  //}
  //printf("\n");

  if((aux[0] == 1) || (aux[1] == 1) || (aux[2] == 1) || (aux[3] == 1) ){

    cout << "\033[1;31m \nResto diferente de zero: Um erro foi detectado!\n \033[0m\n";

    exit(0);  
  }
  else{
    
    cout << "\033[1;31m \nResto igual à zero: Não foi detectado nenhum erro.\n \033[0m\n";
    
  }

  
  int cont_aux;
  j = 4;


  for(i = 0; i < size; i++){
    fluxoCodificado[i] = quadro[i];
  }

  /*
  for(i = size-1; i >= 0; i--){

    if(j > 0){

      auxi = quadro[i] - aux[j-1]; //- remainder;
      //j--;

    } else {

      auxi = quadro[i];// - remainder;

    }

    if(auxi < 0){

      cont_aux = i;
      while(auxi < 0) {

        auxi = quadro[cont_aux-1] - 1;
        cont_aux--;

      }

      quadro[cont_aux] = quadro[cont_aux] - 1;

    }
    if(j > 0){

      fluxoCodificado[i] = 1 - aux[j - 1];

    } else {

      fluxoCodificado[i] = quadro[i];

    }
    j--;
  }
  */

  fluxoCodificado[size] = 2;

  //printf("fluxoCodificado:\n");
  //for(i = 0; i < size; i++){
  //printf("%d", fluxoCodificado[i]);
  //}
  //printf("\n");

  return fluxoCodificado;

}

/*
int *CamadaEnlaceDadosReceptoraControleDeErroCodigodeHamming(int quadro[]){

  return 0;

}
*/

//-----------------------------------------------------

int *CamadaDeEnlaceReceptoraEnquadramento(int quadro[])
{

  // aqui se escolhe o tipo de enquadramento que se deseja retirar
  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroDesenquadrado;

  int i = find_size(quadro);

  quadroDesenquadrado = new (nothrow) int[i];
  int *quadroFinal;

  // desenquadramos de acordo com a abordagem escolhida
  switch (tipoDeEnquadramento)
  {
  case 0:

    cout << "\033[1;36mDesenquadramento da Contagem de Caracteres:\n \033[0m\n";

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);

    break;

  case 1:

    cout << "\033[1;36mDesenquadramento da Inserçao de Bytes:\n \033[0m\n";

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
    //
    break;

  case 2:

    cout << "\033[1;36mDesenquadramento da Insercao de Bits:\n \033[0m\n";

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(quadro);
    //

    break;
  }

  int size = find_size(quadroDesenquadrado);
  for (i = 0; i < size; i++)
  {
    printf("%d", quadroDesenquadrado[i]);

  }
  printf("\n\n");

  // passa o quadro pronto adiante
  return quadroDesenquadrado;
}

// Desenquadramentos
//-----------------------------------------------------

int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(int quadro[])
{
  int size = find_size(quadro);

  // flag 01111110

  int i = 0;
  int x = 0;
  int i_aux = 0;
  int y = 0;
  int cont_um = 0;

  int aux[8];

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {

    // se analisa de 8 em 8 bits atrás da flag
    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[x + i];
    }

    if ((aux[0] == 0) && (aux[1] == 1) && (aux[2] == 1) && (aux[3] == 1) && (aux[4] == 1) && (aux[5] == 1) && (aux[6] == 1) && (aux[7] == 0))
    {

      // é flag

    }
    else
    {

      // se busca sequencias de 1, para que o zero da sequencia seja descartado
      if (quadro[i] == 1 && quadro[i - 1] == 1)
      {
        cont_um++;
      }
      else
      {
        cont_um = 0;
      }

      if (cont_um == 4 && quadro[i] == 0)
      {
        i++;
      }

      FluxoFinal[i_aux] = quadro[i];

      // copia o que é mensagem para o fluxo,
      // jogando flags fora
      for (x = 0; x < 8; x++)
      {

        FluxoFinal[x + i_aux] = aux[x];
      }

      // atualizamos de acordo as variaveis que irão iterar por cada vetor
      i_aux = i_aux + 8;
    }

    i = i + 8;
  }

  FluxoFinal[i_aux] = 2;

  // passa o resultado adiante
  return FluxoFinal;
}

int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int quadro[])
{

  int size = find_size(quadro);

  int i = 0;
  int x = 0;
  int i_aux = 0;

  int aux[8];

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {

    // se faz a análise de 8 em 8 bits
    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[x + i];
    }

    // buscamos a flag
    if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 1) && (aux[5] == 1) && (aux[6] == 1) && (aux[7] == 1))
    {

      // é flag
    }
    else
    {
      // se não é a flag, podemos copiar os bits para o resultado final
      for (x = 0; x < 8; x++)
      {

        FluxoFinal[x + i_aux] = aux[x];
      }

      // atualizamos de acordo as variaveis que irão iterar por cada vetor

      i_aux = i_aux + 8;
    }

    i = i + 8;
  }

  // delimitamos um final e passamos o fluxo adiante

  FluxoFinal[i_aux] = 2;

  return FluxoFinal;
}

int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int quadro[])
{

  int size = find_size(quadro);

  int i = 0;
  int x = 0;
  int i_aux = 0;

  int aux[8];

  int k = 0;

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {

    // pegamos os primeiros 8 bits

    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[i + x];
    }

    // atualizamos em qual posição estamos no quadro

    i = i + 8;

    // definimos qual o tamanho do bloco que vai para o fluxo final

    if ((k == 0))
    {
      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 1) && (aux[6] == 0) && (aux[7] == 0))
      {

        // é o cabeçalho de um quadro completo

        k = 3;
      }

      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 1))
      {

        // restam 2 bytes para passarmos

        k = 2;
      }

      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 0))
      {

        // resta 1 byte para passar

        k = 1;
      }
    }

    // copia a "k" quantidade de bytes pro fluxo

    for (x = 0; x < (8 * k); x++)
    {

      FluxoFinal[x + i_aux] = quadro[x + i];
    }

    // atualiza a posição que estamos no quadro e no fluxo final

    i_aux = i_aux + (8 * k);
    i = i + (8 * k);

    k = 0;

    // dps o fluxo final tem um tamanho igual a i_aux

    // para cada (k*8) posições q o fluxo final anda, o quadro anda (k*8 + 8),jogando o header fora
  }

  // delimitamos o final e passamos o fluxo adiante

  FluxoFinal[i_aux] = 2;

  return FluxoFinal;
}

//-----------------------------------------------------
