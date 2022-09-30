#include "things.hpp"
#include "geometry.hpp"

#ifndef PAINT_HPP
#define PAINT_HPP

namespace arcade {
  class paint {
  private:
    geometry::point pencil;

    short action{};

    short line{};
    short column{};

  public:
    paint() {
      start();
    }

    inline void start() {
      clear();
      controls();
    }

    inline void controls() {
      line = pencil.get(true);
      column = pencil.get(false);

      bool buttons[3] = {
        things::left.read(),
        things::right.read(),
        things::top.read()
      };

      for (short index = 1; index < 4; index++) {
        if (buttons[index - 1]) {
          action = index;

          break;
        }
      }

      pencil.set(
        things::first.read(0, 7),
        things::second.read(0, 7)
      );
    }

    inline void draw() {
      geometry::point shadow(line, column);

      bool value = things::frame.get(shadow);

      switch (action) {
        case 1:
          things::frame.set(shadow, value);
          things::frame.set(pencil, true);
          break;
        case 2:
          things::frame.set(shadow, true);
          things::frame.set(pencil, true);
          break;
        case 3:
          things::frame.set(shadow, false);
          things::frame.set(pencil, true);
          break;
        case 4:
          break;
      }
    }

    inline void clear() {
      things::frame.clear();
      things::layer.clear();
    }

    inline void render() {
      things::screen.render(things::frame);
      things::display.render(things::layer);
    }

    inline void update() {
      controls();
      draw();
      render();
    }

    inline void execute() {
      update();
    }
  };
}



#endif