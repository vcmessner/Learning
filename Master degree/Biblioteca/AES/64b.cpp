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
	byte key[64] = { 0X27 , 0X7F , 0X43 , 0X00 , 0XA0 , 0X96 , 0X15 , 0X79 , 0XF8 , 0XC5 , 0X29 , 0X93 , 0X3F , 0XAE , 0X92 , 0X47 , 0XCC , 0X8C , 0X76 , 0X24 , 0XF1 , 0XB0 , 0X08 , 0X51 , 0XCC , 0X2C , 0XC6 , 0XB3 , 0X9E , 0XD6 , 0X2B , 0XF2 , 0X24 , 0XBB , 0X4E , 0XFE , 0X6F , 0XFF , 0X7E , 0X3C , 0XA8 , 0X69 , 0X0C , 0XE8 , 0X43 , 0X8B , 0XB2 , 0X1B , 0X20 , 0XE6 , 0XE5 , 0X8D , 0X04 , 0X72 , 0XF7 , 0XA2 , 0XE5 , 0XB5 , 0X32 , 0X1C , 0X92 , 0X40 , 0XAE , 0X7C};
	//     iv[ CryptoPP::CIPHER::BLOCKSIZE ];
	//::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	//::memset( iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );
	std::string PlainText = "a";
	std::string CipherText;
	CryptoPP::CIPHER_MODE<CryptoPP::CIPHER>::Encryption Encryptor;
//	Encryptor.SetKeyWithRounds(key,64,15);
        Encryptor.SetKey(key,64);
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
