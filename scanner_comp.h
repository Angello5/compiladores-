#ifndef SCANNER_H
#define SCANNER_H

#include "token_comp.h"
#include <fstream>
#include <iostream>
#include <vector>

class Scanner {
public:
    Scanner(const string& filename);
    Token* next_token();

private:
    int line;
    int column;
    vector<char> content;
    size_t pos;

    char next_char();
    bool is_eof();
    void back();
    bool is_eof_char(char c);
    bool is_digit(char c);
    bool is_char(char c);
    bool is_operator(char c);
    bool is_space(char c);
};

#endif 
