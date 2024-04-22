
class Token:
    TK_IDENTIFIER = 0
    TK_NUMBER = 1
    TK_OPERATOR = 2
    TK_PUNCTUATION = 3
    TK_ASSIGN = 4

    TK_TEXT = [
        "IDENTIFICADOR", "NÚMERO", "OPERADOR", "PUNTUACIÓN", "ASIGNACIÓN"
    ]

    def __init__(self, type=None, text=""):
        self.type = type
        self.text = text
        self.line = None
        self.column = None

    def set_type(self, type):
        self.type = type

    def get_type(self):
        return self.type

    def set_text(self, text):
        self.text = text

    def get_text(self):
        return self.text

    def set_line(self, line):
        self.line = line

    def get_line(self):
        return self.line

    def set_column(self, column):
        self.column = column

    def get_column(self):
        return self.column
    
    def to_string(self):
        type_text = Token.TK_TEXT[self.type] if self.type is not None else "None"
        return print(f"Token [type={type_text}, text={self.text}, line={self.line}, column={self.column}]")