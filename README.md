# C-compiler
  A compiler to a very small subset of C to x86 32-bit ASM.
# compile
  $ bison -d parse.y
  $ flex lex.l 
  $ g++ -o compile parse.tab.c lex.yy.c node.cpp main.cpp
# run
  $ ./compile < proc.c
