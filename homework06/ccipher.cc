#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation
CCipher::CCipher(){
    c = new Cipher();
}

CCipher::CCipher(int rot){
    //Check for valid first (rot >= 0)
    if(rot < 0){
        cout << "Rot is less than 0!" << endl;
        exit(EXIT_FAILURE);
    }
    //Get the exactly shift position
    rot = rot % ALPHABET_SIZE;
    string key = "abcdefghijklmnopqrstuvwxyz";
    
    //Add wanted alpha to head, and delete them in the end
    key.insert(ALPHABET_SIZE, key,0, rot);
    key.erase(0, rot);
    
    //Set it with new one
    c = new Cipher(key);
}

//Use parent class's function to do it
//For these 3 functions
string CCipher::encrypt(string raw){
    string ans = c->encrypt(raw);
    return ans;
}

string CCipher::decrypt(string enc){
    string ans = c->decrypt(enc);
    return ans;
}

CCipher::~CCipher(){
    c->~Cipher();
}

// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    
}
