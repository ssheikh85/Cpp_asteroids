#include "renderer.h"
#include "TextureManager.h"
#include <iostream>
#include <string>
#include <vector>

//Renderer constructor implementation and member function initialization
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height, const std::size_t grid_width,
                   const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      scaleFactor_w(screen_width / grid_width),
      scaleFactor_h(screen_height / grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Load ship, projectile and asteroid textures using texture manager LoadTexture method
  shipTex = TextureManager::LoadTexture("../assets/ship.png", sdl_renderer);
  projectileTex = TextureManager::LoadTexture("../assets/projectile.png", sdl_renderer);
  asteroidTex = TextureManager::LoadTexture("../assets/asteroid.png", sdl_renderer);
}

//Renderer destructor
Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

//Render method implementation which takes in a ship, projectile, asteroids vector and small_asteroids vectors
void Renderer::Render(Ship const ship, Projectile const projectile, std::vector<std::shared_ptr<GameObject>> asteroids, std::vector<std::shared_ptr<GameObject>> small_asteroids)
{
  //clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //Render ship from loaded texture and include support for rotation
  SDL_Rect shipRect;
  shipRect.w = ship.width;
  shipRect.h = ship.height;
  shipRect.x = ship.pos_x * scaleFactor_w;
  shipRect.y = ship.pos_y * scaleFactor_h;
  SDL_RenderCopyEx(sdl_renderer, shipTex, NULL, &shipRect, ship.angle, NULL, SDL_FLIP_NONE);

  //Render projectiles one at a time from loaded texture
  SDL_Rect projectileRect;
  projectileRect.w = projectile.width;
  projectileRect.h = projectile.height;
  projectileRect.x = projectile.pos_x * scaleFactor_w;
  projectileRect.y = projectile.pos_y * scaleFactor_h;
  SDL_RenderCopy(sdl_renderer, projectileTex, NULL, &projectileRect);

  //Render large asteroids from vectors of large asteroids
  for (auto const item : asteroids)
  {
    SDL_Rect asteroidRect;
    asteroidRect.w = item->width;
    asteroidRect.h = item->height;
    asteroidRect.x = item->pos_x * scaleFactor_w;
    asteroidRect.y = item->pos_y * scaleFactor_h;
    SDL_RenderCopy(sdl_renderer, asteroidTex, NULL, &asteroidRect);
  }

  //Render small asteroids from vector of small asteroids
  for (auto const small_item : small_asteroids)
  {
    SDL_Rect smallAsteroidRect;
    smallAsteroidRect.w = small_item->width;
    smallAsteroidRect.h = small_item->height;
    smallAsteroidRect.x = small_item->pos_x * scaleFactor_w;
    smallAsteroidRect.y = small_item->pos_y * scaleFactor_h;
    SDL_RenderCopy(sdl_renderer, asteroidTex, NULL, &smallAsteroidRect);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

//Update window title method implementation with score and frames per second
void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
