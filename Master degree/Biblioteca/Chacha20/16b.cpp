#include "/home/haruka/Downloads/cryptopp-master/chacha.h"
using CryptoPP::ChaCha8;

#include <iostream>
using std::cout;
using std::endl;

using std::string;

int main() {

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
	ChaCha8::Encryption chacha;	
	chacha.SetKeyWithIV(key, 16, iv);
	chacha.ProcessData(ciphertextBytes, plaintextBytes, 2);
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
