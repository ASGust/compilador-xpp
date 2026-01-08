#include "lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& filename, bool isDebug) {
    file.open(filename);
    debug = isDebug;

    if (!file.is_open()) {
        if (debug) {
            std::cerr << "[DEBUG] ERRO: nao foi possivel abrir o arquivo "
                      << filename << std::endl;
        }
        return;
    }

    line = 1;

    if (debug) {
        std::cout << "[DEBUG] Conteudo do arquivo lido pelo lexer:\n";
        std::cout << "-------------------------------------------\n";
    }

    std::streampos pos = file.tellg();

    char c;
    while (file.get(c)) {
        if (!debug) continue;

        if (c == '\n')
            std::cout << "\\n\n";
        else if (c == '\t')
            std::cout << "\\t";
        else
            std::cout << c;
    }

    if (debug) {
        std::cout << "\n-------------------------------------------\n";
        std::cout << "[DEBUG] Fim do conteudo do arquivo\n";
    }

    file.clear();
    file.seekg(pos);

    currentChar = file.get();
}

void Lexer::advance() {
    if (currentChar == '\n') {
        line++;
        if (debug) {
            std::cout << "[DEBUG] Nova linha detectada. line = "
                      << line << std::endl;
        }
    }

    currentChar = file.get();

    if (debug) {
        std::cout << "[DEBUG] advance(): currentChar = '";

        if (currentChar == '\n')
            std::cout << "\\n";
        else if (currentChar == '\t')
            std::cout << "\\t";
        else if (currentChar == EOF)
            std::cout << "EOF";
        else
            std::cout << currentChar;

        std::cout << "' (ASCII " << int(currentChar) << ")\n";
    }
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar)) {
        advance();
    }
}

bool Lexer::isKeyword(const std::string& lex, TokenType& type) {
    if (lex == "class")       { type = TOKEN_CLASS; return true; }
    if (lex == "extends")     { type = TOKEN_EXTENDS; return true; }
    if (lex == "int")         { type = TOKEN_INT; return true; }
    if (lex == "string")      { type = TOKEN_STRING; return true; }
    if (lex == "constructor") { type = TOKEN_CONSTRUCTOR; return true; }
    if (lex == "if")          { type = TOKEN_IF; return true; }
    if (lex == "else")        { type = TOKEN_ELSE; return true; }
    if (lex == "for")         { type = TOKEN_FOR; return true; }
    if (lex == "return")      { type = TOKEN_RETURN; return true; }
    if (lex == "print")       { type = TOKEN_PRINT; return true; }
    if (lex == "read")        { type = TOKEN_READ; return true; }
    if (lex == "super")       { type = TOKEN_SUPER; return true; }
    if (lex == "new")         { type = TOKEN_NEW; return true; }
    if (lex == "break")       { type = TOKEN_BREAK; return true; }
    if (lex == "null")        { type = TOKEN_NULL; return true; }
    return false;
}

Token Lexer::identifierOrKeyword() {
    std::string lex;
    while (isalnum(currentChar) || currentChar == '_') {
        lex += currentChar;
        advance();
    }

    TokenType type;
    if (isKeyword(lex, type))
        return {type, lex, line};

    return {TOKEN_IDENT, lex, line};
}

Token Lexer::number() {
    std::string num;
    while (isdigit(currentChar)) {
        num += currentChar;
        advance();
    }
    return {TOKEN_INT_CONST, num, line};
}

Token Lexer::stringLiteral() {
    std::string str;
    advance();

    while (currentChar != '"' && !file.eof()) {
        str += currentChar;
        advance();
    }

    if (currentChar == '"') {
        advance();
        return {TOKEN_STRING_CONST, str, line};
    }

    return {TOKEN_ERROR, str, line};
}

Token Lexer::operatorOrDelimiter() {
    std::string lex;
    lex += currentChar;
    char first = currentChar;
    advance();

    if ((first == '=' || first == '!' ||
         first == '<' || first == '>') && currentChar == '=') {

        if (debug) {
            std::cout << "[DEBUG] Operador composto detectado: '"
                      << first << currentChar << "'\n";
        }

        lex += currentChar;
        advance();
        return {TOKEN_OP, lex, line};
    }

    if (std::string("+-*/%=").find(first) != std::string::npos) {
        if (debug) {
            std::cout << "[DEBUG] Operador simples detectado: '"
                      << first << "'\n";
        }
        return {TOKEN_OP, lex, line};
    }

    if (std::string("(){}[];,.").find(first) != std::string::npos) {
        if (debug) {
            std::cout << "[DEBUG] Delimitador detectado: '"
                      << first << "'\n";
        }
        return {TOKEN_DELIM, lex, line};
    }

    return {TOKEN_ERROR, lex, line};
}

Token Lexer::nextToken() {
    skipWhitespace();

    if (file.eof()) {
        if (debug) {
            std::cout << "[DEBUG] EOF atingido. Linha: " << line << std::endl;
        }
        return {TOKEN_EOF, "", line};
    }

    if (isalpha(currentChar) || currentChar == '_') {
        if (debug) {
            std::cout << "[DEBUG] Identificador ou palavra-chave. currentChar = '"
                      << currentChar << "'\n";
        }
        return identifierOrKeyword();
    }

    if (isdigit(currentChar)) {
        if (debug) {
            std::cout << "[DEBUG] Número detectado. currentChar = '"
                      << currentChar << "'\n";
        }
        return number();
    }

    if (currentChar == '"') {
        if (debug) {
            std::cout << "[DEBUG] String literal detectada.\n";
        }
        return stringLiteral();
    }

    return operatorOrDelimiter();
}
