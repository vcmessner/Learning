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
#define b 16   // tamanho da chave
#define c 4  // 8b/w ou b/u
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
        j=(j+1)&3;
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
    unsigned char key[b] = { 0X1F , 0X6B , 0XD7 , 0X03 , 0X88 , 0X8F , 0X5E , 0X45 , 0XF4 , 0X2E , 0X0D , 0X35 , 0XE7 , 0XDA , 0X44 , 0X9E};
    pt1[0]=ct[0];pt1[1]=ct[1];
    Inicializa_Estado(key);
    Encripta(pt1,ct);
    //Decripta(pt2,ct);
return 0;
}
