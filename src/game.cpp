#include <iostream>
#include "SDL2/SDL.h"
#include "game.h"
#include "gameObject.h"
#include <cmath>
#include <vector>
#include <algorithm>
#define PI 3.14159

//Game class constructor initializes member variables, ship object, projectile object and random number generators for x, y and angle
Game::Game(std::size_t grid_width, std::size_t grid_height, const std::size_t screen_width, const std::size_t screen_height)
    : ship(grid_width, grid_height),
      projectile(ship),
      scaleFactor_w(screen_width / grid_width),
      scaleFactor_h(screen_height / grid_height),
      start_scaled_ship_x(ship.pos_x * scaleFactor_w),
      start_scaled_ship_y(ship.pos_y * scaleFactor_h),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      rand_angle(0, angle)
{
  //Call the place asteroids function in the constructor, so when a game class object is created asteroids are placed on the screen
  PlaceAsteroids(frame_start, max_asteroids, random_w(engine), random_h(engine));
}

//Implementation of the run member function
void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
  //Variables to capture frame durations and time stamps
  Uint32 title_timestamp = SDL_GetTicks();
  frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, ship, projectile);
    Update(frame_start);
    renderer.Render(ship, projectile, asteroids, small_asteroids);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// The update method is where the main gameplay occurs
void Game::Update(Uint32 frame_start)
{
  //In this method the Asteroids method is called for large asteroids first and passed the asteroids smart pointers vector and the large asteroid scale variable to help determine that large asteroids being used with this invocation of the method.
  Asteroids(frame_start, asteroids, largeAsteroidScale);

  //The next invocation of the Asteroid method is for the small asteroids generated when a large asteroid is destroyed, the small asteroids vector is passed in with the small asteroid scale variable to indicate small asteroids are to be used
  Asteroids(frame_start, small_asteroids, smallAsteroidScale);

  //Here the asteroids vector size is checked against the small asteroids vector size to spawn more large asteroids, if the asteroids vector is smaller or equal to the larger asteroids vector than more asteroids will be spawned
  if (asteroids.size() <= small_asteroids.size())
  {
    PlaceAsteroids(frame_start, max_asteroids, random_w(engine), random_h(engine));
  }

  //The update method to control the movement of the ship
  ship.Update(frame_start);

  //The update method to control the firing of projectiles
  projectile.Update(frame_start);
}

//Implementation of the place asteroids method takes in the frame_start, number of asteroids, and input x and y coordinates
void Game::PlaceAsteroids(Uint32 frame_start, int num_asteroids, int x_in, int y_in)
{
  //Variables to hold the x and y position to be scaled by the screen dimensions
  float x_scaled = 0.0f;
  float y_scaled = 0.0f;

  //Loop through the number of asteroids inputted, large asteroids are generated 3 or more at a time, small asteroids 2 or less at a time
  for (int i = 0; i < num_asteroids; i++)
  {
    //Create a pointer to a new asteroid game object
    GameObject *asteroid = new GameObject();

    //If the asteroids inputted are large asteroids set their positions to random x and y positions within the loop
    if (num_asteroids > numSmallAsteroids)
    {
      x_in = random_w(engine);
      y_in = random_h(engine);

      //Set the large asteroids width and height
      asteroid->width = ship.width * largeAsteroidScale;
      asteroid->height = ship.width * largeAsteroidScale;
    }
    else
    {
      //Set the small asteroids width and height
      asteroid->width = ship.width * smallAsteroidScale;
      asteroid->height = ship.width * smallAsteroidScale;
    }

    //Scale the input x and y positions by a scale factor determined from the screen dimensions
    float x_scaled = x_in * scaleFactor_w;
    float y_scaled = y_in * scaleFactor_h;

    //Set a random angle for the asteroids motion
    asteroid->angle = PI / 180 * rand_angle(engine);

    //Use collision detection to check if the positions generated collide with the ship, if they do not set the asteroids position to the input or random x and y coordinates
    if (!checkCollisions(start_scaled_ship_x, start_scaled_ship_y, ship.width, ship.height, x_scaled, y_scaled, asteroid->width, asteroid->height))
    {
      asteroid->pos_x = x_in;
      asteroid->pos_y = y_in;
    }
    //Place large asteroids in the large asteroids vector or small asteroids vector based on the number of asteroids input to the method, 3 or more for larger asteroids, 2 or less for small asteroids
    if (num_asteroids > numSmallAsteroids)
    {
      asteroids.emplace_back(asteroid);
    }
    else
    {
      small_asteroids.emplace_back(asteroid);
    }
  }
}

//The asteroids game play method, takes in the frame start time, a reference to a vector of smart pointers to game objects and the asteroid scale to determine if an asteroid is large or small
void Game::Asteroids(Uint32 frame_start, std::vector<std::shared_ptr<GameObject>> &vector_in, int asteroid_scale)
{
  //Create an iterator for the vector
  std::vector<std::shared_ptr<GameObject>>::iterator it = vector_in.begin();

  //Loop through input vector
  while (it != vector_in.end())
  {
    //Scale the ship, projectile and asteroid, cannot use the private member scale factor as the ship's position can constantly change during game play and the ship scale factor member variable is set once in the constructor
    float ship_x_scaled = ship.pos_x * scaleFactor_w;
    float ship_y_scaled = ship.pos_y * scaleFactor_h;
    float projectile_scaled_x = projectile.pos_x * scaleFactor_w;
    float projectile_scaled_y = projectile.pos_y * scaleFactor_h;
    float asteroid_scaled_x = (*it)->pos_x * scaleFactor_w;
    float asteroid_scaled_y = (*it)->pos_y * scaleFactor_h;

    //Check if an asteroid collides with the ship
    if (!checkCollisions(ship_x_scaled, ship_y_scaled, ship.width, ship.height, asteroid_scaled_x, asteroid_scaled_y, (*it)->width, (*it)->height))
    {
      //Move the asteroids using velocity/thrust equations that take into account circular motion and elapsed time
      (*it)->pos_x += sin((*it)->angle) * asteroidSpeed * (SDL_GetTicks() - frame_start) * time_scale;
      (*it)->pos_y += -cos((*it)->angle) * asteroidSpeed * (SDL_GetTicks() - frame_start) * time_scale;
    }

    //If asteroid collides with ship -- Game Over, notify player and do not accumulate the score any more
    else
    {
      std::cout << "Your ship collided with an asteroid"
                << "\n";
      std::cout << "Game over!"
                << "\n";
      ship.alive = false;
      score += 0;
      break;
    }

    //Check if a fired projectile has collided with the asteroid
    bool checkProjectileCollide = checkCollisions(projectile_scaled_x, projectile_scaled_y, projectile.width, projectile.height, asteroid_scaled_x, asteroid_scaled_y, (*it)->width, (*it)->height);

    if (checkProjectileCollide && vector_in.size() > 0 && (*it)->alive && ship.alive)
    {
      //If large asteroid, score is incremented by 5 as they are easier to destroy
      if (asteroid_scale == largeAsteroidScale)
      {
        score += 5;
        (*it)->alive = false;
        //Erase asteroid from vector and place small asteroids at the location
        vector_in.erase(it);
        PlaceAsteroids(frame_start, numSmallAsteroids, (*it)->pos_x, (*it)->pos_y);
      }
      else
      {
        //If small asteroid destroyed, increase score by 10, as they are harder to destroy, erase it from the vector
        score += 10;
        (*it)->alive = false;
        vector_in.erase(it);
      }
    }
    else
    {
      //Increment iterator
      it++;
    }
  }
}

//Implementation of bounding box collision detection between two axis aligned rectangles
bool Game::checkCollisions(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2)
{
  if ((y1 + h1 >= y2) && (y1 <= y2 + h2) && (x1 + w1 >= x2) && (x1 <= x2 + w2))
  {
    return true;
  }

  return false;
}

//Return score
int Game::GetScore() const { return score; }
