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
CPPFLAG = -Wall -I ./MaxRectsAlgorithim/  -I ./TinyXml2
CPPLINKFLAG = -lfreeimage
#for MaxRectsAlgorithm
DIR_ALGO_LIB = ./MaxRectsAlgorithim
#for tinyxml parse
DIR_TINYXML_LIB = ./TinyXml2

OBJ = main.o PngUtils.o PngMergeTool.o $(DIR_ALGO_LIB)/MaxRectsBinPack.o \
	  $(DIR_ALGO_LIB)/Rect.o PlistConfig.o $(DIR_TINYXML_LIB)/tinyxml2.o

PngMergeTool: $(OBJ)
	$(CC) $(CPPFLAG) -o $@ $(OBJ) $(CPPLINKFLAG) 	

main.o: main.cpp
	$(CC) $(CPPFLAG) -c main.cpp

PngUtils.o: PngUtils.cpp PngUtils.h
	$(CC) $(CPPFLAG) -c PngUtils.cpp

PngMergeTool.o: PngMergeTool.cpp PngMergeTool.h
	$(CC) $(CPPFLAG) -c PngMergeTool.cpp

PlistConfig.o: PlistConfig.cpp PlistConfig.h
	$(CC) $(CPPFLAG) -c PlistConfig.cpp

tinyxml2.o: $(DIR_TINYXML_LIB)/tinyxml2.cpp $(DIR_TINYXML_LIB)/tinyxml2.h
	$(CC) $(CPPFLAG) -c $(DIR_TINYXML_LIB)/tinyxml2.cpp



.PHONY: clean
clean:
	del $(OBJ) PngMergeTool.exe
