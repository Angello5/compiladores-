#ifndef TOKEN_H
#define TOKEN_H 

#include <iostream>
#include <string>

using namespace std;


class Token{
    public:
            static const int Tk_identifier;
            static const int Tk_number;
            static const int Tk_operator;
            static const int Tk_punctuantion;
            static const int Tk_assign;

            static const string Tk_text[];

            Token(int type = -1, const string& text = "", int line =-1, int column = -1);

            void set_type(int type);
            int get_type() const; 
            void set_text(const string& text);
            const string& get_text() const;
            void set_line(int line);
            int get_line() const;
            void set_column(int column);
            int get_column() const; 
            void to_string() const;


    private: 
            int type;
            string text;
            int line;
            int column;

};
#endif 