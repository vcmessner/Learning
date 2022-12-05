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
#include <stdio.h>
using namespace std;
#define w 32     // Tamanho da palavra (bloco tem tamanho 2w)
#define r 15    // número de rounds
#define b 64   // tamanho da chave
#define c 16  // 8b/w ou b/u
#define t 32 // 2* (r+1)
#define P 0xb7e15163ul
#define Q 0x9e3779b9ul

#define ROTL(v,n) (((v)<<(n))|((v)>>(32-(n))))
#define ROTR(v,n) (((v)>>(n))|((v)<<(32-(n))))
unsigned long int S[t];

inline void Inicializa_Estado(unsigned char * K){
    unsigned long int j,k,i,u=w/8,A,B,L[c];
    L[c-1]=0;
    for(i=b-1;i!=-1;--i){
        L[i/u] = (L[i/u]<<8) + K[i];
    }
    S[0]=P;
    for(i=1;i<t;++i){
           S[i]=S[i-1]+Q;
    }
    A=B=i=j=0;u=3*t; //m = max(c, t); u=3*m
    for (k=0;k<u;++k){
        S[i]= ROTL(S[i]+A+B,3);
        A=S[i];
        i=(i+1)&31;
        L[j]= ROTL(L[j]+A+B,(A+B));
        B=L[j];
        j=(j+1)&15;
}}

inline void Encripta(unsigned long int * pt, unsigned long int * ct){
   unsigned long int i,A=pt[0]+S[0],B=pt[1]+S[1];
   for (i=1;i<=r;++i){
    A = ROTL(A^B,B)+S[2*i];
    B = ROTL(B^A,A)+S[2*i+1];
   }
   ct[0]=A;ct[1]=B;
}


inline void Decripta(unsigned long int * pt, unsigned long int * ct){
   unsigned long int i,B=ct[1],A=ct[0];
   for (i=r;i>0;--i){
    B=ROTR(B-S[2*i+1],A)^A;
    A=ROTR(A-S[2*i],B)^B;}
    pt[1]=B-S[1];pt[0]=A-S[0];
}

int main (){
    unsigned char i,j,k;
    unsigned long int pt1[2]={'a','\0'},ct[2]={0,0};
    unsigned char key[b] = { 0X27 , 0X7F , 0X43 , 0X00 , 0XA0 , 0X96 , 0X15 , 0X79 , 0XF8 , 0XC5 , 0X29 , 0X93 , 0X3F , 0XAE , 0X92 , 0X47 , 0XCC , 0X8C , 0X76 , 0X24 , 0XF1 , 0XB0 , 0X08 , 0X51 , 0XCC , 0X2C , 0XC6 , 0XB3 , 0X9E , 0XD6 , 0X2B , 0XF2 , 0X24 , 0XBB , 0X4E , 0XFE , 0X6F , 0XFF , 0X7E , 0X3C , 0XA8 , 0X69 , 0X0C , 0XE8 , 0X43 , 0X8B , 0XB2 , 0X1B , 0X20 , 0XE6 , 0XE5 , 0X8D , 0X04 , 0X72 , 0XF7 , 0XA2 , 0XE5 , 0XB5 , 0X32 , 0X1C , 0X92 , 0X40 , 0XAE , 0X7C};
    pt1[0]=ct[0];pt1[1]=ct[1];
    Inicializa_Estado(key);
    Encripta(pt1,ct);
    //Decripta(pt2,ct);
return 0;
}
