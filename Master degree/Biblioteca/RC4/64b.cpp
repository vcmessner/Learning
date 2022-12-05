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

//#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/arc4.h>



using namespace std;

int main(){
unsigned char chave[257]={ 0X27 , 0X7F , 0X43 , 0X00 , 0XA0 , 0X96 , 0X15 , 0X79 , 0XF8 , 0XC5 , 0X29 , 0X93 , 0X3F , 0XAE , 0X92 , 0X47 , 0XCC , 0X8C , 0X76 , 0X24 , 0XF1 , 0XB0 , 0X08 , 0X51 , 0XCC , 0X2C , 0XC6 , 0XB3 , 0X9E , 0XD6 , 0X2B , 0XF2 , 0X24 , 0XBB , 0X4E , 0XFE , 0X6F , 0XFF , 0X7E , 0X3C , 0XA8 , 0X69 , 0X0C , 0XE8 , 0X43 , 0X8B , 0XB2 , 0X1B , 0X20 , 0XE6 , 0XE5 , 0X8D , 0X04 , 0X72 , 0XF7 , 0XA2 , 0XE5 , 0XB5 , 0X32 , 0X1C , 0X92 , 0X40 , 0XAE , 0X7C};
unsigned char out[257]={'a','\0'};

CryptoPP::Weak1::ARC4 arc4((byte*)chave, 64);
arc4.ProcessData((byte*)out, (byte*)out, 2);
// Reset state
//arc4.SetKey((byte*)chave, 1);
//arc4.ProcessData((byte*)out, (byte*)out, 2);
//cout << out[0] << endl;
}

