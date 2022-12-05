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
#define b 256   // tamanho da chave
#define c 64   // 8b/w ou b/u
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
    A=B=i=j=0;u=3*c; //m = max(c, t); u=3*m
    for (k=0;k<u;++k){
        S[i]= ROTL(S[i]+A+B,3);
        A=S[i];
        i=(i+1)&31;
        //i=(i+1)%t;
        L[j]= ROTL(L[j]+A+B,(A+B));
        B=L[j];
        j=(j+1)&63;
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
    unsigned char key[b]={ 0XA5 , 0XD7 , 0X9C , 0X7B , 0X8D , 0X45 , 0X6B , 0X3F , 0X1C , 0X49 , 0X90 , 0XDE , 0XF5 , 0XCE , 0X6F , 0XF1 , 0X02 , 0X2B , 0X3B , 0XE8 , 0X8D , 0X31 , 0XE7 , 0X8C , 0XFC , 0X94 , 0XDD , 0X83 , 0X1A , 0X0B , 0X2F , 0X47 , 0XEF , 0XCD , 0X8D , 0XF6 , 0XE9 , 0X6C , 0X04 , 0X8D , 0XF8 , 0XB0 , 0X3E , 0XC8 , 0X6B , 0XD5 , 0X72 , 0X51 , 0X1B , 0X10 , 0X68 , 0X62 , 0XAD , 0X22 , 0X16 , 0X8F , 0X53 , 0X31 , 0XED , 0X41 , 0XF5 , 0X17 , 0XA6 , 0X79 , 0XCA , 0XA2 , 0X8F , 0X8C , 0X64 , 0XF5 , 0XEF , 0X72 , 0X42 , 0X20 , 0X95 , 0X0E , 0X69 , 0XF2 , 0XD3 , 0X08 , 0X7E , 0XA2 , 0XDD , 0X81 , 0X1F , 0XE1 , 0XA9 , 0XCF , 0X46 , 0XA1 , 0XAC , 0X6C , 0XED , 0X05 , 0X79 , 0X8C , 0X46 , 0X50 , 0XCC , 0XE5 , 0X3E , 0X13 , 0X26 , 0X8B , 0X92 , 0XEE , 0XB8 , 0XC7 , 0XAA , 0XF5 , 0X9E , 0X7D , 0X10 , 0X2A , 0X31 , 0X7E , 0X23 , 0XFF , 0X1A , 0XAB , 0X31 , 0X60 , 0X55 , 0X10 , 0XAC , 0XA0 , 0X39 , 0XA4 , 0XEC , 0XB1 , 0XDC , 0X37 , 0XD3 , 0X02 , 0X2E , 0XF4 , 0XFD , 0XF6 , 0X7A , 0X5A , 0X4D , 0XF1 , 0X88 , 0X8E , 0X18 , 0X6C , 0X44 , 0X0F , 0X38 , 0X9A , 0X2B , 0X0A , 0XB5 , 0XEB , 0X72 , 0X48 , 0XF0 , 0X5A , 0X05 , 0X3B , 0X1F , 0X5A , 0XBD , 0X33 , 0X06 , 0XE4 , 0X59 , 0X07 , 0X6E , 0X97 , 0XE9 , 0XC4 , 0XBF , 0X2B , 0XA0 , 0XF0 , 0XBD , 0X5D , 0X55 , 0XE8 , 0X2B , 0XE6 , 0XB5 , 0X0C , 0XFD , 0X2B , 0XAF , 0X81 , 0X69 , 0XEF , 0X27 , 0X2A , 0X1E , 0X85 , 0XD5 , 0X50 , 0X7B , 0X0D , 0XBB , 0X14 , 0X6F , 0XE7 , 0XA7 , 0XE0 , 0XE7 , 0X66 , 0XDC , 0XBF , 0X09 , 0X0E , 0X0A , 0X8D , 0X05 , 0X12 , 0X0C , 0X54 , 0X41 , 0XA8 , 0X8A , 0X9E , 0X03 , 0X11 , 0X4D , 0XD9 , 0XDB , 0XE2 , 0X4C , 0X4F , 0XA7 , 0X97 , 0XD2 , 0X47 , 0X9D , 0X38 , 0XEB , 0XE9 , 0X91 , 0X72 , 0X32 , 0XB5 , 0XE1 , 0XA6 , 0X2A , 0X70 , 0X13 , 0XFE , 0X91 , 0XDD , 0X99 , 0XDC , 0XEC , 0XE4 , 0XE0 , 0X2A , 0X61 , 0X46};
    Inicializa_Estado(key);
    Encripta(pt1,ct);
   // Decripta(pt2,ct);
    return 0;
}
