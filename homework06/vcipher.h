#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
// TODO: Implement this class
class VCipher : public KCipher{
    KCipher *c;
public:
    VCipher() : KCipher() {c = new KCipher();}
    VCipher(string newKey);
    ~VCipher() {c->~KCipher();}
    
    string encrypt(string text) {return c->encrypt(text);}
    string decrypt(string text) {return c->decrypt(text);}
};

#endif

