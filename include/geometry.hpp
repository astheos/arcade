#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace geometry {
  class point {
  private:
    short line;
    short column;

  public:
    point() :
      line(short()),
      column(short()) {}

    point(short line, short column) :
      line(line),
      column(column) {}
    
    point(const point &other) {
      this->line = other.line;
      this->column = other.column;
    }

    point(const point &&other) {
      this->line = other.line;
      this->column = other.column;
    }
    
    inline short get(bool value) {
      if (value) {
        return line;
      }
      else {
        return column;
      }
    }

    inline void set(short line, short column) {
      this->line = line;
      this->column = column;
    }

    inline bool operator==(const point &other) {
      return this->line == other.line &&
             this->column == other.column;
    }

    inline point operator=(const point &other) {
      this->line = other.line;
      this->column = other.column;

      return point(other.line, other.column);
    }

    inline point operator+(const point &other) {
      return point(line + other.line, column + other.column);
    }

    inline point operator-(const point &other) {
      return point(line - other.line, column - other.column);
    }

    inline point operator+=(const point &other) {
      *this = *this + other;

      return *this;
    }

    inline point operator-=(const point &other) {
      *this = *this - other;

      return *this;
    }

    inline bool operator==(const point &&other) {
      return operator==(other);
    }

    inline point operator=(const point &&other) {
      return operator=(other);
    }

    inline point operator+(const point &&other) {
      return operator+(other);
    }

    inline point operator-(const point &&other) {
      return operator-(other);
    }

    inline point operator+=(const point &&other) {
      return operator+=(other);
    }

    inline point operator-=(const point &&other) {
      return operator-=(other);
    }
  };

  template <const short size>
  class object {
  private:
    point dots[size];

  public:
    object() {}

    object(const object<size> &other) {
      short index = short();

      for (point &dot: dots) {
        dot = other[index++];
      }
    }

    object(const object<size> &&other) {
      short index = short();

      for (point &dot: dots) {
        dot = other[index++];
      }
    }

    object(const point (&values)[size]) {
      short index = short();

      for (point &dot: dots) {
        dot = values[index++];
      }
    }

    inline short length() {
      return size;
    }

    inline point *begin() {
      return dots;
    }

    inline point *end() {
      return dots + size;
    }

    inline object<size> operator=(const object<size> &other) {
      short index = short();

      for (point &dot: dots) {
        dot = other[index++];
      }
    }

    inline object<size> operator+(const point &dot) {
      object<size> values;

      short index = short();

      for (point &value: values) {
        value = dots[index++] + dot;
      }

      return values;
    }

    inline object<size> operator-(const point &dot) {
      object<size> values;

      short index = short();

      for (point &value: values) {
        value = dots[index++] - dot;
      }

      return values;
    }

    inline object<size> operator+=(const point &dot) {
      *this = *this + dot;

      return *this;
    }

    inline object<size> operator-=(const point &dot) {
      *this = *this - dot;

      return *this;
    }

    inline object<size> operator=(const object<size> &&other) {
      return operator=(other);
    }

    inline object<size> operator+(const point &&dot) {
      return operator+(dot);
    }

    inline object<size> operator-(const point &&dot) {
      return operator-(dot);
    }

    inline object<size> operator+=(const point &&dot) {
      return operator+=(dot);
    }

    inline object<size> operator-=(const point &&dot) {
      return operator-=(dot);
    }

    inline point &operator[](short index) {
      return dots[index];
    }
  };

  inline point orthos(const point &other, const point &center, double angle) {
    angle *= 0.01745329251;

    double abscissa = other.get(false);
    double ordered = other.get(true);

    double horizontal = center.get(false);
    double vertical = center.get(true);

    double line   = (abscissa - horizontal) * cos(angle) - (ordered - vertical) * sin(angle) + horizontal;
    double column = (abscissa - horizontal) * sin(angle) + (ordered - vertical) * cos(angle) + vertical;

    return point(line, column);
  }

  inline point rotate(const point &other, const point &center, short amount) {
    static const int sinrt[4] = {0, 1, 0, -1};
    static const int cosrt[4] = {1, 0, -1, 0};

    short abscissa = other.get(false);
    short ordered = other.get(true);

    short horizontal = center.get(false);
    short vertical = center.get(true);

    amount %= 4;

    short line =   (abscissa - horizontal) * cosrt[amount] - (ordered - vertical) * sinrt[amount] + vertical;
    short column = (abscissa - horizontal) * sinrt[amount] + (ordered - vertical) * cosrt[amount] + horizontal;

    return point(line, column);
  }

  template <const short size>
  inline object<size> rotate(const object<size> &other, const point &center, short amount) {
    object<size> rotated{other};

    for (int index = 0; index < size; index++) {
      rotated[index] = rotate(other[index], center, amount);
    }

    return rotated;
  }
}

#endif