#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ship.h"
#include "projectile.h"

//Defines a Game class
class Game
{
public:
  //Defines constructor that accepts grid width, gird height, screen width and screen height parameters)
  Game(std::size_t grid_width, std::size_t grid_height, const std::size_t screen_width, const std::size_t screen_height);

  //Game run function runs the game loop
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  //Returns the game score
  int GetScore() const;
  //Variable to hold start time for first frame passed down throughout program
  Uint32 frame_start;

  //Constants used to define the asteroid objects within the game
  const int angle{360};
  const float asteroidSpeed{0.25f};
  const float time_scale{0.25f};
  const int largeAsteroidScale{2};
  const int smallAsteroidScale{1};
  const int max_asteroids{3};
  const int numSmallAsteroids{2};

  //Vectors of smart pointers to regular and small asteroids
  std::vector<std::shared_ptr<GameObject>> asteroids;
  std::vector<std::shared_ptr<GameObject>> small_asteroids;

private:
  //Ship and Projectile objects
  Ship ship;
  Projectile projectile;

  //Random number generators and ranges for x, y and angles
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> rand_angle;

  //Variables to hold the score and scale factors to calculate the position of various game objects on the screen
  int score{0};
  int scaleFactor_w;
  int scaleFactor_h;
  float start_scaled_ship_x;
  float start_scaled_ship_y;

  //Memer fbunction to place asteroids
  void PlaceAsteroids(Uint32 frame_start, int num_asteroids, int x_in, int y_in);

  //Member function to update game play
  void Update(Uint32 frame_start);

  //Collision detection between two rectangular objects
  bool checkCollisions(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);

  //Function to play game of asteroids, moves asteroids on screen, checks if they have hit the ship and if a projectile has hit them and increments the score according to whether an asteroid is a big asteroid or small asteroid
  void Asteroids(Uint32 frame_start, std::vector<std::shared_ptr<GameObject>> &vector_in, int asteroid_scale);
};

#endif
