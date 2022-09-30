#include "things.hpp"
#include "geometry.hpp"

#ifndef SNAKE_HPP
#define SNAKE_HPP

namespace arcade {
  class snake {
  private:
    static const short size{64};

    geometry::object<size> body;

    geometry::point food;
    geometry::point sense;

    bool left{};
    bool right{};
    bool top{};
    bool bottom{};

    short level{};
    short bright{};

    short steps{};
    short count{};

    short length{};
    short points{};

  public:
    snake() {
      clear();
      start();
    }

    inline void start() {
      numerics::seed();

      length = 1;
      points = 1;

      short line = numerics::rand(3, 4);
      short column = numerics::rand(3, 4);

      for (auto &part: body) {
        part.set(line, column);
      }

      sense.set(0, 0);
    }

    inline void read() {
      controls();
      brightness();
      difficulty();
    }

    inline void controls() {
      left = things::left.read();
      right = things::right.read();
      top = things::top.read();
      bottom = things::bottom.read();

      short line = sense.get(true);
      short column = sense.get(false);

      if (line or (not (line or column))) {
        if (left) {
          sense.set(0, -1);
        }
        else if (right) {
          sense.set(0, 1);
        }
      }
      if (column or (not (line or column))) {
        if (top) {
          sense.set(-1, 0);
        }
        else if (bottom) {
          sense.set(1, 0);
        }
      }
    }

    inline void brightness() {
      short bright = things::bright.read(0, 100);

      things::screen.brightness(bright);
      things::display.brightness(bright);
    }

    inline void difficulty() {
      level = things::level.read(0, 3);
    }

    inline void time() {
      steps = 20 - 4 * level;
      count = 1 + count % steps;
    }

    inline void render() {
      things::screen.render(things::frame);
      things::display.render(things::layer);
    }

    inline void clear() {
      things::frame.clear();
      things::layer.clear();
    }

    inline void draw() {
      things::frame.set(body, true);

      things::frame.set(food, true);

      things::layer.set(0, -1);
      things::layer.set(1, points / 10);
      things::layer.set(2, points % 10);
      things::layer.set(3, -1);

      things::display.separator(false);
    }

    inline bool verify() {
      for (short index = 1; index < length; index++) {
        if (body[0] == body[index]) {
          return true;
        }
      }

      short line = body[0].get(true);
      short column = body[1].get(false);

      if (line < 0 or line > 7) {
        return true;
      }
      if (column < 0 or column > 7) {
        return true;
      }

      return false;
    }

    inline bool found() {
      return body[0] == food;
    }

    inline void change() {
      while (true) {
        food.set(
          numerics::rand(0, 7),
          numerics::rand(0, 7)
        );

        bool valid = true;

        for (auto &part: body) {
          if (food == part) {
            valid = false;

            break;
          }
        }

        if (valid) {
          break;
        }
      }
    }

    inline void repos() {
      if (count == steps) {
        short index = length - 1;

        while (index) {
          body[index] = body[index - 1];

          index--;
        }

        body[index] += sense;

        if (found()) {
          change();

          length++;
          points++;
        }
        else {
          index = length;

          while (index < size) {
            body[index] = body[index - 1];

            index++;
          }
        }
      }
    }

    inline void update() {
      read();
      time();
      repos();
      clear();
      draw();
      render();
    }

    inline void execute() {
      update();

      if (verify()) {
        start();
      }
    }
  };
}

#endif