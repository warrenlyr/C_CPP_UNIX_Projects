#ifndef RCIPHER_H_ 
#define RCIPHER_H_
#include "ccipher.h"

using namespace std;

/* A class that implements a
   ROT13 cipher class. It 
   inherts class CCipher */
// TODO: Implement this class
class RCipher : public CCipher{
    CCipher *c;
public:
    RCipher() : CCipher(13) {c = new CCipher(13);}
    ~RCipher();
    
    string encrypt(string raw);
    string decrypt(string raw);
};
#endif

