#include "controller.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "ship.h"

void Controller::SetDirection(Ship &ship, Ship::Direction input) const
{
  ship.direction = input;
}

void Controller::SetInput(Projectile &projectile, Projectile::Action key) const
{
  projectile.action = key;
}

void Controller::HandleInput(bool &running, Ship &ship, Projectile &projectile) const
{
  SDL_Event e;
   //Control the ship or projectiles movement when the key is pressed
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_w:
        SetDirection(ship, Ship::Direction::kUp);
        break;

      case SDLK_s:
        SetDirection(ship, Ship::Direction::kDown);
        break;

      case SDLK_a:
        SetDirection(ship, Ship::Direction::kLeft);
        break;

      case SDLK_d:
        SetDirection(ship, Ship::Direction::kRight);
        break;
      case SDLK_SPACE:
        SetInput(projectile, Projectile::Action::kFire);
        break;
      }
    }
    //Stop the ship or projectiles movement when the key is not pressed
    else if (e.type == SDL_KEYUP)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_w:
        SetDirection(ship, Ship::Direction::kNeutral);
        break;

      case SDLK_s:
        SetDirection(ship, Ship::Direction::kNeutral);
        break;

      case SDLK_a:
        SetDirection(ship, Ship::Direction::kNeutral);
        break;

      case SDLK_d:
        SetDirection(ship, Ship::Direction::kNeutral);
        break;
      case SDLK_SPACE:
        SetInput(projectile, Projectile::Action::kStop);
        break;

      }
    }
  }
}
