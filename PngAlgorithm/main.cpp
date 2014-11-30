#include "PngMergeTool.h"
#include "PngUtils.h"

int main(int argc, char *argv[])
{
    PngMergeTool *pmt = new PngMergeTool("pngTest");

    if (pmt && pmt->getAndReadAllImage())
    {
        show_msg("%s","Load All Png Data To Memory");
        pmt->printVecInfo();
        pmt->mergeImages();

        pmt->splitSinglePngFromMergedImage("pngTest.png");

    }
    else
    {
    }
    delete pmt;

    return 0;
}
