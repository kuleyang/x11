#ifndef _SCREENCAPTURE_H_
#define _SCREENCAPTURE_H_

const float X_OPEN_INTERVALTIME = 0.1;
const int IMAGE_BUFFER_SIZE = 1024 * 500;
const int GRAPHIC_SIZE = 40 * 1024;

typedef struct _image_item {
   unsigned char *pOutBuf;
   unsigned long lOutSize;
   int count ;
   int mod;
   int frameIndex;
   int endflag;
   
}IMAGE_ITEM, *PIMAGE_ITEM;


typedef struct _screen_image {
  long width;
  long height;
  long bytesPerLine;
  char *pData;
}SCREEN_IMAGE, *PSCREEN_IMAGE;

class ScreenCapture
{
public:
    ScreenCapture();
    ~ScreenCapture();

public:
    bool create(const char *fbPath);
    void destroy();
    bool capture(SCREEN_IMAGE & img);

public:
    bool parse(char* pXwdBuf, char** pImageData, long& width, long& height, long& bytePerLine);
    void swapLong(char * bp) const;

private:
    char *m_pBuffer;
    char *m_pCapBuf;

    int m_iFBhd;
    long m_lFBSize;

//just for test    
public:
    long getFBSize() const { return m_lFBSize; }
}; 

#endif /* _SCREENCAPTURE_H_ */
