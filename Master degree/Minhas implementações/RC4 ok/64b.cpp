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
    unsigned char chave[257]={ 0X27 , 0X7F , 0X43 , 0X00 , 0XA0 , 0X96 , 0X15 , 0X79 , 0XF8 , 0XC5 , 0X29 , 0X93 , 0X3F , 0XAE , 0X92 , 0X47 , 0XCC , 0X8C , 0X76 , 0X24 , 0XF1 , 0XB0 , 0X08 , 0X51 , 0XCC , 0X2C , 0XC6 , 0XB3 , 0X9E , 0XD6 , 0X2B , 0XF2 , 0X24 , 0XBB , 0X4E , 0XFE , 0X6F , 0XFF , 0X7E , 0X3C , 0XA8 , 0X69 , 0X0C , 0XE8 , 0X43 , 0X8B , 0XB2 , 0X1B , 0X20 , 0XE6 , 0XE5 , 0X8D , 0X04 , 0X72 , 0XF7 , 0XA2 , 0XE5 , 0XB5 , 0X32 , 0X1C , 0X92 , 0X40 , 0XAE , 0X7C};
    unsigned char S[257];
    unsigned char out[257]={'a','\0'};
    Inicializa_Estado(S,chave);
    Encripta_Decripta(S,out);
return 0;
}
