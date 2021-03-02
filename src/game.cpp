#include "game.h"
#include <iostream>
#include "SDL.h"
#include "audio.h"

Game::Game(std::size_t grid_width, std::size_t grid_height,std::size_t num_channels)
    : snake(grid_width, grid_height),
      sound(num_channels),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood();
  PlacePoison();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, poison);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !PoisonCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// New:: Method to add posioned food to the game for the snake
void Game::PlacePoison() 
{
  int x, y;

  // Check if score is up to 5
  if (score % 5 == 0 ) 
    {
      //Create an SDL point and add "score" number of poison point to the poison vector
      SDL_Point p; p.x = 0; p.y = 0;
      for(int i =0 ; i< score ; i++)
      {
        poison.emplace_back(p);
      }
    }
  // Iterate through all the items in the poison vector
  for(SDL_Point  &p : poison)
  {
    if (p.x == 0 && p.y == 0)
    {
        while (true)
      {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake or food item before placing poison.
        if (!snake.SnakeCell(x, y) && !Game::FoodCell(x,y) && !Game::PoisonCell(x,y)) 
        {
          p.x = x;
          p.y = y;
          break;
        }
      }
    }
    
  }
}
void Game::Update() {
  if (!snake.alive) 
  {
    sound.PlaySound(1,1);
    SDL_Delay(3500);
    return;
  }
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) 
  {
    sound.PlaySound(0, 0);
    score++;
    PlaceFood();
    PlacePoison();
    // Grow snake and increase speed.
    snake.GrowBody();
    //snake.speed += 0.02;
  }
  for (SDL_Point const &p : poison)
  {
    // New:Check if the snake has eaten poisoned food
    if(p.x == new_x && p.y == new_y)
    {
      // The snake dies if it eats poisoned food
      snake.alive = false ;
    }
  }
}
  

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// New: Verify if a given cell is a occupied by food
bool Game::FoodCell(int x, int y) 
{
  if (x == food.x && y == food.y) 
  {
    return true;
  }
   return false;
}

bool Game::PoisonCell(int x, int y) 
{
  for(auto &P : poison)
  {
    if (x == P.x && y == P.y) 
    {
      return true;
    }
  }
  return false;
}