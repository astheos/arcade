#include "utils.hpp"
#include "geometry.hpp"

#ifndef CANVAS_HPP
#define CANVAS_HPP

namespace canvas {
  class frame {
  private:
    short pattern[8];

  public:
    frame() {
      clear();
    }

    frame(const byte (&values)[8]) {
      short index = short();

      for (short &line: pattern) {
        line = values[index++];
      }
    }

    inline void clear() {
      for (short &line: pattern) {
        line = short();
      }
    }

    inline bool get(const geometry::point &point) {
      short line = point.get(true);
      short column = point.get(false);

      return numerics::get(pattern[line], column);
    }

    inline bool get(const geometry::point &&point) {
      get(point);
    }

    inline void set(const geometry::point &point, bool value) {
      short line = point.get(true);
      short column = point.get(false);

      pattern[line] = numerics::set(pattern[line], column, value);
    }

    inline void set(const geometry::point &&point, bool value) {
      set(point, value);
    }

    template <const short size>
    inline void set(const geometry::object<size> &points, bool value) {
      for (auto &point: points) {
        set(point, value);
      }
    }

    template <const short size>
    inline void set(const geometry::object<size> &&points, bool value) {
      set<size>(points, value);
    }

    inline short* begin() {
      return pattern;
    }

    inline short* end() {
      return pattern + 8;
    }

    inline short &operator[](short index) {
      return pattern[index];
    }
  };

  class layer {
  private:
    short pattern[4];

  public:
    layer() {
      clear();
    }

    layer(const short (&values)[4]) {
      short index = short();

      for (short &line: pattern) {
        line = values[index++];
      }
    }

    inline void clear() {
      for (short &line: pattern) {
        line = short();
      }
    }

    inline short get(short index) {
      return numerics::encode(pattern[index]);
    }

    inline void set(short index, short value) {
      pattern[index] = value;
    }

    inline short* begin() {
      return pattern;
    }

    inline short* end() {
      return pattern + 4;
    }

    inline short &operator[](short index) {
      return pattern[index];
    }
  };
}

#endif