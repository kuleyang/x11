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
#include "ScreenCapture.h"
#include "X11/XWDFile.h"

ScreenCapture::ScreenCapture():
    m_pBuffer(NULL), m_pCapBuf(NULL), m_iFBhd(0)
{
    
}

ScreenCapture::~ScreenCapture()
{
    
}

bool ScreenCapture::create(const char *fbPath)
{
    if(fbPath == NULL)
    {
        std::cout<<"fbpath empty!"<<std::endl;
        return false;
    }

    struct stat info;
    m_iFBhd = open(fbPath, O_RDONLY);
    if (m_iFBhd < 0)
    {
        std::cout<<"open fbpath occur error!"<<std::endl;
        return false;
    }

    if (fstat(m_iFBhd, &info) < 0)
    {
        std::cout<<"get file stat occur error!"<<std::endl;
        close(m_iFBhd);
        return false;
    }

    m_lFBSize = info.st_size;
    m_pBuffer = (char *) mmap(NULL, m_lFBSize, PROT_READ, MAP_PRIVATE, m_iFBhd,0);
    m_pCapBuf = new char[m_lFBSize + 1];

    return true;
}

void ScreenCapture::destroy()
{
    close(m_iFBhd);
    munmap(m_pBuffer,m_lFBSize);	
    m_pBuffer = NULL;
    m_iFBhd = -1;
    m_lFBSize = 0;
    if (NULL != m_pCapBuf)
    {
        delete[] m_pCapBuf;
        m_pCapBuf = NULL;
    }
    
    return;
}

bool ScreenCapture::capture(SCREEN_IMAGE & img)
{
    memcpy(m_pCapBuf, m_pBuffer, m_lFBSize);
    this->parse(m_pCapBuf, &img.pData, img.width, img.height, img.bytesPerLine);
    return true;
}

bool ScreenCapture::parse(char* pXwdBuf, char** pImageData, long& width, long& height, long& bytePerLine)
{
    XWDFileHeader* pHeader = new XWDFileHeader();
    memcpy(pHeader, pXwdBuf, sizeof(XWDFileHeader));

    swapLong((char*)(&(pHeader->header_size)));
	swapLong((char*)(&(pHeader->pixmap_width)));
	swapLong((char*)(&(pHeader->pixmap_height)));
	swapLong((char*)(&(pHeader->bytes_per_line)));
	swapLong((char*)(&(pHeader->ncolors)));

	*pImageData = pXwdBuf+pHeader->header_size+sizeof(XWDColor)*pHeader->ncolors;
	//printf("cap:pHeaderSize=%ld colormapSize=%d orgbuf=%p \n",pHeader.pHeader_size,sizeof(XWDColor),pXwdBuf);

	width = pHeader->pixmap_width;
	height = pHeader->pixmap_height;
	bytePerLine = pHeader->bytes_per_line;
	delete pHeader;
	pHeader = NULL;    
    
    return true;
}

void ScreenCapture::swapLong(char * bp) const
{
    register char c;
    c = bp[3];
    bp[3] = bp[0];
    bp[0] = c;
    c = bp[2];
    bp[2] = bp[1];
    bp[1] = c;

    return;
}
    
