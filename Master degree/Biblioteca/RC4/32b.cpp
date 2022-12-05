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
unsigned char chave[257]={ 0XC6 , 0XF8 , 0X65 , 0X01 , 0XBC , 0X07 , 0X80 , 0XB4 , 0X33 , 0X8B , 0X9A , 0XCD , 0XF7 , 0X12 , 0XB8 , 0XBB , 0XB9 , 0XCA , 0XFE , 0X6F , 0X80 , 0X45 , 0X9A , 0X56 , 0XEA , 0XDC , 0XB4 , 0XCE , 0XE3 , 0X5C , 0XF2 , 0XC9};
unsigned char out[257]={'a','\0'};

CryptoPP::Weak1::ARC4 arc4((byte*)chave, 32);
arc4.ProcessData((byte*)out, (byte*)out, 2);
// Reset state
//arc4.SetKey((byte*)chave, 1);
//arc4.ProcessData((byte*)out, (byte*)out, 2);
//cout << out[0] << endl;
}

