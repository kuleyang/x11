#ifndef _SCREENCAPTURE_H_
#define _SCREENCAPTURE_H_

const float     X_OPEN_INTERVALTIME = 0.1;

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
