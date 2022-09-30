#ifndef UTILS_HPP
#define UTILS_HPP

namespace numerics {
  inline void seed() {
    randomSeed(micros() + millis());
    randomSeed(random(1, micros()) * (1ull + analogRead(0)));
  }

  inline long rand(long minimum, long maximum) {
    return random(minimum, maximum + 1);
  }

  inline byte reverse(byte number) {
    byte other = 1;
    byte count = 8;

    while (count--) {
      other = (other << 1) | (number & 1);
      number = (number >> 1);
    }

    return other;
  }

  inline byte get(byte number, byte position) {
    number = number >> (7 - position);

    return number & 1;
  }

  inline byte set(byte number, byte position, bool value) {
    byte mask = 1 << (7 - position);

    if (value) {
      number = number | mask;
    }
    else {
      number = number & ~mask;
    }

    return number;
  }

  inline byte encode(short number) {
    static const byte code[] = {
      63, 6, 91, 79, 102, 109, 125, 7, 127, 111
    };

    if (number < 0) {
      return 0;
    }

    return code[number];
  }
}

#endif