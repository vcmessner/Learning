/*RC4.cpp
/*--------------------------------------------------------------------
    Universidade Federal do Rio de Janeiro
    Autor: Victor Cracel Messner
*   Algoritmo de criptografia RC4
*   O código apresentado faz parte da tese de mestrado do autor pelo
*   título de mestre, apresentado ao Intituto Alberto Luiz Coimbra de
*   Pós-Graduação e Pesquisa de Engenharia (COPPE)da Universidade
*   Federal do Rio de Janeiro. Você pode modificar e distribuir este
*   código livremente através dos termos do GNU General Public como
*    publicado pelo Free Software Foundation através da versão 3 da
*    licença, ou qualquer versão subsequente por opção sua.

*   Este código é utilizado para a execução dos testes de desempenho
*   para o cenário ICN-IOT.
---------------------------------------------------------------------*/
#include <iostream>
#include<string>
#include<fstream>
//#include <chrono>
using namespace std;
//#define SWAP(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

inline void Inicializa_Estado(unsigned char S[], unsigned char chave[]){
   int i=0,j=0,j1=0;
    while (chave[i]!='\0'){
        S[i]= i;
        ++i;
    }
    while (i<256){
        chave[i]=chave[j];
        S[i] = i;
        ++i;
        ++j;
    }
   for (i=0,j=0; i < 256; ++i) {
      j = (j + S[i] + chave[i]) & 0XFF;
      swap(S[i], S[j]);
   }}

inline void Encripta_Decripta(unsigned char S[], unsigned char out[]){
   int i=0,j=0,x,t;
   unsigned char chave;
   for (x=0; out[x]!='\0'; ++x)  {
      i = (i + 1) & 0XFF;
      j = (j + S[i]) & 0XFF;
      swap(S[i], S[j]);
      out[x] = (S[(S[i] + S[j]) & 0XFF])^out[x];
    }}

int main (){
    unsigned char chave[257]={0X90 , 0X7E , 0XA3 , 0X59};
    unsigned char S[257];
    unsigned char out[257]={'a','\0'};
    Inicializa_Estado(S,chave);
    Encripta_Decripta(S,out);
return 0;
}
