#=============================================================================
#     FileName: Makefile
#         Desc: test pngtool makefile
#       Author: bugcode
#        Email: bugcoding@gmail.com
#     HomePage: http://bugcode.com.cn
#      Version: 0.0.1
#   LastChange: 2014-09-04 12:43:05
#=============================================================================
CC = g++
CPPFALG = -Wall 
CPPLINKFLAG = -lpng -lz
OBJ = main.o pngToolFuc.o

pngTool: $(OBJ)
	$(CC) $(CPPFALG) -o $@ $(OBJ) $(CPPLINKFLAG) 	

main.o: main.cpp
	$(CC) $(CPPFALG) -c main.cpp
pngToolFuc.o: pngToolFuc.cpp pngToolFuc.h
	$(CC) $(CPPFALG) -c pngToolFuc.cpp

.PHONY: clean
clean:
	del $(OBJ) pngTool.exe
