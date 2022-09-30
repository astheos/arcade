#include "utils.hpp"
#include "things.hpp"
#include "geometry.hpp"

#ifndef INVADERS_HPP
#define INVADERS_HPP

namespace arcade {
  class invaders {
  private:
    geometry::object<4> ship;
    geometry::object<4> enemy;

    geometry::point bullet;

    short position{};

    short lifes{};
    short points{};
    short level{};
    short bright{};

    short steps{};
    short count{};

    bool shot{};

  public:
    invaders() {
      start();

      lifes = 5;
    }

    inline void start() {
      read();
      repos();

      int initial = numerics::rand(1, 6);

      enemy[0].set(-2, initial);
      enemy[1].set(-1, initial);
      enemy[2].set(-2, initial - 1);
      enemy[3].set(-2, initial + 1);

      shot = false;
    }

    inline void read() {
      controls();
      brightness();
      difficulty();
    }

    inline void controls() {
      position = things::first.read(1, 6);

      bool trigger = false;

      trigger = trigger || things::left.read();
      trigger = trigger || things::right.read();
      trigger = trigger || things::top.read();
      trigger = trigger || things::bottom.read();

      if (trigger) {
        shot = trigger;
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
    
    inline int evade() {
      return bullet.get(true) == -1;
    }

    inline bool verify() {
      short posBullet[] = {
        bullet.get(true),
        bullet.get(false)
      };
      short posEnemy[] = {
        enemy[0].get(true),
        enemy[0].get(false)
      };
      short posShip[] = {
        ship[0].get(true),
        ship[0].get(false)
      };

      if (abs(posBullet[0] - posEnemy[0]) < 2 && abs(posBullet[1] - posEnemy[1]) < 2) {
        points++;
        return true;
      }
      if (abs(posShip[0] - posEnemy[0]) < 1 && abs(posShip[1] - posEnemy[1]) >= 3) {
        lifes--;
        return true;
      }
      if (abs(posShip[0] - posEnemy[0]) < 2 && abs(posShip[1] - posEnemy[1]) < 3) {
        lifes--;
        return true;
      }

      return false;
    }

    inline void repos() {
      if (shot) {
        if (count % (steps / 2) == 0) {
          if (evade()) {
            shot = false;
          }
          else {
            bullet -= geometry::point(1, 0);
          }
        }
      }
      else {
        bullet.set(6, position);
      }

      if (count == steps) {
        enemy += geometry::point(1, 0);
      }

      ship[0].set(7, position);
      ship[1].set(6, position);
      ship[2].set(7, position - 1);
      ship[3].set(7, position + 1);
    }

    inline void draw() {
      things::frame.set(ship, true);
      things::frame.set(enemy, true);
      things::frame.set(bullet, true);

      things::layer.set(0, lifes / 10);
      things::layer.set(1, lifes % 10);
      things::layer.set(2, points / 10);
      things::layer.set(3, points % 10);

      things::display.separator(true);
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