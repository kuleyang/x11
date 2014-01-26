#include <iostream>
#include <fstream>
#include <string>
#include "ScreenCapture.h"
#include "JpegEncoder.h"

using namespace std;

const int VIDEO_QUALITY = 80;


int main(int argc, char *argv[])
{
    
    std::string fb_path = "/home/luckyan315/Xvfb_screen0";
    std::string jpg_out_path = "./out.jpg";
    
    SCREEN_IMAGE image;
    
    ScreenCapture* pSc = new ScreenCapture();
    pSc->create(fb_path.c_str());
    pSc->capture(image);

    std::cout<<" width: "<<image.width<<" height: "<<image.height<<" bytesPerline: "<<image.bytesPerLine<<std::endl;

    JpegEncoder* pJpeg = new JpegEncoder(image.width, image.height, VIDEO_QUALITY);

    std::ofstream ofs;
    PIMAGE_ITEM pOut = new IMAGE_ITEM();
    pOut->count = -1;
    pOut->mod = -1;
    pOut->frameIndex = -1;
    pOut->endflag = -1;
    pOut->pOutBuf = new unsigned char[IMAGE_BUFFER_SIZE + 1];
    
    ofs.open(jpg_out_path.c_str(), std::ofstream::out | std::ofstream::app);
    
    pJpeg->encode((unsigned char*) image.pData, pOut->pOutBuf, &pOut->lOutSize);
    
    pOut->frameIndex = 0;
    pOut->count = pOut->lOutSize / GRAPHIC_SIZE;
    pOut->mod =  pOut->lOutSize % GRAPHIC_SIZE;

    std::cout<<"Out Size: "<<pOut->lOutSize<<std::endl;
    // std::cout<<"Fb Size: "<<pSc->getFBSize()<<std::endl;

    ofs.write((const char *)pOut->lOutSize, pOut->lOutSize);
    
    ofs.close();

    
    delete pSc;
    delete [] pOut->pOutBuf;
    delete pOut;
    delete pJpeg;

    return 0;
}
