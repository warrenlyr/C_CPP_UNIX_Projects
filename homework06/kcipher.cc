#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation

KCipher::KCipher(string newKey){
    //Check for valid first (no nothing-input)
    if(newKey == ""){
        cout << "Invalid key, nothing in there!" << endl;
        exit(EXIT_FAILURE);
    }
    //If valid, push it to key
    key.push_back(newKey);
}

string KCipher::encrypt(string text){
    //cout << "page: " << page << " " << "key size: " << key[page].size() << " " << "text size: " << text.size() << endl;
    //Check for valid first
    //Key size > text size (without space
    int count = 0; int textCount = 0;
    for(int i = 0; i < key[page].size(); i ++){
        if(key[page][i] != ' '){
            count ++;
        }
    }
    for(int i = 0; i < text.size(); i ++){
        if(text[i] != ' '){
        textCount ++;
        }
    }
    if(count < textCount){
        cout << "Book char < plain text char!" << endl;
        exit(EXIT_FAILURE);
    }
    //Nothing other than digit and alpha
    for(int i = 0; i < key[page].size(); i ++){
        if(!(key[page][i] == ' ' || isalpha(key[page][i]) || isdigit(key[page][i]))){
            cout << "Contain invalid input in key!" << endl;
            cout << key[page] << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    //Begin encrypt
    int i = 0;
    int j = 0;
    string str = "";
    while(text[i]){
        if(key[page][j] == ' '){
            j ++;
        }
        //Use parent's encrypt to do
        //Shift keyword's position and do the base encrypt
        //"CCipher(n)
        c = new CCipher(get_position(key[page][j]));
        string a;
        a.push_back(text[i]);
        str += c->encrypt(a);
        if(j < (key[page].size() - 1)){
            if(a != " "){
                j ++;
            }
        }
        else{
            j = 0;
        }
        i ++;
        //Tried here, deleting causes
        //          "deleting ptr not exist, idk why"
        //*********
        //delete c;
        //*********
    }
    
    return str;
}
string KCipher::decrypt(string text){
    //Exactly the same one
    //Except use decrypt instead encrypt
    //Because they are the exactly same algorithm
    int i = 0;
    int j = 0;
    string str = "";
    while(text[i]){
        if(key[page][j] == ' '){
            j ++;
        }
        c = new CCipher(get_position(key[page][j]));
        string a;
        a.push_back(text[i]);
        str += c->decrypt(a);
        if(j < (key[page].size() - 1)){
            if(a != " "){
                j ++;
            }
        }
        else{
            j = 0;
        }
        i ++;
        //delete c;
    }
    
    return str;
}

void KCipher::add_key(string newKey){
    //Check valid first
    if(newKey == ""){
        cout << "Invalid key, nothing in there!" << endl;
        exit(EXIT_FAILURE);
    }
    //If valid, pushback it
    key.push_back(newKey);
}

void KCipher::set_id(int newPage){
    //Check valid first
    if(newPage > (key.size() - 1)){
        cout << "Cannot set key, not exit!" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        //If valid, set it
        page = newPage;
    }
}

//function to return the position of alpha, like a is 0, z is 25
int get_position(char input){
    return input - 'a';
}
// -------------------------------------------------------

