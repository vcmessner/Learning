/*--------------------------------------------------------------------
    Universidade Federal do Rio de Janeiro
    Autor: Victor Cracel Messner
*   Algoritmo de criptografia Trivium
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


#include <string.h>
#include "iostream"
#include <bitset>
//#include <string>
#include<stdio.h>
#include<chrono>

#define StreamBit(A,B,C,t1,t2,t3,Z)                      \
        t1 = (A[65]) ^ (A[92]);            \
        t2 = (B[68]) ^ (B[83]);             \
        t3 = (C[65]) ^ (C[110]);             \
        Z = t1 ^t2 ^t3;                       \
        t1= t1 ^ (A[90]&A[91])   ^ (B[77]);    \
        t2= t2 ^ (B[81]&B[82])   ^ (C[86]);     \
        t3= t3 ^ (C[108]&C[109]) ^ (A[68]);      \
        A<<=1;B<<=1;C<<=1;                        \
        A[0]=t3;B[0]=t1;C[0]=t2;                   \

#define Inicializa(A,B,C,chave,nonce)              \
for (i=0;i<10;++i){                  \
        Preenche(A,B,C,chave,nonce)  \
    }                                \
    C[110]=1;C[109]=1;C[108]=1;      \
    for (i=0;i<4*288;++i){           \
        Rotaciona(A,B,C)             \
    }                                \

#define Preenche(A, B, C, chave, nonce) \
    A[j]=chave[i]&1; B[j++]=nonce[i]&1; \
    A[j]=chave[i]&2; B[j++]=nonce[i]&2; \
    A[j]=chave[i]&4; B[j++]=nonce[i]&4; \
    A[j]=chave[i]&8; B[j++]=nonce[i]&8; \
    A[j]=chave[i]&16;B[j++]=nonce[i]&16; \
    A[j]=chave[i]&32;B[j++]=nonce[i]&32; \
    A[j]=chave[i]&64;B[j++]=nonce[i]&64; \
    A[j]=chave[i]&128;B[j++]=nonce[i]&128;

#define Rotaciona(A, B, C) \
    t1 = (A[65]) ^ (A[90]&A[91]) ^ (A[92]) ^ (B[77]);\
    t2 = (B[68]) ^ (B[81]&B[82]) ^ (B[83]) ^ (C[86]);\
    t3 = (C[65]) ^ (C[108]&C[109]) ^ (C[110]) ^ (A[68]);\
    A<<=1;B<<=1;C<<=1;\
    A[0]=t3;B[0]=t1;C[0]=t2;

using namespace std;

unsigned char lookup[103];

void hex_to_raw(const char * src, unsigned char * word, int n ){
    int i;
    for (i = 0; i < n; ++i){
        word[i] = (lookup[src[i*2]] << 4) | lookup[src[i*2 + 1]];

    }
}

int main(){
    char *txtchave,*txtnonce,*txtplain,*txtcrypt;
    unsigned char a;
    int j = 0,i,n,n1;
    bool t1,t2,t3,Z;
    unsigned char pt='a',ct,ct2,nonce[10]={0};
    unsigned char chave[10]={ 0X61 , 0XA0};
std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> mediainit=std::chrono::duration<double>::zero(),valinit[1000];
    std::chrono::duration<double> mediaencrypt=std::chrono::duration<double>::zero(),valencrypt[1000];
    for (int i=0;i<1000;++i){	
    start = std::chrono::system_clock::now(); // chrono start
    //hex_to_raw(txtchave,chave,n);
    //hex_to_raw(txtnonce,nonce,n1);
    bitset<93>  A(0); //[1-93]
    bitset<84>  B(0); //[94-177]
    bitset<111> C(0); //[178-288]

    a=0;j=0;

    //Encriptação
    //Inicialização
    Inicializa(A,B,C,chave,nonce)
end = std::chrono::system_clock::now();
    mediainit += end-start;
    valinit[i]= end-start;
    start = std::chrono::system_clock::now(); // chrono start        
    for (i=0;i<8;++i){ //pegando 1 byte
        StreamBit(A,B,C,t1,t2,t3,Z)
        a|=Z;
        a<<=1;
    }
    ct = pt^a;
end = std::chrono::system_clock::now();
	mediaencrypt += end-start;
	valencrypt[i]= end-start;
	}
	double dpin=0,mediain,dpen=0,mediaen;
	mediain = mediainit.count()/1000.00;
	mediaen = mediaencrypt.count()/1000.00;
	for (int i=0;i<1000;++i){
		dpin += (valinit[1].count()-mediain) * (valinit[1].count()-mediain);
		dpen += (valencrypt[1].count()-mediaen) * (valencrypt[1].count()-mediaen);
	}
	dpin /=1000;
	dpen /=1000;
	cout << "Media de inicialização" << endl;	
	cout << mediain << endl;
	cout << "Variância de inicialização" << endl;	
 	cout << dpin << endl;
	cout << "Media de Encriptação" << endl;	
	cout << mediaen << endl;
	cout << "Variância de Encriptação" << endl;	
	cout << dpen << endl;
    //decrypt
    /* j=0;a=0;A.reset();B.reset();C.reset();
    for (i=0;i<10;++i){
        Inicializa(A,B,C,chave,nonce)
    }
    for (i=0;i<8;++i){ //pegando 1 byte
        StreamBit(A,B,C,t1,t2,t3,Z)
        a|=Z;
        a<<=1;
    }
    ct2 = ct^a;
    cout << pt << " " <<  ct << " " << ct2 << endl;
	*/
return 0;
}
