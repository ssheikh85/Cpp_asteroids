#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//Class for creating a texture manager object which creates sdl textures from file names
class TextureManager
{
public:
  //Static method for creating textures from loaded files
  static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *renderer);
};

#endif
