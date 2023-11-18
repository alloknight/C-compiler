# C-compiler from scratch using GNU bison and flex
  A compiler to a very small subset of C to x86 32-bit ASM.
## compile
  $ bison -d parse.y <br />
  $ flex lex.l <br />
  $ g++ -o compile parse.tab.c lex.yy.c node.cpp main.cpp
## run
  $ ./compile < proc.c
