#pragma once

#include "LibApi.h"
class LIB_API Texture : public Object{
    public:
        Texture();
        virtual ~Texture();

        Texture* loadTextureFromFile(const char* filepath);

		unsigned int getWidth();
		unsigned int getHeight();
        void render(void * data = nullptr);
    private:
        void* texture = nullptr;
        void init();
        unsigned int texId = 0;
        unsigned int width = 0;
        unsigned int height = 0;
        bool initialized = false;
        int tiling;
};

