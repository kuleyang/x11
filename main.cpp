#include <iostream>
#include <string>
#include "ScreenCapture.h"

using namespace std;

int main(int argc, char *argv[])
{
    
    std::string fb_path = "/home/luckyan315/Xvfb_screen0";
    SCREEN_IMAGE image;
    
    ScreenCapture* pSc = new ScreenCapture();
    pSc->create(fb_path.c_str());
    pSc->capture(image);

    std::cout<<" width: "<<image.width<<" height: "<<image.height<<" bytesPerline: "<<image.bytesPerLine<<std::endl;
    
    // std::cout<<"Fb Size: "<<pSc->getFBSize()<<std::endl;

    
    
    return 0;
}
