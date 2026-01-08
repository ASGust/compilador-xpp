# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++14

# Nome do executável
TARGET = Compiladores_XPP

# Arquivos fonte
SRCS = main.cpp lexer.cpp parser.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilação dos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Limpeza completa (opcional)
distclean: clean
	rm -f logs/*.log

