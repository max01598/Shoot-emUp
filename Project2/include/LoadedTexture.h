#ifndef LOADEDTEXTURE_H
#define LOADEDTEXTURE_H

#include <SDL_image.h>
#include <stdio.h>
#include <string>
using namespace std;
class LoadedTexture
{
    public:
        LoadedTexture();
        ~LoadedTexture();
        void free();
        bool loadFromFile(SDL_Renderer* renderer, std::string path);
    protected:

    private:
        int w, h;
        SDL_Texture* texture;
};

#endif // LOADEDTEXTURE_H
