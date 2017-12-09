#include "qmytexture.h"

QMyTexture::QMyTexture()
{

}
unsigned int QMyTexture::loadTexture(const char *fileName)
{
    unsigned int textureId   =   0;
    //1 获取图片格式
    FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);

    //2 加载图片
    FIBITMAP    *dib = FreeImage_Load(fifmt, fileName,0);

    int fmt = GL_RGB;
    //4 获取数据指针
    BYTE    *pixels =   (BYTE*)FreeImage_GetBits(dib);

    int     width   =   FreeImage_GetWidth(dib);
    int     height  =   FreeImage_GetHeight(dib);

    /**
         *注意：1、当启用alpha测试时，那么文理格式就是（GL_RGBA），
         *       需要把图像转化成32位图，同时改变（glTexImage2D）中相对应的参数
         *     2、可根据文理的文件格式进行判断，然后确定转化成24位图还是转换成32位图，也就是是否存在alpha值
         */

    if(fifmt == FIF_PNG)
    {
        dib =   FreeImage_ConvertTo32Bits(dib);
        fmt =   GL_RGBA;
        for (size_t i = 0 ;i < float(width * height * 4) ; i+=4 )
        {
            BYTE temp       =   pixels[i];
            pixels[i]       =   pixels[i + 2];
            pixels[i + 2]   =   temp;
        }
    }
    else
    {
        //3 转化为rgb 24色
        dib     =   FreeImage_ConvertTo24Bits(dib);
        for (size_t i = 0 ;i < float(width * height * 3) ; i+=3 )
        {
            BYTE temp       =   pixels[i];
            pixels[i]       =   pixels[i + 2];
            pixels[i + 2]   =   temp;
        }
    }
    /**
            *   产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
            */
    glGenTextures( 1, &textureId );

    /**
            *   使用这个纹理id,或者叫绑定(关联)
            */
    glBindTexture( GL_TEXTURE_2D, textureId );
    /**
            *   指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
            */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    /**
            *   将图片的rgb数据上传给opengl.
            */
    glTexImage2D(
                GL_TEXTURE_2D,      //! 指定是二维图片
                0,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
                fmt,                //! 纹理的使用的存储格式
                width,              //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
                height,             //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
                0,                  //! 是否存在边
                fmt,                //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
                GL_UNSIGNED_BYTE,   //! 数据是8bit数据
                pixels
                );
    /**
            *   释放内存
            */
    FreeImage_Unload(dib);
    _width = width;
    _height = height;

    return  textureId;
}

unsigned int QMyTexture::createTexture(int width, int height)
{
    //!函数功能：产生一个新的空白文理，这个文理产生时是黑色的
    unsigned int textureId;
    glGenTextures(1,&textureId);//!生成文理
    glBindTexture(GL_TEXTURE_2D,textureId);//绑定文理
    /**
         *以下函数（）说明：这是一个设置文理参数的函数，同时也是起到对文理的包装
         * 对文理的放大、缩小滤波起到多层文理的过度作用
         * 主要说明最后一个参数：
         * 当第二个参数是<GL_TEXTURE_MAG_FILTER>时，
         * 参数3：GL_LINEAR
         * 参数3：GL_NEAREST
         * 当第二个参数是<GL_TEXTURE_MIN_FILTER>时，
         * 参数3：GL_LINEAR
         * 参数3：GL_NEAREST
         * 参数3：GL_LINEAR_MIPMAP_LINEAR 针对多层文理可用
         * 参数3：GL_NEAREST_MIPMAP_LINEAR 针对多层文理可用
         * 参数3：GL_LINEAR_MIPMAP_NEAREST 针对多层文理可用
         * 参数3：GL_NEAREST_MIPMAP_NEAREST 针对多层文理可用
         */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);//设置文理的相关参数1、文理的放大滤波
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);//设置文理的相关参数2、文理的缩小滤波
    /**
         *针对文理的包装:
         * 参数2是<GL_TEXTURE_WRAP_S>时，表示水平文理，
         *       <GL_TEXTURE_WRAP_T>时，表示垂直文理
         * 参数3：GL_REPEAT        表示文理根据所给文理重复
         * 参数3：GL_CLAMP_TO_EDGE 表示文理根据所给文理的最后一个像素重复
         * 参数3：GL_REPEAT        表示文理根据所给文理镜像重复
         */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//设置文理的相关参数3、水平文理的重复格式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);//设置文理的相关参数4、垂直文理的重复格式
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    return textureId;
}

unsigned int QMyTexture::loadTextureMipmap(std::vector<QString> fName)
{
    //!函数实现功能：把多个文理尺寸放在同一个文理中，
    //!实现各种显示出来的效果（有文理分明的过度和渐变过度，主要是调整<glTexParameteri>函数中的最后一个参数来实现）????????????
    unsigned int textureId = 0;
    glGenTextures(1,&textureId);
    glBindTexture( GL_TEXTURE_2D, textureId );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int fileCount = fName.size();
    printf("file number:%d\n",fileCount);
    fflush(NULL);
    for(int j=0;j<fileCount;++j)
    {
        QString fileName = fName[j];
        FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName.toLatin1().data(), 0);

        //2 加载图片
        FIBITMAP    *dib = FreeImage_Load(fifmt,fileName.toLatin1().data(),0);

        //3 转化为rgb 24色
        dib     =   FreeImage_ConvertTo24Bits(dib);

        //4 获取数据指针
        BYTE    *pixels =   (BYTE*)FreeImage_GetBits(dib);

        int     width   =   FreeImage_GetWidth(dib);
        int     height  =   FreeImage_GetHeight(dib);

        for (size_t i = 0 ;i < width * height * 3 ; i+=3 )
        {
            BYTE temp       =   pixels[i];
            pixels[i]       =   pixels[i + 2];
            pixels[i + 2]   =   temp;
        }
        glTexImage2D(
                    GL_TEXTURE_2D,      //! 指定是二维图片
                    j,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
                    GL_RGB,             //! 纹理的使用的存储格式
                    width,              //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
                    height,             //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
                    0,                  //! 是否存在边
                    GL_RGB,             //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
                    GL_UNSIGNED_BYTE,   //! 数据是8bit数据
                    pixels
                    );
        /**
                *   释放内存
                */
        FreeImage_Unload(dib);
    }

    return textureId;
}
