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
//#define CIPHER AES
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
 #define CIPHER RC5
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
	byte key[128] = { 0X48 , 0X1C , 0X87 , 0X1B , 0X57 , 0X02 , 0XD3 , 0XB4 , 0X94 , 0X91 , 0XFA , 0X75 , 0XD6 , 0X6B , 0X04 , 0XC3 , 0XAB , 0XAB , 0X8C , 0XA5 , 0X72 , 0X37 , 0XEA , 0X44 , 0X5B , 0X57 , 0X8B , 0X22 , 0X60 , 0X68 , 0X7A , 0X39 , 0X89 , 0XB2 , 0XAF , 0XC0 , 0XC1 , 0X63 , 0X47 , 0X3D , 0XB0 , 0XE2 , 0X1D , 0X06 , 0XB0 , 0X90 , 0X6E , 0X3C , 0X2E , 0X48 , 0X3B , 0XC8 , 0XAD , 0X4A , 0XA8 , 0XAD , 0XC8 , 0X41 , 0X12 , 0XC5 , 0XFB , 0X04 , 0X1D , 0X75 , 0X1A , 0X05 , 0XA8 , 0X1A , 0XBA , 0X49 , 0XB1 , 0X66 , 0X7B , 0X5D , 0X6A , 0XF9 , 0XA2 , 0X81 , 0XC8 , 0X4D , 0XFA , 0XCF , 0XF3 , 0X0A , 0X24 , 0X9F , 0X2E , 0X73 , 0X00 , 0X41 , 0XA4 , 0XDF , 0XDC , 0XBE , 0X66 , 0XE4 , 0XB8 , 0X78 , 0XDF , 0XCC , 0XCD , 0X5C , 0XE6 , 0X56 , 0X30 , 0XA9 , 0X2E , 0X82 , 0XFD , 0XD5 , 0X62 , 0X4C , 0X3E , 0XD1 , 0XBD , 0X2D , 0X8A , 0XE2 , 0X64 , 0XC0 , 0X7E , 0X5B , 0XAE , 0XD5 , 0X2B , 0X02 , 0XA1 , 0X3C};
	//     iv[ CryptoPP::CIPHER::BLOCKSIZE ];
	//::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	//::memset( iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );
	std::string PlainText = "a";
	std::string CipherText;
	
	CryptoPP::CIPHER_MODE<CryptoPP::CIPHER>::Encryption Encryptor;
	Encryptor.SetKeyWithRounds(key,128,15);
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
