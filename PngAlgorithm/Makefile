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
CPPFLAG = -Wall 
CPPLINKFLAG = -lpng -lz
OBJ = main.o pngToolFuc.o MergePngTool.o

pngTool: $(OBJ)
	$(CC) $(CPPFALG) -o $@ $(OBJ) $(CPPLINKFLAG) 	

main.o: main.cpp
	$(CC) $(CPPFLAG) -c main.cpp
MergePngTool.o: MergePngTool.cpp MergePngTool.h
	$(CC) $(CPPFLAG) -c MergePngTool.cpp
pngToolFuc.o: pngToolFuc.cpp pngToolFuc.h
	$(CC) $(CPPFLAG) -c pngToolFuc.cpp

.PHONY: clean
clean:
	del $(OBJ) pngTool.exe
