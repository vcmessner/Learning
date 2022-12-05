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
#define r 14    // número de rounds
//#define r 20     // padrão de rounds
#define b 128   // tamanho da chave
#define c 32   // 8b/w ou b/u
#define t 32 // 2* (r+2)
//#define t 44 // t padrão
#define lgw 5 // log_2(w)
#define P 0xb7e15163ul
#define Q 0x9e3779b9ul

#define ROTL(v,n) (((v)<<(n))|((v)>>(32-(n))))
#define ROTR(v,n) (((v)>>(n))|((v)<<(32-(n))))

//#define ROTL(x,y) (((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1)))))
//#define ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1)))))

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
        //i=(i+1)%t;
        L[j]= ROTL(L[j]+A+B,(A+B));
        B=L[j];
        j=(j+1)&31;
        //j=(j+1)%c;
}}

inline void Encripta(unsigned long int * pt, unsigned long int * ct){
   unsigned long int i,A=pt[0],B=pt[1]+S[0],C=pt[2],D=pt[3]+S[1],u,k;
   for (i=1;i<=r;++i){
    k = ROTL(B*(2*B+1),lgw);
    u = ROTL(D*(2*D+1),lgw);
    A = ROTL(A^k,u)+S[2*i];
    C = ROTL(C^u,k)+S[2*i+1];
    u=A;A=B;B=C;C=D;D=u;
   }
   A+=S[t-2];
   C+=S[t-1];
   ct[0]=A;ct[1]=B;ct[2]=C;ct[3]=D;
}


inline void Decripta(unsigned long int * pt, unsigned long int * ct){
   unsigned long int i,B=ct[1],A=ct[0]-S[t-2],C=ct[2]-S[t-1],D=ct[3],u,k;
   for (i=r;i>0;--i){
    u=D;D=C;C=B;B=A;A=u;
    //(A,B,C,D)=(D,A,B,C);
    u=ROTL(D*(2*D+1),lgw);
    k=ROTL(B*(2*B+1),lgw);
    C=ROTR(C-S[2*i+1],k)^u;
    A=ROTR(A-S[2*i],u)^k;}
    D-=S[1];
    B-=S[0];
    pt[1]=B;pt[0]=A;pt[2]=C;pt[3]=D;
}

int main (){
    unsigned char i,j,k;
    unsigned long int pt1[4]={'a','a','a','\0'},ct[4]={0,0,0,0};
    unsigned char key[b]={ 0X48 , 0X1C , 0X87 , 0X1B , 0X57 , 0X02 , 0XD3 , 0XB4 , 0X94 , 0X91 , 0XFA , 0X75 , 0XD6 , 0X6B , 0X04 , 0XC3 , 0XAB , 0XAB , 0X8C , 0XA5 , 0X72 , 0X37 , 0XEA , 0X44 , 0X5B , 0X57 , 0X8B , 0X22 , 0X60 , 0X68 , 0X7A , 0X39 , 0X89 , 0XB2 , 0XAF , 0XC0 , 0XC1 , 0X63 , 0X47 , 0X3D , 0XB0 , 0XE2 , 0X1D , 0X06 , 0XB0 , 0X90 , 0X6E , 0X3C , 0X2E , 0X48 , 0X3B , 0XC8 , 0XAD , 0X4A , 0XA8 , 0XAD , 0XC8 , 0X41 , 0X12 , 0XC5 , 0XFB , 0X04 , 0X1D , 0X75 , 0X1A , 0X05 , 0XA8 , 0X1A , 0XBA , 0X49 , 0XB1 , 0X66 , 0X7B , 0X5D , 0X6A , 0XF9 , 0XA2 , 0X81 , 0XC8 , 0X4D , 0XFA , 0XCF , 0XF3 , 0X0A , 0X24 , 0X9F , 0X2E , 0X73 , 0X00 , 0X41 , 0XA4 , 0XDF , 0XDC , 0XBE , 0X66 , 0XE4 , 0XB8 , 0X78 , 0XDF , 0XCC , 0XCD , 0X5C , 0XE6 , 0X56 , 0X30 , 0XA9 , 0X2E , 0X82 , 0XFD , 0XD5 , 0X62 , 0X4C , 0X3E , 0XD1 , 0XBD , 0X2D , 0X8A , 0XE2 , 0X64 , 0XC0 , 0X7E , 0X5B , 0XAE , 0XD5 , 0X2B , 0X02 , 0XA1 , 0X3C};
    Inicializa_Estado(key);
    Encripta(pt1,ct);
   // Decripta(pt2,ct);
    return 0;
}
