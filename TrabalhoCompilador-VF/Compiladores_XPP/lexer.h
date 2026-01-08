#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>

enum TokenType {
    // Palavras-chave
    TOKEN_CLASS,
    TOKEN_EXTENDS,
    TOKEN_INT,
    TOKEN_STRING,
    TOKEN_CONSTRUCTOR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_RETURN,
    TOKEN_PRINT,
    TOKEN_READ,
    TOKEN_SUPER,
    TOKEN_NEW,
    TOKEN_BREAK,
    TOKEN_NULL,

    // Identificadores e literais
    TOKEN_IDENT,
    TOKEN_INT_CONST,
    TOKEN_STRING_CONST,

    // Operadores
    TOKEN_OP,

    // Delimitadores
    TOKEN_DELIM,

    // Controle
    TOKEN_EOF,
    TOKEN_ERROR
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
private:
    std::ifstream file;
    char currentChar;
    int line;
    bool debug;

    void advance();
    void skipWhitespace();
    Token identifierOrKeyword();
    Token number();
    Token stringLiteral();
    Token operatorOrDelimiter();
    bool isKeyword(const std::string& lex, TokenType& type);

public:
    Lexer(const std::string& filename, bool isDebug);
    Token nextToken();
};

#endif
