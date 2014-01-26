#ifndef _JPEGENCODER_H_
#define _JPEGENCODER_H_

class JpegEncoder
{
public:
    JpegEncoder(int width, int height, int quality);
    virtual ~JpegEncoder();

public:
    bool encode(unsigned char* pInBuf, unsigned char* pOutBuf, unsigned long* pOutSize) const;
    void reOrder(unsigned char* pInBuf,unsigned char* pOutBuf,int width) const;
    
private:
    unsigned int m_uWidth;
    unsigned int m_uHeight;
    unsigned int m_uQuality;
    
};

#endif /* _JPEGENCODER_H_ */
