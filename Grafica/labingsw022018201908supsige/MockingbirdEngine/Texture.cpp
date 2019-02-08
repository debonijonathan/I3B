//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include "GL/freeglut.h"
#include <FreeImage.h>

#include <iostream>

/////////////
// #DEFINE //
/////////////

#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB_ARB                0x8571
#define GL_RGB_SCALE_ARB                  0x8573

Texture::Texture(){
	FreeImage_Initialise(FALSE);
}


Texture::~Texture(){
}

/////////////////////////
// loadTextureFromFile //
/////////////////////////

/**
 * this method allows to load the texture with freeimage library
 * @param the location of the file .OVO
 * @return the current texture
 */
Texture* Texture::loadTextureFromFile(const char* filepath){
    FIBITMAP* fibitmap = FreeImage_Load(FreeImage_GetFileType(filepath, 0),filepath, 0);
    width = FreeImage_GetWidth(FreeImage_ConvertTo32Bits(fibitmap));
    height = FreeImage_GetHeight(FreeImage_ConvertTo32Bits(fibitmap));
    texture = FreeImage_GetBits(FreeImage_ConvertTo32Bits(fibitmap));

    FreeImage_Unload(fibitmap);
    return this;
}

//////////////
// getWidth //
//////////////

/**
 * this method allows to get the width
 * @param empty
 * @return the width value
 */
unsigned int Texture::getWidth(){
	return width;
}

///////////////
// getHeight //
///////////////

/**
 * this method allows to get the height
 * @param empty
 * @return the height value
 */
unsigned int Texture::getHeight(){
	return height;
}

//////////
// init //
//////////

/**
 * this method allows initialize the texture render
 * @param empty
 * @return the height value
 */
void Texture::init() {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width,
                 height,0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, texture);
}

////////////
// render //
////////////

/**
 * this method allows to render the Texture
 * @param camera information
 * @return void
 */
void Texture::render(void * data){
    // Create and bind texture:
    glEnable(GL_TEXTURE_2D);
    if(!initialized){
        initialized = true;
        init();
    }
    glBindTexture(GL_TEXTURE_2D, texId);
}
