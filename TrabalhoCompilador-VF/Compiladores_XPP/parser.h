#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <fstream>
#include <string>

class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    std::ofstream log;

    // utilitários
    void advance();
    void match(TokenType type, const std::string& msg);
    void error(const std::string& msg);

    // gramática
    void program();
    void classList();
    void classDecl();
    void classBody();

    void varDecl();
    void methodDecl();
    void paramList();

    void statement();
    void statementList();

    void atribStat();
    void printStat();
    void readStat();
    void returnStat();
    void ifStat();
    void forStat();

    void expression();
    void numExpr();
    void term();
    void factor();

public:
    Parser(Lexer& lex);
    void parse();
};

#endif
