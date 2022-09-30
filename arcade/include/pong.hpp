#include "utils.hpp"
#include "things.hpp"
#include "geometry.hpp"

#ifndef PONG_HPP
#define PONG_HPP

namespace arcade {
  class pong {
  private:
    geometry::object<3> left;
    geometry::object<3> right;

    geometry::point ball;
    geometry::point sense;

    short first{};
    short second{};
    short level{};
    short bright{};

    short steps{};
    short count{};

    short one{};
    short two{};

  public:
    pong() {
      start();
    }

    inline void start() {
      read();
      repos();

      ball.set(
        numerics::rand(3, 4),
        numerics::rand(3, 4)
      );

      sense.set(
        1 - 2 * numerics::rand(0, 1),
        1 - 2 * numerics::rand(0, 1)
      );
    }

    inline void read() {
      controls();
      brightness();
      difficulty();
    }

    inline void controls() {
      int limit = 5;

      if (level > 1) {
        limit = 6;
      }
      if (level > 2) {
        limit = 7;
      }

      first = things::first.read(0, limit);
      second = things::second.read(0, limit);
    }

    inline void brightness() {
      bright = things::bright.read(0, 100);

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
      things::frame.set(left, true);
      things::frame.set(right, true);

      things::frame.set(ball, true);

      things::layer.set(0, one / 10);
      things::layer.set(1, one % 10);
      things::layer.set(2, two / 10);
      things::layer.set(3, two % 10);

      things::display.separator(true);
    }

    inline void repos() {
      for (byte index = 0; index < 3; index++) {
        left[index].set(first + index, 0);
        right[index].set(second + index, 7);
      }

      if (level > 1) {
        left[2].set(first, 0);
        right[2].set(second, 7);
      }
      if (level > 2) {
        left[1].set(first, 0);
        right[1].set(second, 7);
      }

      if (count == steps) {
        int movement = collision();

        switch (movement) {
          case 0:
            break;
          case 1:
            sense.set(
              -sense.get(true),
              sense.get(false)
            );
            break;
          case 2:
            sense.set(
              sense.get(true),
              -sense.get(false)
            );
            break;
          case 3:
            sense.set(
              -sense.get(true),
              -sense.get(false)
            );
            break;
        }

        ball += sense;
      }
    }

    inline int collision() {
      byte line = ball.get(true);
      byte column = ball.get(false);

      if (line == 0) {
        if (column == 1 and first == 0) {
          return 3;
        }
        if (column == 6 and second == 0) {
          return 3;
        }

        return 1;
      }
      if (line == 7) {
        if (column == 1 and first == 5) {
          return 3;
        }
        if (column == 6 and second == 5) {
          return 3;
        }

        return 1;
      }

      if (column == 1) {
        if (first > line) {
          return 0;
        }
        if (first + 3 < line) {
          return 0;
        }

        return 2;
      }
      if (column == 6) {
        if (second > line) {
          return 0;
        }
        if (second + 3 < line) {
          return 0;
        }

        return 2;
      }

      return 0;
    }

    inline bool verify() {
      if (count == steps) {
        byte column = ball.get(false);

        if (column == 0) {
          two++;
          return true;
        }
        if (column == 7) {
          one++;
          return true;
        }
      }

      return false;
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