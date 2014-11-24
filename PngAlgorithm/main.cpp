#include "pngToolFuc.h"


int main(int argc, char *argv[])
{
    PngTools *pt = new PngTools("test.png");
    pt->getFileName();
    if (pt->readPngInfo())
    {
        PngInfo *tmp = pt->readPngInfo();
        pt->getPngBoundary(*(tmp->pixelData), tmp->width, tmp->height);
        pt->handlePng();
        pt->writePngData2File("test_gray.png");
    }
    else
    {
        std::cout << "read png file error!" << std::endl;
    }
    return 0;
}
