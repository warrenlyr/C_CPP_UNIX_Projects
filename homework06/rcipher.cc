#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// Caesar Cipher implementation
// -------------------------------------------------------
RCipher::~RCipher(){
    c->~CCipher();
}

//Nothing to do here, rot13 = ccipher(13)
string RCipher::encrypt(string raw){
    return CCipher::encrypt(raw);
}

string RCipher::decrypt(string enc){
    return CCipher::decrypt(enc);
}
