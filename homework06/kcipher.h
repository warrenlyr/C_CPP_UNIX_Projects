#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function
class KCipher : public CCipher{
private:
    CCipher *c;
    int page;
    vector<string> key;
    
public:
    KCipher() : CCipher() {c = new CCipher(); add_key("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); page = 0;}
    KCipher(string);
    ~KCipher() {c->~CCipher();}
    
    string encrypt(string);
    string decrypt(string);
    
    void set_id(int newPage);
    void add_key(string);
};

int get_position(char);
#endif

