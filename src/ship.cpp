#include "ship.h"
#include "gameObject.h"
#include <cmath>
#include <iostream>
#define PI 3.14159

//Implementation of overriden public update method
void Ship::Update(Uint32 frame_start)
{
  //Invokes private control ship method
  ControlShip(frame_start);
}

//Private method to control the ship based on a switch statement that takes 4 different cases, Neutral, Up, Down, Left and Right
void Ship::ControlShip(Uint32 frame_start)
{
  switch (direction)
  {
  //Neutral sets the ships position to zero
  case Direction::kNeutral:
    pos_y += 0;
    pos_x += 0;
    break;
  //The Up case uses circular motion to set the velocity/thrust of the ship to any direction in a 360 degree circle
  case Direction::kUp:
    pos_x += (sin(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    pos_y += (-cos(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    break;

  //The Down case uses circular motion to set the reverse velocity/thrust of the ship to any direction in a 360 degree circle
  case Direction::kDown:
    pos_x += (-sin(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    pos_y += (cos(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    break;

  //The left case decrements the angle to move the ship leftward in a circular fashion
  case Direction::kLeft:
    angle -= rotation;
    break;

  //The left case increments the angle to move the ship rightward in a circular fashion
  case Direction::kRight:
    angle += rotation;
    break;
  }

  //Handles game object if game object is going off of the screen.
  pos_x = fmod(pos_x + grid_width_ship, grid_width_ship);
  pos_y = fmod(pos_y + grid_height_ship, grid_height_ship);
}
