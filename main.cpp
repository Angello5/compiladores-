#include <iostream>
#include "scanner_comp.h"

using namespace std;

int main(){
    Scanner sc("input.isi");
    Token* token = nullptr;
    while (true)
    {
        token = sc.next_token();
        if (token != nullptr){
            token->to_string();
        }else{
            break;
        }
    }
    return 0;
}