#include "/home/haruka/Downloads/cryptopp-master/chacha.h"
using CryptoPP::ChaCha8;
#include <chrono>
#include <iostream>
using std::cout;
using std::endl;

using std::string;

int main() {
std::chrono::time_point<std::chrono::system_clock> start, end;
   	 std::chrono::duration<double> mediainit=std::chrono::duration<double>::zero(),valinit[1000];
  	 std::chrono::duration<double> mediaencrypt=std::chrono::duration<double>::zero(),valencrypt[1000];
	//string ciphertextStr(""), plaintextStr("My Plaintext!! My Dear plaintext!!");
	byte plaintextBytes[2] ={'a','\0'};
	//I could statically allocate this, but then changes will require work, and typing
	byte ciphertextBytes[2] ={0};

	//~Key and IV Generation/Initialization======================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	byte key[16]={ 0X1F , 0X6B , 0XD7 , 0X03 , 0X88 , 0X8F , 0X5E , 0X45 , 0XF4 , 0X2E , 0X0D , 0X35 , 0XE7 , 0XDA , 0X44 , 0X9E};
	byte iv[8]={0};
//	prng.GenerateBlock(key, 32);
//	prng.GenerateBlock(iv, 8);

	//~Encryption================================================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	for (int i=0;i<1000;++i){	
	start = std::chrono::system_clock::now(); // chrono start        	
	
	ChaCha8::Encryption chacha;	      	
	chacha.SetKeyWithIV(key, 16, iv);


	end = std::chrono::system_clock::now();
	mediainit += end-start;
	valinit[i]= end-start;
	start = std::chrono::system_clock::now(); // chrono start

	chacha.ProcessData(ciphertextBytes, plaintextBytes, 2);


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
	//ciphertextStr.assign((char *) ciphertextBytes);

	//Output plaintext/ciphertext for sanity check
	//cout << "Plaintext: " << plaintextStr << endl;
	//cout << "Ciphertext: " << ciphertextStr << endl;

	//Reset plaintext (for sanity again)
	//plaintextStr.assign("");

	//Reset Key & IV
	//!!! THIS IS IMPORTANT: If you do not reset the stream cipher the data will
		//be encrypted again with a different part of the streaming key
		//Resetting the key & IV ensure that the same key is used, and we decrypt
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	//salsa.SetKeyWithIV(key, 32, iv);

	//~Decryption================================================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	//salsa.ProcessData(plaintextBytes, ciphertextBytes, ciphertextStr.length());
	//plaintextStr.assign((char *) plaintextBytes);

	//Output newly decrypted plaintext
	//cout << "Plaintext Again: " << plaintextStr << endl << endl;
	//cout << endl << "SALSA!" << endl << endl << "     " << "...20..." << endl;

	//delete ciphertextBytes;*/

	return 0;
}
