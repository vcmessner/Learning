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



#include <chrono>
using namespace std;

int main(){
unsigned char chave[257]={ 0X48 , 0X1C , 0X87 , 0X1B , 0X57 , 0X02 , 0XD3 , 0XB4 , 0X94 , 0X91 , 0XFA , 0X75 , 0XD6 , 0X6B , 0X04 , 0XC3 , 0XAB , 0XAB , 0X8C , 0XA5 , 0X72 , 0X37 , 0XEA , 0X44 , 0X5B , 0X57 , 0X8B , 0X22 , 0X60 , 0X68 , 0X7A , 0X39 , 0X89 , 0XB2 , 0XAF , 0XC0 , 0XC1 , 0X63 , 0X47 , 0X3D , 0XB0 , 0XE2 , 0X1D , 0X06 , 0XB0 , 0X90 , 0X6E , 0X3C , 0X2E , 0X48 , 0X3B , 0XC8 , 0XAD , 0X4A , 0XA8 , 0XAD , 0XC8 , 0X41 , 0X12 , 0XC5 , 0XFB , 0X04 , 0X1D , 0X75 , 0X1A , 0X05 , 0XA8 , 0X1A , 0XBA , 0X49 , 0XB1 , 0X66 , 0X7B , 0X5D , 0X6A , 0XF9 , 0XA2 , 0X81 , 0XC8 , 0X4D , 0XFA , 0XCF , 0XF3 , 0X0A , 0X24 , 0X9F , 0X2E , 0X73 , 0X00 , 0X41 , 0XA4 , 0XDF , 0XDC , 0XBE , 0X66 , 0XE4 , 0XB8 , 0X78 , 0XDF , 0XCC , 0XCD , 0X5C , 0XE6 , 0X56 , 0X30 , 0XA9 , 0X2E , 0X82 , 0XFD , 0XD5 , 0X62 , 0X4C , 0X3E , 0XD1 , 0XBD , 0X2D , 0X8A , 0XE2 , 0X64 , 0XC0 , 0X7E , 0X5B , 0XAE , 0XD5 , 0X2B , 0X02 , 0XA1 , 0X3C};
unsigned char out[257]={'a','\0'};

	 std::chrono::time_point<std::chrono::system_clock> start, end;
   	 std::chrono::duration<double> mediainit=std::chrono::duration<double>::zero(),valinit[1000];
  	 std::chrono::duration<double> mediaencrypt=std::chrono::duration<double>::zero(),valencrypt[1000];
for (int i=0;i<1000;++i){	
	start = std::chrono::system_clock::now(); // chrono start       
	CryptoPP::Weak1::ARC4 arc4((byte*)chave, 128);
	end = std::chrono::system_clock::now();
	mediainit += end-start;
	valinit[i]= end-start;
	start = std::chrono::system_clock::now(); // chrono start        
	arc4.ProcessData((byte*)out, (byte*)out, 2);
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
// Reset state
//arc4.SetKey((byte*)chave, 1);
//arc4.ProcessData((byte*)out, (byte*)out, 2);
//cout << out[0] << endl;
}

