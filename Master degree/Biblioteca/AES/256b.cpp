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
	byte key[256] = { 0XA5 , 0XD7 , 0X9C , 0X7B , 0X8D , 0X45 , 0X6B , 0X3F , 0X1C , 0X49 , 0X90 , 0XDE , 0XF5 , 0XCE , 0X6F , 0XF1 , 0X02 , 0X2B , 0X3B , 0XE8 , 0X8D , 0X31 , 0XE7 , 0X8C , 0XFC , 0X94 , 0XDD , 0X83 , 0X1A , 0X0B , 0X2F , 0X47 , 0XEF , 0XCD , 0X8D , 0XF6 , 0XE9 , 0X6C , 0X04 , 0X8D , 0XF8 , 0XB0 , 0X3E , 0XC8 , 0X6B , 0XD5 , 0X72 , 0X51 , 0X1B , 0X10 , 0X68 , 0X62 , 0XAD , 0X22 , 0X16 , 0X8F , 0X53 , 0X31 , 0XED , 0X41 , 0XF5 , 0X17 , 0XA6 , 0X79 , 0XCA , 0XA2 , 0X8F , 0X8C , 0X64 , 0XF5 , 0XEF , 0X72 , 0X42 , 0X20 , 0X95 , 0X0E , 0X69 , 0XF2 , 0XD3 , 0X08 , 0X7E , 0XA2 , 0XDD , 0X81 , 0X1F , 0XE1 , 0XA9 , 0XCF , 0X46 , 0XA1 , 0XAC , 0X6C , 0XED , 0X05 , 0X79 , 0X8C , 0X46 , 0X50 , 0XCC , 0XE5 , 0X3E , 0X13 , 0X26 , 0X8B , 0X92 , 0XEE , 0XB8 , 0XC7 , 0XAA , 0XF5 , 0X9E , 0X7D , 0X10 , 0X2A , 0X31 , 0X7E , 0X23 , 0XFF , 0X1A , 0XAB , 0X31 , 0X60 , 0X55 , 0X10 , 0XAC , 0XA0 , 0X39 , 0XA4 , 0XEC , 0XB1 , 0XDC , 0X37 , 0XD3 , 0X02 , 0X2E , 0XF4 , 0XFD , 0XF6 , 0X7A , 0X5A , 0X4D , 0XF1 , 0X88 , 0X8E , 0X18 , 0X6C , 0X44 , 0X0F , 0X38 , 0X9A , 0X2B , 0X0A , 0XB5 , 0XEB , 0X72 , 0X48 , 0XF0 , 0X5A , 0X05 , 0X3B , 0X1F , 0X5A , 0XBD , 0X33 , 0X06 , 0XE4 , 0X59 , 0X07 , 0X6E , 0X97 , 0XE9 , 0XC4 , 0XBF , 0X2B , 0XA0 , 0XF0 , 0XBD , 0X5D , 0X55 , 0XE8 , 0X2B , 0XE6 , 0XB5 , 0X0C , 0XFD , 0X2B , 0XAF , 0X81 , 0X69 , 0XEF , 0X27 , 0X2A , 0X1E , 0X85 , 0XD5 , 0X50 , 0X7B , 0X0D , 0XBB , 0X14 , 0X6F , 0XE7 , 0XA7 , 0XE0 , 0XE7 , 0X66 , 0XDC , 0XBF , 0X09 , 0X0E , 0X0A , 0X8D , 0X05 , 0X12 , 0X0C , 0X54 , 0X41 , 0XA8 , 0X8A , 0X9E , 0X03 , 0X11 , 0X4D , 0XD9 , 0XDB , 0XE2 , 0X4C , 0X4F , 0XA7 , 0X97 , 0XD2 , 0X47 , 0X9D , 0X38 , 0XEB , 0XE9 , 0X91 , 0X72 , 0X32 , 0XB5 , 0XE1 , 0XA6 , 0X2A , 0X70 , 0X13 , 0XFE , 0X91 , 0XDD , 0X99 , 0XDC , 0XEC , 0XE4 , 0XE0 , 0X2A , 0X61 , 0X46};
	//     iv[ CryptoPP::CIPHER::BLOCKSIZE ];
	//::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	//::memset( iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );
	std::string PlainText = "a";
	std::string CipherText;
	 CryptoPP::CIPHER_MODE<CryptoPP::CIPHER>::Encryption Encryptor;
	//Encryptor.SetKeyWithRounds(key,256,15);
        Encryptor.SetKey(key,256);
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
