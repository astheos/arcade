#include "pong.hpp"
#include "snake.hpp"
#include "tetris.hpp"
#include "invaders.hpp"

#include "paint.hpp"

#include "utils.hpp"
#include "things.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

namespace engine {
  arcade::pong pong;
  arcade::snake snake;
  arcade::tetris tetris;
  arcade::invaders invaders;

  arcade::paint paint;

  const int choice = 3;

  inline void init() {
    numerics::seed();

    Serial.begin(9600);
  }

  template <typename type>
  inline void execute(const type &game) {
    game.execute();
  }

  inline void run() {
    switch (choice) {
      case 1:
        execute(pong);
        break;
      case 2:
        execute(snake);
        break;
      case 3:
        execute(tetris);
        break;
      case 4:
        execute(invaders);
        break;
      case 6:
        execute(paint);
        break;
      default:
        break;
    }

    delay(things::period);
  }
}

#endif