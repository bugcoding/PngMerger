#include "PngMergeTool.h"
#include "PngUtils.h"

int main(int argc, char *argv[])
{
    PngMergeTool *pmt = new PngMergeTool("./pngTest");

    if (pmt && pmt->getAndReadAllImage())
    {

        fprintf(stdout, "%s\n", "Load All Png To Memory Success");
        pmt->printVecInfo();
    }
    else
    {
        fprintf(stdout, "%s\n", "Load All Png To Memory Failed");
    }
    delete pmt;

    return 0;
}
