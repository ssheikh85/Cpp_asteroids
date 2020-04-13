#include "TextureManager.h"
#include <iostream>
#include <string>

SDL_Texture *TextureManager::LoadTexture(const char *fileName, SDL_Renderer *renderer)
{
  //Creares surface from file path
  SDL_Surface *sdl_surface = IMG_Load(fileName);
  if (nullptr == sdl_surface)
  {
    std::cerr << "Surface could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Creates texture from surface
  SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
  if (nullptr == sdl_texture)
  {
    std::cerr << "Texture could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  //Remove the surface as it is no longer needed
  SDL_FreeSurface(sdl_surface);

  //Return the texture
  return sdl_texture;
}
