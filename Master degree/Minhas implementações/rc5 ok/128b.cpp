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
#define b 128   // tamanho da chave
#define c 32  // 8b/w ou b/u
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
        j=(j+1)&31;
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
    unsigned char key[b] = { 0X48 , 0X1C , 0X87 , 0X1B , 0X57 , 0X02 , 0XD3 , 0XB4 , 0X94 , 0X91 , 0XFA , 0X75 , 0XD6 , 0X6B , 0X04 , 0XC3 , 0XAB , 0XAB , 0X8C , 0XA5 , 0X72 , 0X37 , 0XEA , 0X44 , 0X5B , 0X57 , 0X8B , 0X22 , 0X60 , 0X68 , 0X7A , 0X39 , 0X89 , 0XB2 , 0XAF , 0XC0 , 0XC1 , 0X63 , 0X47 , 0X3D , 0XB0 , 0XE2 , 0X1D , 0X06 , 0XB0 , 0X90 , 0X6E , 0X3C , 0X2E , 0X48 , 0X3B , 0XC8 , 0XAD , 0X4A , 0XA8 , 0XAD , 0XC8 , 0X41 , 0X12 , 0XC5 , 0XFB , 0X04 , 0X1D , 0X75 , 0X1A , 0X05 , 0XA8 , 0X1A , 0XBA , 0X49 , 0XB1 , 0X66 , 0X7B , 0X5D , 0X6A , 0XF9 , 0XA2 , 0X81 , 0XC8 , 0X4D , 0XFA , 0XCF , 0XF3 , 0X0A , 0X24 , 0X9F , 0X2E , 0X73 , 0X00 , 0X41 , 0XA4 , 0XDF , 0XDC , 0XBE , 0X66 , 0XE4 , 0XB8 , 0X78 , 0XDF , 0XCC , 0XCD , 0X5C , 0XE6 , 0X56 , 0X30 , 0XA9 , 0X2E , 0X82 , 0XFD , 0XD5 , 0X62 , 0X4C , 0X3E , 0XD1 , 0XBD , 0X2D , 0X8A , 0XE2 , 0X64 , 0XC0 , 0X7E , 0X5B , 0XAE , 0XD5 , 0X2B , 0X02 , 0XA1 , 0X3C};
    pt1[0]=ct[0];pt1[1]=ct[1];
    Inicializa_Estado(key);
    Encripta(pt1,ct);
    //Decripta(pt2,ct);
return 0;
}
