# X++ Compiler – LL(1) Lexical and Syntactic Analyzer

## 📚 Description
This project consists of the implementation of an **LL(1) lexical and syntactic analyzer** for the **X++ language**, developed as a **practical assignment for the Compilers course**.

The lexical analyzer reads the source code and recognizes the language tokens, while the syntactic analyzer verifies whether the token sequence conforms to the defined **LL(1) grammar**, identifying syntactic errors when present.

---

## 🛠️ Technologies Used
- **Language:** C++
- **Compiler:** g++
- **Standard:** C++14 or higher
- **Operating System:** Windows / Linux

---

## 📂 Project Structure

compilador-xpp/
│
├── src/
│ ├── lexer.cpp
│ ├── parser.cpp
│ └── main.cpp
│
├── include/
│ ├── lexer.h
│ └── parser.h
│
├── tests/
│ ├── programa_valido.xpp
│ └── programa_invalido.xpp
│
├── Makefile
├── README.md


---

## ⚙️ Features
- Lexical analysis with token recognition
- Line tracking for error messages
- Predictive LL(1) syntactic analyzer
- Use of a parsing table
- Detection and handling of lexical and syntactic errors
- Command-line execution

---

## ▶️ How to Compile
In the project root directory, run:

``bash
make

Or alternatively:

g++ -std=c++14 src/*.cpp -Iinclude -o compilador_xpp

▶️ How to Run

After compilation:

./compilador_xpp file.xpp

Example:

./compilador_xpp tests/programa_valido.xpp

📄 X++ Code Example

class Main {
    int x;
    x = 10;
}

❌ Error Example

Syntax error at line 5: unexpected token '}'.

🎯 Assignment Objectives

    Apply lexical analysis concepts

    Implement an LL(1) syntactic analyzer

    Work with context-free grammars

    Develop proper error handling

    Integrate the analysis stages of a compiler

👨‍🎓 Authors

Gustavo Alves Silva / Gustavo Silveira Dias
Course: Computer Engineering
Institution: IFMG – Campus Bambuí
