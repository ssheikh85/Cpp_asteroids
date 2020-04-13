#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ship.h"
#include "projectile.h"

//Controller class for registering keyboard input from the user to control the ship and fire projectiles
class Controller
{
public:
  //Public method for setting the input for the ship and projectile class objects
  void HandleInput(bool &running, Ship &ship, Projectile &projectile) const;

private:
  //Private method to register the appropriate keys to control the ships direction
  void SetDirection(Ship &ship, Ship::Direction input) const;
  //Private method to register the appropriate keys to control firing projectiles
  void SetInput(Projectile &projectile, Projectile::Action key) const;
};

#endif
