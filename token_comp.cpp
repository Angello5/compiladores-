#include "token_comp.h"
#include <iostream>

using namespace std;

const int Token::Tk_identifier =0;
const int Token::Tk_number =1;
const int Token::Tk_operator = 2;
const int Token::Tk_punctuantion = 3;
const int Token::Tk_assign = 4;
const int Token::Tk_hola = 5;

const string Token::Tk_text[]= {"IDENTIFICADOR", "NUMERO","OPERADOR","PUNTUACION","ASIGNACION"};

Token::Token(int type, const std::string& text, int line, int column)
    : type(type), text(text), line(line), column(column) {}

void Token::set_type(int type) {
    this->type = type;
}

int Token::get_type() const {
    return type;
}

void Token::set_text(const string& text) {
    this->text = text;
}

const string& Token::get_text() const {
    return text;
}

void Token::set_line(int line) {
    this->line = line;
}

int Token::get_line() const {
    return line;
}

void Token::set_column(int column) {
    this->column = column;
}

int Token::get_column() const {
    return column;
}

void Token::to_string() const {
    string type_text = (type != -1 && type < 5) ? Tk_text[type] : "None";
    cout << "Token [type=" << type_text << ", text=" << text << ", line=" << line << ", column=" << column << "]" << endl;
}