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
unsigned char chave[257]={ 0X61 , 0XA0};
unsigned char out[257]={'a','\0'};

	 std::chrono::time_point<std::chrono::system_clock> start, end;
   	 std::chrono::duration<double> mediainit=std::chrono::duration<double>::zero(),valinit[1000];
  	 std::chrono::duration<double> mediaencrypt=std::chrono::duration<double>::zero(),valencrypt[1000];
for (int i=0;i<1000;++i){	
	start = std::chrono::system_clock::now(); // chrono start       
	CryptoPP::Weak1::ARC4 arc4((byte*)chave, 2);
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

