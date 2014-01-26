#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>

#include <unistd.h>
#include <fcntl.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

#include "JpegEncoder.h"
#include "jpeglib.h"

JpegEncoder::JpegEncoder(int width, int height, int quality):
    m_uWidth(width), m_uHeight(height), m_uQuality(quality)
{
}

JpegEncoder::~JpegEncoder()
{
}


bool JpegEncoder::encode(unsigned char* pInBuf, unsigned char* pOutBuf, unsigned long* pOutSize) const
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_mem_dest(&cinfo, &pOutBuf,pOutSize);
    cinfo.image_width = m_uWidth;
    cinfo.image_height = m_uHeight;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;


    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo,m_uQuality,TRUE);
    jpeg_start_compress(&cinfo,TRUE);

    JSAMPROW row_pointer[1];//pointer to scanline
    unsigned char* pBuf = (unsigned char*) malloc(3*m_uWidth);
    row_pointer[0] = pBuf;
    int lineSize = m_uWidth * 4;

  	while(cinfo.next_scanline < m_uHeight)
    {
		reOrder(pInBuf + cinfo.next_scanline * lineSize, pBuf, m_uWidth);
    	jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    free(pBuf);
    pBuf   = NULL;
    return true;
}

void  JpegEncoder::reOrder(unsigned char* pInBuf, unsigned char* pOutBuf, int width) const
{
	register int i=0;
	register unsigned char* pIn = pInBuf;
	register unsigned char* pOut = pOutBuf;
	register int count = width;
	for(i=0; i<count; i++)
	{
		*pOut++ = *(pIn+i*4+2);
		*pOut++ = *(pIn+i*4+1);
		*pOut++ = *(pIn+i*4);
	}

}
