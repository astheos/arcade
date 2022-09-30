#include "things.hpp"
#include "geometry.hpp"

#ifndef TETRIS_HPP
#define TETRIS_HPP

namespace arcade {
  class tetris {
  private:
    geometry::point point;

    geometry::object<4> block;

    short position{};
    short rotation{};
    short level{};
    short bright{};

    short steps{};
    short count{};
    short piece{};
    
    bool change{};

  public:
    tetris() {
      start();
    }

    inline void start() {
      numerics::seed();
    }

    inline void generate() {
      short line = point.get(true);
      short column = point.get(false);

      geometry::object<4> other({
        geometry::point(line, column + 0),
        geometry::point(line, column + 1),
        geometry::point(line, column + 2),
        geometry::point(line, column + 3)
      });

      switch (piece) {
        case 1:
          other[3].set(line + 1, column + 0);
          break;
        case 2:
          other[3].set(line + 1, column + 1);
          break;
        case 3:
          other[3].set(line + 1, column + 2);
          break;
        case 4:
          other[0].set(line + 1, column + 0);
          other[3].set(line + 1, column + 1);
          break;
        case 5:
          other[2].set(line + 1, column + 1);
          other[3].set(line + 1, column + 2);
          break;
        case 6:
          other[2].set(line + 1, column + 0);
          other[3].set(line + 1, column + 1);
          break;
      }

      block = geometry::rotate(other, other[1], rotation);
    }

    inline void read() {
      controls();
      brightness();
      difficulty();
    }

    inline void controls() {
      short inferior = 7;
      short superior = 0;

      for (auto &part: block) {
        short column = part.get(false);

        inferior = min(inferior, column);
        superior = max(superior, column);
      }

      Serial.println(superior - inferior);
      position = things::first.read(0, 7 - (superior - inferior));
      rotation = things::second.read(0, 3);

      if (change) {
        piece = numerics::rand(0, 6);

        change = false;
      }
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
      things::frame.set(block, true);
    }

    inline bool collision() {
      for (auto &part: block) {
        short line = part.get(true);
        short column = part.get(false);

        if (line == 7) {
          return true;
        }
        if (things::frame.get(geometry::point(line + 1, column))) {
          return true;
        }
      }

      return false;
    }

    inline void repos() {
      point.set(point.get(true), position);

      if (count == steps) {
        if (collision()) {
          generate();
          return;
        }

        point += geometry::point(1, 0);
      }

      things::frame.set(block, false);

      generate();
    }

    inline void update() {
      read();
      time();
      repos();
      draw();
      render();
    }

    inline void execute() {
      update();
    }
  };
}

#endif