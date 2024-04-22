
import codecs
from token_comp import Token

class Scanner:
    def __init__(self, filename):
        self.line = 1
        self.column = 0
        try:
            with codecs.open(filename, 'r', encoding='utf-8') as file:
                txt_content = file.read()
            self.content = list(txt_content)
            self.pos = 0
        except Exception as ex:
            print(ex)


    def next_token(self):
        if self.is_eof():
            return None
        
        estado = 0
        term = ""

        while True:
            current_char = self.next_char()
            self.column += 1

            if estado == 0:
                if self.is_char(current_char):
                    term += current_char
                    estado = 1
                elif self.is_digit(current_char):
                    estado = 2
                    term += current_char
                elif self.is_space(current_char):
                    estado = 0
                elif self.is_operator(current_char):
                    term += current_char
                    token = Token()
                    token.set_type(token.TK_OPERATOR)
                    token.set_text(term)
                    token.set_line(self.line)
                    token.set_column(self.column - len(term))
                    return token
                else: 
                    print("SIMBOLO NO RECONOCIDO")
                    break

            elif estado == 1:
                if self.is_char(current_char) or self.is_digit(current_char):
                    estado = 1
                    term += current_char # concatenación del termino. 
                elif self.is_space(current_char) or self.is_operator(current_char) or self.is_eof_char(current_char):
                    if not self.is_eof_char(current_char):
                        self.back()
                    token = Token()
                    token.set_type(Token.TK_IDENTIFIER)
                    token.set_text(term)
                    token.set_line(self.line)
                    token.set_column(self.column - len(term))
                    return token
                else:
                    print("IDENTIFICADOR MAL FORMADO")
                    break

            elif estado == 2:
                if self.is_digit(current_char) or current_char == '.':
                    estado = 2
                    term += current_char # concatenación que es igual a decir term = term + current_char
                elif not self.is_char(current_char) or self.is_eof_char(current_char):
                    if not self.is_eof_char(current_char):
                        self.back()
                    token = Token()
                    token.set_type(Token.TK_NUMBER)
                    token.set_text(term)
                    token.set_line(self.line)
                    token.set_column(self.column - len(term))
                    return token
                else:
                    print("NÚMERO NO RECONOCIDO")
                    break

    # a?c + 123 * 456 / 12.0 
    # "abc 6" -> 'a', 'b', 'c', ' ', '6'

    def is_digit(self, c):
        return '0' <= c <= '9'

    def is_char(self, c):
        return 'a' <= c <= 'z' or 'A' <= c <= 'Z'
    
    def is_operator(self, c):
        return c in ['>', '<', '=', '!', '+', '-', '*', '/']
    
    def is_space(self, c):
        if c in ['\n', '\r']:
            self.line += 1
            self.column = 0
        return c in [' ', '\t', '\n', '\r']
    
    def next_char(self):
        if self.is_eof():
            return '$'
        self.pos = self.pos + 1
        return self.content[self.pos - 1]
    
    def is_eof(self): # es el final del archivo?
        return self.pos >= len(self.content)
    
    def back(self):
        self.pos -= 1
        self.column -= 1

    def is_eof_char(self, c):
        return c == '\0'