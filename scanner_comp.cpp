#include "scanner_comp.h"
#include <string>

using namespace std;

Scanner::Scanner(const string& filename) : line(1), column(0), pos(0) {
    ifstream file(filename);
    if (file.is_open()) {
        string txt_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        content.assign(txt_content.begin(), txt_content.end());
    } else {
        cerr << "Error al abrir el archivo" << endl;
    }
    file.close();
}

Token* Scanner::next_token() {
    if (is_eof()) {
        return nullptr;
    }

    int estado = 0;
    string term = "";

    while (true) {
        char current_char = next_char();
        column++;

        if (estado == 0) {
            if (is_char(current_char)) {
                term += current_char;
                estado = 1;
            } else if (is_digit(current_char)) {
                estado = 2;
                term += current_char;
            } else if (is_space(current_char)) {
                estado = 0;
            } else if (is_operator(current_char)) {
                term += current_char;
                Token* token = new Token();
                token->set_type(Token::Tk_operator);
                token->set_text(term);
                token->set_line(line);
                token->set_column(column - term.length());
                return token;
            } else {
                cout << "Simbolo no reconocido" << endl;
                break;
            }
        } else if (estado == 1) {
            if (is_char(current_char) || is_digit(current_char)) {
                estado = 1;
                term += current_char;
            } else if (is_space(current_char) || is_operator(current_char) || is_eof_char(current_char)) {
                if (!is_eof_char(current_char)) {
                    back();
                }
                Token* token = new Token();
                token->set_type(Token::Tk_identifier);
                token->set_text(term);
                token->set_line(line);
                token->set_column(column - term.length());
                return token;
            } else {
                cout << "Identificador mal formado" << endl;
                break;
            }
        } else if (estado == 2) {
            if (is_digit(current_char) || current_char == '.') {
                estado = 2;
                term += current_char;
            } else if (!is_char(current_char) || is_eof_char(current_char)) {
                if (!is_eof_char(current_char)) {
                    back();
                }
                Token* token = new Token();
                token->set_type(Token::Tk_number);
                token->set_text(term);
                token->set_line(line);
                token->set_column(column - term.length());
                return token;
            } else {
                cout << "Numero no reconocido" << endl;
                break;
            }
        }
    }
}

bool Scanner::is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool Scanner::is_char(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool Scanner::is_operator(char c) {
    return c == '>' || c == '<' || c == '=' || c == '!' || c == '+' || c == '-' || c == '*' || c == '/';
}

bool Scanner::is_space(char c) {
    if (c == '\n' || c == '\r') {
        line++;
        column = 0;
    }
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

char Scanner::next_char() {
    if (is_eof()) {
        return '$';
    }
    pos++;
    return content[pos - 1];
}

bool Scanner::is_eof() {
    return pos >= content.size();
}

void Scanner::back() {
    pos--;
    column--;
}

bool Scanner::is_eof_char(char c) {
    return c == '\0';
}
