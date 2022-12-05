#include "SymmetricCipher.h"
#include <iostream>
#include <iomanip>
#include <crypto++/modes.h> // xxx_Mode< >
#include <crypto++/filters.h> // StringSource and
// StreamTransformation

// Cipher Modes
//
// #define CIPHER_MODE CBC_CTS_Mode
//#define CIPHER_MODE CBC_Mode
// #define CIPHER_MODE CFB_FIPS_Mode
// #define CIPHER_MODE CFB_Mode
// #define CIPHER_MODE CTR_Mode
 #define CIPHER_MODE ECB_Mode
// #define CIPHER_MODE OFB_Mode

// Ciphers
//
#define CIPHER AES
// #define CIPHER Blowfish
// #define CIPHER BTEA
// #define CIPHER Camellia
// #define CIPHER CAST128
// #define CIPHER CAST256
// #define CIPHER DES
// #define CIPHER DES_EDE2
// #define CIPHER DES_EDE3
// #define CIPHER DES_XEX3
// #define CIPHER GOST
// #define CIPHER IDEA
// #define CIPHER MARS
// #define CIPHER RC2
// #define CIPHER RC5
// #define CIPHER RC6
// #define CIPHER Rijndael
// #define CIPHER SAFER_K
// #define CIPHER SAFER_SK
// #define CIPHER Serpent
// #define CIPHER SHACAL2
// #define CIPHER SHARK
// #define CIPHER SKIPJACK
// #define CIPHER ThreeWay
// #define CIPHER Twofish
// #define CIPHER XTEA

int main(int argc, char* argv[]) {

	// Key and IV setup
	byte key[32] = { 0XC6 , 0XF8 , 0X65 , 0X01 , 0XBC , 0X07 , 0X80 , 0XB4 , 0X33 , 0X8B , 0X9A , 0XCD , 0XF7 , 0X12 , 0XB8 , 0XBB , 0XB9 , 0XCA , 0XFE , 0X6F , 0X80 , 0X45 , 0X9A , 0X56 , 0XEA , 0XDC , 0XB4 , 0XCE , 0XE3 , 0X5C , 0XF2 , 0XC9};
	//     iv[ CryptoPP::CIPHER::BLOCKSIZE ];
	//::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	//::memset( iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );
	std::string PlainText = "a";
	std::string CipherText;
CryptoPP::CIPHER_MODE<CryptoPP::CIPHER>::Encryption Encryptor;
//	Encryptor.SetKeyWithRounds(key,32,15);
        Encryptor.SetKey(key,32);
	CryptoPP::StringSource( PlainText, true,
	 new CryptoPP::StreamTransformationFilter( Encryptor,
	    new CryptoPP::StringSink( CipherText )
	 ) // StreamTransformationFilter
	); // StringSource
/*
      ///////////////////////////////////////
      // DMZ //
      ///////////////////////////////////////

      // Recovered Text Sink
      std::string RecoveredText;

      // Decryptor
      CryptoPP::CIPHER_MODE<CryptoPP::CIPHER>::Decryption
         Decryptor( key, sizeof(key), iv );

      // Decryption
      CryptoPP::StringSource( CipherText, true,
         new CryptoPP::StreamTransformationFilter( Decryptor,
            new CryptoPP::StringSink( RecoveredText )
         ) // StreamTransformationFilter
      ); // StringSource*/
   return 0;
}
