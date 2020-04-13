#include "projectile.h"
#include "gameObject.h"
#include "ship.h"
#include <iostream>
#include <cmath>
#define PI 3.14159

//Implementation of overriden public update method
void Projectile::Update(Uint32 frame_start)
{
  //Invokes private control projectile method
  ControlProjectile(frame_start);
}

//Private control method
void Projectile::ControlProjectile(Uint32 frame_start)
{
  //Switch statements to control firing of projectile
  switch (action)
  {
  //Default Stop case sets the projectile position to the ship position and the alive variable to false
  case Action::kStop:
    alive = false;
    pos_x = ship.pos_x;
    pos_y = ship.pos_y;
    break;

  //Fire case sets the projectile angle to the ship's angle so the projectile matches the ship's position
  //Set's the projectile alive boolean to true and uses circular motion, speed and elapsed time to calculate the projectile's velocity/thrust
  case Action::kFire:
    alive = true;
    angle = ship.angle;
    pos_x += (sin(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    pos_y += (-cos(PI / 180 * angle) * speed) * (SDL_GetTicks() - frame_start) * time_scale;
    break;
  }
}
