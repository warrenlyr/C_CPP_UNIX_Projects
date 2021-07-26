#include <string>
#include <iostream>
#include <vector>
#include "ccipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------
VCipher::VCipher(string newKey){
    //Because checked for key's length in the rcipher
    //If I want to use parent's method
    //I have to make key size > text size
    for(int i = 0; i < newKey.size(); i ++){
        string a;
        a.push_back(newKey[i]);
        //But if key is a space, which is not valid
        //Exit
        if(a == " "){
            cout << "Invalid key!" << endl;
            exit(EXIT_FAILURE);
        }
        //a.erase();
    }
    string key = "";
    for(int i = 0; key.size() < MAX_LENGTH; i ++){
        key += newKey;
    }
    cout << key << endl << key.size() << endl;
    
    c = new KCipher(key);
    c->set_id(0);
}
