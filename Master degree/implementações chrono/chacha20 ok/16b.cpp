/*--------------------------------------------------------------------
    Universidade Federal do Rio de Janeiro
    Autor: Victor Cracel Messner
*   Algoritmo de criptografia Chacha20
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
#include "stdio.h"
#include "string.h"
#include <chrono>

using namespace std;


#define U8to32(p)   \
	(((unsigned long int)(p[0])) | ((unsigned long int)(p[1]) <<  8) | \
	 ((unsigned long int)(p[2]) << 16) | ((unsigned long int)(p[3]) << 24)   )

#define ROTL32(v, n) (((v) << (n)) | ((v) >> (32 - (n))))

#define QUARTERROUND(x, a, b, c, d) \
    x[a] += x[b]; x[d] = ROTL32(x[d] ^ x[a], 16); \
    x[c] += x[d]; x[b] = ROTL32(x[b] ^ x[c], 12); \
    x[a] += x[b]; x[d] = ROTL32(x[d] ^ x[a], 8); \
    x[c] += x[d]; x[b] = ROTL32(x[b] ^ x[c], 7);

unsigned char lookup[103];
unsigned long int estado[16];
unsigned long int contador,pos,stream32[16];


void hex_to_raw(const char * src, unsigned char * word, int n ){
    int i;
    for (i = 0; i < n; ++i){
        word[i] = (lookup[src[i*2]] << 4) | lookup[src[i*2 + 1]];

    }
}

void Encripta(int n2,unsigned char * result){
    unsigned char *stream8 = (unsigned char*)stream32;
    int i;
    for (i = 0; i < n2; ++i){
        if (pos > 63){
            for (int i = 0; i < 16; ++i){
                stream32[i] = estado[i];
            }
            for (int i = 0; i < 10; ++i){
                QUARTERROUND(stream32, 0, 4, 8, 12)
                QUARTERROUND(stream32, 1, 5, 9, 13)
                QUARTERROUND(stream32, 2, 6, 10, 14)
                QUARTERROUND(stream32, 3, 7, 11, 15)
                QUARTERROUND(stream32, 0, 5, 10, 15)
                QUARTERROUND(stream32, 1, 6, 11, 12)
                QUARTERROUND(stream32, 2, 7, 8, 13)
                QUARTERROUND(stream32, 3, 4, 9, 14)
            }
            for (int i = 0; i < 16; ++i){
              stream32[i] += estado[i];
            }
            ++estado[12];
            if (!estado[12]){
                ++estado[13];
            }
        pos = 0;
            }
        result[i] ^= stream8[pos];
        ++pos;
        }
}

void Inicializa( const unsigned char chave[32],const unsigned char nonce[8]){

    const unsigned char * sigma = (unsigned char*) "expand 32-byte k";
    //const unsigned char * tau   = (unsigned char*) "expand 16-byte k";
    estado[0] = U8to32((sigma));
    estado[1] = U8to32((sigma + 4));
    estado[2] = U8to32((sigma + 8));
    estado[3] = U8to32((sigma + 12));
    estado[4] = U8to32((chave));
    estado[5] = U8to32((chave + 4));
    estado[6] = U8to32((chave + 8));
    estado[7] = U8to32((chave + 12));
    estado[8] = U8to32((chave + 16));
    estado[9] = U8to32((chave + 20));
    estado[10] = U8to32((chave + 24));
    estado[11] = U8to32((chave + 28));
    /*
    estado[8] = U8to32((chave + 0));
    estado[9] = U8to32((chave + 4));
    estado[10] = U8to32((chave + 8));
    estado[11] = U8to32((chave + 12));*/
    // 64 bit counter initialized to zero by default.
    estado[12] = 0;
    estado[13] = 0;
    estado[14] = U8to32((nonce));
    estado[15] = U8to32((nonce + 4));
    }

int main(){
    int i,e,n,n1,n2;
    contador = 0;
    unsigned char chave[16] ={ 0X1F , 0X6B , 0XD7 , 0X03 , 0X88 , 0X8F , 0X5E , 0X45 , 0XF4 , 0X2E , 0X0D , 0X35 , 0XE7 , 0XDA , 0X44 , 0X9E}; 
    unsigned char nonce[8]={0},result[2]={'a','\0'};
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> mediainit=std::chrono::duration<double>::zero(),valinit[1000];
    std::chrono::duration<double> mediaencrypt=std::chrono::duration<double>::zero(),valencrypt[1000];
for (int i=0;i<1000;++i){	
    start = std::chrono::system_clock::now(); // chrono start
    Inicializa(chave, nonce);
    pos=64;
    estado[12] = (unsigned long int) (contador);
    estado[13] = contador >> 32;
    end = std::chrono::system_clock::now();
    mediainit += end-start;
    valinit[i]= end-start;
    start = std::chrono::system_clock::now(); // chrono start
    Encripta(n2,result);
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
}

