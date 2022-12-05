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
#define b 256   // tamanho da chave
#define c 64  // 8b/w ou b/u
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
    A=B=i=j=0;u=3*c; //m = max(c, t); u=3*m
    for (k=0;k<u;++k){
        S[i]= ROTL(S[i]+A+B,3);
        A=S[i];
        i=(i+1)&31;
        L[j]= ROTL(L[j]+A+B,(A+B));
        B=L[j];
        j=(j+1)&63;
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
    unsigned char key[b] = { 0XA5 , 0XD7 , 0X9C , 0X7B , 0X8D , 0X45 , 0X6B , 0X3F , 0X1C , 0X49 , 0X90 , 0XDE , 0XF5 , 0XCE , 0X6F , 0XF1 , 0X02 , 0X2B , 0X3B , 0XE8 , 0X8D , 0X31 , 0XE7 , 0X8C , 0XFC , 0X94 , 0XDD , 0X83 , 0X1A , 0X0B , 0X2F , 0X47 , 0XEF , 0XCD , 0X8D , 0XF6 , 0XE9 , 0X6C , 0X04 , 0X8D , 0XF8 , 0XB0 , 0X3E , 0XC8 , 0X6B , 0XD5 , 0X72 , 0X51 , 0X1B , 0X10 , 0X68 , 0X62 , 0XAD , 0X22 , 0X16 , 0X8F , 0X53 , 0X31 , 0XED , 0X41 , 0XF5 , 0X17 , 0XA6 , 0X79 , 0XCA , 0XA2 , 0X8F , 0X8C , 0X64 , 0XF5 , 0XEF , 0X72 , 0X42 , 0X20 , 0X95 , 0X0E , 0X69 , 0XF2 , 0XD3 , 0X08 , 0X7E , 0XA2 , 0XDD , 0X81 , 0X1F , 0XE1 , 0XA9 , 0XCF , 0X46 , 0XA1 , 0XAC , 0X6C , 0XED , 0X05 , 0X79 , 0X8C , 0X46 , 0X50 , 0XCC , 0XE5 , 0X3E , 0X13 , 0X26 , 0X8B , 0X92 , 0XEE , 0XB8 , 0XC7 , 0XAA , 0XF5 , 0X9E , 0X7D , 0X10 , 0X2A , 0X31 , 0X7E , 0X23 , 0XFF , 0X1A , 0XAB , 0X31 , 0X60 , 0X55 , 0X10 , 0XAC , 0XA0 , 0X39 , 0XA4 , 0XEC , 0XB1 , 0XDC , 0X37 , 0XD3 , 0X02 , 0X2E , 0XF4 , 0XFD , 0XF6 , 0X7A , 0X5A , 0X4D , 0XF1 , 0X88 , 0X8E , 0X18 , 0X6C , 0X44 , 0X0F , 0X38 , 0X9A , 0X2B , 0X0A , 0XB5 , 0XEB , 0X72 , 0X48 , 0XF0 , 0X5A , 0X05 , 0X3B , 0X1F , 0X5A , 0XBD , 0X33 , 0X06 , 0XE4 , 0X59 , 0X07 , 0X6E , 0X97 , 0XE9 , 0XC4 , 0XBF , 0X2B , 0XA0 , 0XF0 , 0XBD , 0X5D , 0X55 , 0XE8 , 0X2B , 0XE6 , 0XB5 , 0X0C , 0XFD , 0X2B , 0XAF , 0X81 , 0X69 , 0XEF , 0X27 , 0X2A , 0X1E , 0X85 , 0XD5 , 0X50 , 0X7B , 0X0D , 0XBB , 0X14 , 0X6F , 0XE7 , 0XA7 , 0XE0 , 0XE7 , 0X66 , 0XDC , 0XBF , 0X09 , 0X0E , 0X0A , 0X8D , 0X05 , 0X12 , 0X0C , 0X54 , 0X41 , 0XA8 , 0X8A , 0X9E , 0X03 , 0X11 , 0X4D , 0XD9 , 0XDB , 0XE2 , 0X4C , 0X4F , 0XA7 , 0X97 , 0XD2 , 0X47 , 0X9D , 0X38 , 0XEB , 0XE9 , 0X91 , 0X72 , 0X32 , 0XB5 , 0XE1 , 0XA6 , 0X2A , 0X70 , 0X13 , 0XFE , 0X91 , 0XDD , 0X99 , 0XDC , 0XEC , 0XE4 , 0XE0 , 0X2A , 0X61 , 0X46};
    pt1[0]=ct[0];pt1[1]=ct[1];
    Inicializa_Estado(key);
    Encripta(pt1,ct);
    //Decripta(pt2,ct);
return 0;
}
