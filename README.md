# C-compiler
  A compiler to a very small subset of C to x86 32-bit ASM.
# compile
  $ bison -d parse.y // -d flag that generates parse.tab.h
  $ flex lex.l 
  $ g++ -o compile parse.tab.c lex.yy.c node.cpp main.cpp
# run
  $ ./compile < proc.c
# to see return value 
  $ echo $?
