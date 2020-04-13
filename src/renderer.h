#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <memory>
#include "SDL2/SDL.h"
#include "ship.h"
#include "projectile.h"

//Renderer class
class Renderer
{
public:
  //Renderer constructor sets private screen_width, screen_height, grid_width and grid_height methods
  Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);

  //Renderer class destructor
  ~Renderer();

  //Render method which takes in a ship, projectile, asteroids vector and small_asteroids vectors
  void Render(Ship const ship, Projectile const projectile, std::vector<std::shared_ptr<GameObject>> asteroids, std::vector<std::shared_ptr<GameObject>> small_asteroids);

  //Update window title method with takes a score and frames per second
  void UpdateWindowTitle(int score, int fps);

private:
  //pointers to SDL_Window and sdl_renderer objects
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  //Pointers to SDL_Texture objects
  SDL_Texture *shipTex;
  SDL_Texture *asteroidTex;
  SDL_Texture *projectileTex;

  //Screen width, screen_height constants
  const std::size_t screen_width;
  const std::size_t screen_height;

  //Horizontal and vertical scale factors to scale rendered objects to appropriate window dimensions in pixels
  int scaleFactor_w;
  int scaleFactor_h;
};

#endif
