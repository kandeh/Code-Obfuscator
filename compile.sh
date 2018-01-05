bison -v -yd bis.y
flex lex.l
g++ -c lex.yy.c
g++ -c y.tab.c
g++ -o Obfuscator -std=c++11 main.cpp ast.cpp code_generator.cpp obfuscator.cpp y.tab.o lex.yy.o
