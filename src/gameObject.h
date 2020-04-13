#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL2/SDL.h"

//Base class for creating "game objects" like the ship, projectiles and asteroids"
class GameObject
{
public:
  //public member variables to used in derived classes
  bool alive{true};
  float pos_x{0.0f};
  float pos_y{0.0f};
  double angle{0.0};
  int width{0};
  int height{0};

  //Update method to be overriden in derived classes  takes in an unsigned 32bit integer for the start time from the sdl2 library to calculate the elapsed time
  virtual void Update(Uint32 frame_start){};
};

#endif
