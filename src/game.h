#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "audio.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height,std::size_t num_channels);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  bool FoodCell(int x, int y);
  bool PoisonCell(int x, int y);

 private:
  Snake snake;
  Sound sound;
  SDL_Point food;
  std::vector<SDL_Point> poison; // New:vector to store poison points

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlacePoison(); // New: method to place poision points
  int Update();
  void SetScore(int gamescore); //New set score to a given integer
  
};

#endif