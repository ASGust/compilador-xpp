#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0777)
#endif
#include <direct.h>

int main(int argc, char* argv[]) {
    std::string filename = "../testes/teste_erro_sintatico_1.xpp"; //<-- realize os teste aqui
    bool isDebug = true;
    Lexer lexer(filename, isDebug);
    std::ofstream lexLog("logs/tokens.log");

    Token token;

    char buffer[FILENAME_MAX];

    // _getcwd(buffer, tamanho) retorna o caminho atual
    if (_getcwd(buffer, FILENAME_MAX)) {
        std::cout << "Diretorio atual: " << buffer << std::endl;
    }

    MKDIR("logs");

    // ETAPA 1 – ANÁLISE LÉXICA
    if (!lexLog.is_open()) {
        std::cerr << "Erro ao criar logs/tokens.log\n";
        return -1;
    }

    do {
        token = lexer.nextToken();
        lexLog << "Linha " << token.line
               << " | Token: " << token.type
               << " | Lexema: " << token.lexeme
               << std::endl;
    } while (token.type != TOKEN_EOF);
    lexLog.close();

    std::cout << "Analise lexica concluida.\n";

    // ETAPA 2 – ANÁLISE SINTÁTICA
    Lexer lexerSintatico(filename, isDebug);
    Parser parser(lexerSintatico);

    parser.parse();

    std::cout << "Analise sintatica concluida.\n";
    std::cout << "Verifique os arquivos na pasta 'logs'.\n";

    return 0;
}
