#include "parser.h"
#include <iostream>

Parser::Parser(Lexer& lex) : lexer(lex) {
    currentToken = lexer.nextToken();
    log.open("logs/sintatico.log");
}

void Parser::advance() {
    currentToken = lexer.nextToken();
}

void Parser::error(const std::string& msg) {
    log << "Erro sintático na linha "
        << currentToken.line << ": " << msg
        << " (encontrado '" << currentToken.lexeme << "')\n";

    // recuperação simples: avança
    advance();
}

void Parser::match(TokenType type, const std::string& msg) {
    if (currentToken.type == type) {
        advance();
    } else {
        error(msg);
    }
}

void Parser::parse() {
    program();
    log << "Análise sintática finalizada.\n";
    log.close();
}

void Parser::program() {
    log << "<program>\n";
    classList();
}

void Parser::classList() {
    while (currentToken.type == TOKEN_CLASS) {
        classDecl();
    }
}

void Parser::classDecl() {
    log << "<classDecl>\n";
    match(TOKEN_CLASS, "esperado 'class'");
    match(TOKEN_IDENT, "esperado identificador da classe");
    classBody();
}

void Parser::classBody() {
    if (currentToken.lexeme != "{") {
        error("esperado '{'");
        return;
    }
    advance();

    while (currentToken.type == TOKEN_INT ||
           currentToken.type == TOKEN_STRING ||
           currentToken.type == TOKEN_IDENT) {

        Token lookahead = currentToken;
        advance();

        if (currentToken.lexeme == "(") {
            // método
            currentToken = lookahead;
            methodDecl();
        } else {
            // variável
            currentToken = lookahead;
            varDecl();
        }
    }

    if (currentToken.lexeme != "}") {
        error("esperado '}'");
        return;
    }
    advance();
}

void Parser::varDecl() {
    log << "<varDecl>\n";
    advance(); // tipo
    match(TOKEN_IDENT, "esperado identificador");
    match(TOKEN_DELIM, "esperado ';'");
}

void Parser::methodDecl() {
    log << "<methodDecl>\n";
    advance(); // tipo
    match(TOKEN_IDENT, "esperado nome do método");

    if (currentToken.lexeme != "(") {
        error("esperado '('");
        return;
    }
    advance();

    paramList();

    if (currentToken.lexeme != ")") {
        error("esperado ')'");
        return;
    }
    advance();

    statement();
}

void Parser::paramList() {
    if (currentToken.type == TOKEN_INT ||
        currentToken.type == TOKEN_STRING ||
        currentToken.type == TOKEN_IDENT) {

        advance();
        match(TOKEN_IDENT, "esperado identificador");

        while (currentToken.lexeme == ",") {
            advance();
            advance();
            match(TOKEN_IDENT, "esperado identificador");
        }
    }
}

void Parser::statement() {
    log << "<statement>\n";

    if (currentToken.lexeme == "{") {
        advance();
        statementList();
        match(TOKEN_DELIM, "esperado '}'");
        match(TOKEN_DELIM, "esperado ';'");
    }
    else if (currentToken.type == TOKEN_IDENT) {
        atribStat();
        match(TOKEN_DELIM, "esperado ';'");
    }
    else if (currentToken.lexeme == "print") {
        printStat();
        match(TOKEN_DELIM, "esperado ';'");
    }
    else if (currentToken.lexeme == "read") {
        readStat();
        match(TOKEN_DELIM, "esperado ';'");
    }
    else if (currentToken.lexeme == "return") {
        returnStat();
        match(TOKEN_DELIM, "esperado ';'");
    }
    else if (currentToken.lexeme == "if") {
        ifStat();
    }
    else if (currentToken.lexeme == "for") {
        forStat();
    }
    else if (currentToken.lexeme == ";") {
        advance();
    }
    else {
        error("comando inválido");
    }
}

void Parser::statementList() {
    while (currentToken.lexeme != "}") {
        statement();
    }
}

void Parser::atribStat() {
    log << "<atribStat>\n";
    advance(); // ident

    if (currentToken.lexeme != "=") {
        error("esperado '='");
        return;
    }
    advance();
    expression();
}

void Parser::printStat() {
    advance(); // print
    expression();
}

void Parser::readStat() {
    advance(); // read
    match(TOKEN_IDENT, "esperado identificador");
}

void Parser::returnStat() {
    advance(); // return
    expression();
}

void Parser::ifStat() {
    advance(); // if
    match(TOKEN_DELIM, "esperado '('");
    expression();
    match(TOKEN_DELIM, "esperado ')'");
    statement();

    if (currentToken.lexeme == "else") {
        advance();
        statement();
    }
}

void Parser::forStat() {
    advance(); // for
    match(TOKEN_DELIM, "esperado '('");

    if (currentToken.type == TOKEN_IDENT)
        atribStat();

    match(TOKEN_DELIM, "esperado ';'");
    expression();
    match(TOKEN_DELIM, "esperado ';'");

    if (currentToken.type == TOKEN_IDENT)
        atribStat();

    match(TOKEN_DELIM, "esperado ')'");
    statement();
}

void Parser::expression() {
    numExpr();
}

void Parser::numExpr() {
    term();
    while (currentToken.lexeme == "+" || currentToken.lexeme == "-") {
        advance();
        term();
    }
}

void Parser::term() {
    factor();
    while (currentToken.lexeme == "*" ||
           currentToken.lexeme == "/" ||
           currentToken.lexeme == "%") {
        advance();
        factor();
    }
}

void Parser::factor() {
    if (currentToken.type == TOKEN_INT_CONST ||
        currentToken.type == TOKEN_STRING_CONST ||
        currentToken.type == TOKEN_IDENT) {
        advance();
    }
    else if (currentToken.lexeme == "(") {
        advance();
        expression();
        match(TOKEN_DELIM, "esperado ')'");
    }
    else {
        error("fator inválido");
    }
}
