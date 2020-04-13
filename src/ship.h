#ifndef SHIP_H
#define SHIP_H

#include "gameObject.h"
#include "SDL2/SDL.h"

//Derived ship class for creating and controlling the ship the player flies around, derives from gameObject base class
class Ship : public GameObject
{
public:
  //Direction enum for directions the ship can move in
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight,
    kNeutral
  };

  //Ship constructor for setting the width and height of the ship and its position
  Ship(int grid_width, int grid_height) : grid_width_ship(grid_width), grid_height_ship(grid_height)
  {
    pos_x = grid_width / 2;
    pos_y = grid_height / 2;
    height = grid_width;
    width = grid_height;
  }

  //Start direction for the ship which is a standstill
  Direction direction = Direction::kNeutral;

  //Overriden Update method from GameObject base class
  void Update(Uint32 frame_start) override;

private:
  //Private method to control ship movement based on switch statements, takes in an unsigned 32bit integer for the start time from the sdl2 library to calculate the elapsed time
  void ControlShip(Uint32 frame_start);

  //Constants for ship speed, rotation and time scale
  const float speed{0.5f};
  const float rotation{2.0f};
  const float time_scale{0.5f};

  //private member variables for grid width and height, which are set in the constructor
  int grid_width_ship;
  int grid_height_ship;
};

#endif
