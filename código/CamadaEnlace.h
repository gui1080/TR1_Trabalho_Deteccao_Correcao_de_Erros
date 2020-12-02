#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>

//-----------------------------------------------------

// CODIFICAÇÃO RELATIVA AO TRABALHO 3
// (implementação de detecção e correção de erros)

// https://github.com/gui1080/TR1_Trabalho_Deteccao_Correcao_de_Erros
// (repositório privado na entrega do trabalho)

//-----------------------------------------------------

#define TIPO_DE_ERRO 0
// TIPO_DE_ERRO 0 = Paridade Par
// TIPO_DE_ERRO 1 = Paridade Impar
// TIPO_DE_ERRO 2 = Erro CRC
// TIPO_DE_ERRO 3 = Código de Hamming

#define ERRO 0
// ERRO 0 = "Modo caos"
// ERRO 1 = "Modo Conservador"

#define CHANCE_DO_ERRO 1
// Definir um número entre 0 e 100


//-----------------------------------------------------

// CODIFICAÇÃO RELATIVA AO TRABALHO 2
// (implementação de camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace
// (repositório privado na entrega do trabalho)

//-----------------------------------------------------

#define ENQUADRAMENTO 0
// Enquadramento 0 = Contagem de Caracteres
// Enquadramento 1 = Inserção de Bytes
// Enquadramento 2 = Inserção de Bits
// esse define vai atualizar não apenas o enquadramento como também o desenquadramento, simplificando os testes

// Transmissão
//-----------------------------------------------------
void CamadaEnlaceDadosTransmissora(int* quadro);
int *CamadadeEnlaceTransmissoraEnquadramento(int* quadro);

// Recepção
//-----------------------------------------------------
int *CamadaDeEnlaceReceptoraEnquadramento(int* quadro);
void CamadaEnlaceDadosReceptora(int* quadro);

// Enquadrando
//-----------------------------------------------------
int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(int *quadro);

// Desenquadrando
//-----------------------------------------------------
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(int *quadro);


//-----------------------------------------------------
// Trabalho 3 - Erros
//-----------------------------------------------------

// Transmissão
int *CamadaEnlaceDadosTransmissoraControledeErro(int *quadro);

// Transmissão: Controle de erros
int *CamadaEnlaceDadosTransmissoraControleDeErroBitParidePar(int *quadro);
int *CamadaEnlaceDadosTransmissoraControleDeErroBitParideImpar(int *quadro);
int *CamadaEnlaceDadosTransmissoraControleDeErroCRC(int *quadro);
int *CamadaEnlaceDadosTransmissoraControleDeErroCodigodeHamming(int *quadro);

// Recepção
int *CamadaDeEnlaceReceptoraControleDeErro(int *quadro);

// Recepção: Controle de erros
int *CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(int *quadro);
int *CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(int *quadro);
int *CamadaEnlaceDadosReceptoraControleDeErroCRC(int *quadro);
//int *CamadaEnlaceDadosReceptoraControleDeErroCodigodeHamming(int *quadro);

//-----------------------------------------------------
