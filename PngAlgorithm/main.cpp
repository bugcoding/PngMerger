#include "pngToolFuc.h"


int main(int argc, char *argv[])
{
    PngTools *pt = new PngTools();
    pt->setWillHandingPng("test.png");
    pt->getFileName();
    return 0;
}
