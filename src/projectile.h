#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include "ship.h"
#include "gameObject.h"
#include "SDL2/SDL.h"

//Derived projectile class for creating and controlling the projectiles the player fires, derives from gameObject base class
class Projectile : public GameObject
{
public:
  //enum for two cases for firing projectiles, Fire and Shop
  enum class Action
  {
    kFire,
    kStop
  };

  //The constructor sets the projectile to the same width and height as the ship
  Projectile(Ship &aShip) : ship(aShip)
  {
    width = aShip.width;
    height = aShip.width;
  }
  //Overriden Update method from GameObject base class
  void Update(Uint32 frame_start) override;

  //Defualt enum case is to not be firing
  Action action = Action::kStop;

private:
   //Private method to control projectile movement based on switch statements, takes in an unsigned 32bit integer for the start time from the sdl2 library to calculate the elapsed time
  void ControlProjectile(Uint32 frame_start);

  //Creates a reference to a ship object so that the projectiles size and originating position match the ships
  Ship &ship;

  //Consts for the projectiles speed and a time scale factor
  const float speed{2.0f};
  const float time_scale{0.5f};
};

#endif
