# Trabalho de Compiladores
    -Gustavo Alves Silva
    -Gustavo Silveira Dias
    -IFMG - Campus Bambuí, 2026

## 1. Visão Geral
Este projeto implementa um compilador parcial para a linguagem X++, desenvolvido para a disciplina Compiladores. O sistema contempla as etapas de Análise Léxica e Análise Sintática,
realizando a verificação estrutural de programas escritos em X++.

O compilador recebe como entrada um arquivo-fonte no formato `.xpp` e gera arquivos de log contendo os tokens reconhecidos e possíveis erros léxicos ou sintáticos.

---

## 2. Estrutura do Projeto
A estrutura real do projeto no ambiente Windows é apresentada a seguir:

Trabalho-Compiladores/
├── Compiladores_XPP/
│   ├── bin/
│   │   └── Debug/
│   │       └── Compiladores_XPP.exe
│   ├── logs/
│   │   ├── tokens.txt
│   │   └── sintatico.txt
│   ├── obj/
│   │   └── Debug/
│   │       ├── lexer.o
│   │       ├── main.o
│   │       └── parser.o
│   ├── lexer.cpp
│   ├── lexer.h
│   ├── parser.cpp
│   ├── parser.h
│   ├── main.cpp
│   └── Compiladores_XPP.cbp
│
├── testes/
│   ├── teste_ok.xpp
│   ├── teste_ok2.xpp
│   ├── teste_ok3.xpp
│   ├── teste_erro_lexico.xpp
│   ├── teste_erro_lexico2.xpp
│   ├── teste_erro_sintatico_1.xpp
│   └── teste_erro_sintatico_2.xpp
│
└── README.md

---

## 3. Requisitos
    - Sistema Operacional: Windows
    - IDE: Code::Blocks
    - Compilador: MinGW (g++)
    - Padrão da linguagem: C++14

---

## 4. Como Compilar
A compilação é realizada diretamente pelo Code::Blocks.

Passos:
    1. Abrir o arquivo `Compiladores_XPP.cbp` no Code::Blocks
    2. Selecionar o perfil **Debug**
    3. Clicar em **Build** ou **Build and Run**
O executável será gerado automaticamente em:
    Compiladores_XPP/bin/Debug/Compiladores_XPP.exe

---

## 5. Como Executar
A execução pode ser feita via terminal (Prompt de Comando ou PowerShell).
Exemplo:
    -Compiladores_XPP/bin/Debug/Compiladores_XPP.exe testes/teste_ok.xpp
Após a execução, os arquivos de log são gerados na pasta:
    -Compiladores_XPP/logs/

Outra forma seria apenas modificar o caminho do caso de teste (está na main), ex:
    Arquivo original: std::string filename = "../testes/teste_erro_sintatico_1.xpp";
    Mude o --> "../testes/teste_erro_sintatico_1.xpp"; <-- Para, por exemplo: "../testes/teste_erro_sintatico_2.xpp";

---

## 6. Analisador Léxico
O anlisador léxico é responsável por ler o código-fonte caractere por caractere e transformá-lo em uma sequência de tokens válidos, de acordo com as regras da linguagem X++.
Arquivos relacionados:
    - lexer.h
    - lexer.cpp

### Estruturas Principais
enum TokenType
Define todos os tipos de tokens da linguagem, como identificadores, números, palavras-chave, operadores e símbolos.

struct Token
Representa um token reconhecido pelo analisador léxico, contendo o tipo do token, o lexema e a linha onde foi encontrado.

### Classe Lexer
Lexer(const std::string& filename)
Entrada: caminho do arquivo `.xpp`
Função: abre o arquivo de entrada e inicializa o processo de análise léxica.

Token getNextToken()
Saída: Token
Função: retorna o próximo token reconhecido no código-fonte.

void advance()
Função: avança a leitura para o próximo caractere do arquivo.

void skipWhitespace()
Função: ignora espaços em branco, tabulações e quebras de linha, atualizando a contagem de linhas.

Token identifierOrKeyword()
Função: identifica se uma sequência de caracteres corresponde a um identificador ou a uma palavra-chave reservada.

Token number()
Função: reconhece constantes numéricas inteiras.

---

## 7. Analisador Sintático
O analisador sintático verifica se a sequência de tokens gerada pelo analisador léxico está de acordo com a gramática da linguagem X++.

Arquivos relacionados:
    - parser.h
    - parser.cpp

### Classe Parser
Parser(Lexer& lexer)
Entrada: referência para um objeto Lexer
Função: inicializa o analisador sintático e obtém o primeiro token.

void parseProgram()
Função: inicia a análise sintática do programa X++.

void eat(TokenType type)
Entrada: tipo esperado de token
Função: consome o token atual caso esteja correto; caso contrário, registra erro sintático.

void error(const std::string& message)
Função: registra mensagens de erro sintático, informando a linha do erro.

Métodos auxiliares
Função: implementam as regras da gramática da linguagem, como declarações, comandos condicionais e estruturas de repetição.

---

## 8. Arquivo main.cpp
O arquivo main.cpp é responsável por coordenar o funcionamento do compilador. Ele valida os argumentos de entrada, cria o analisador léxico,
inicializa o analisador sintático e inicia o processo de análise.

---

## 9. Logs Gerados
Os arquivos de log são armazenados no diretório:

Compiladores_XPP/logs/
    - tokens.txt: lista de tokens reconhecidos durante a análise léxica
    - sintatico.txt: mensagens e erros gerados pela análise sintática

---

## 10. Considerações Finais
O projeto implementa de forma modular os conceitos fundamentais da disciplina de Compiladores, permitindo a análise léxica e sintática da linguagem X++.
A organização do código facilita futuras extensões, como análise semântica e geração de código intermediário.
