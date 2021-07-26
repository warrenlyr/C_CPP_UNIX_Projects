#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class
class CCipher : public Cipher{
private:
    Cipher *c;
public:
    CCipher();
    CCipher(int rot);
    ~CCipher();
    
    string encrypt(string raw);
    string decrypt(string enc);
};

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

