#ifndef Effect_H
#define Effect_H
#include <Adafruit_NeoPixel.h>

typedef struct {
  byte r;
  byte g;
  byte b;
} RGB;

/**
 * Base effect class
 */
class Effect {
  public:
    Effect() {
      clear();
    }

    virtual void update() {

    }

    void clear() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = { 0, 0, 0 };
      }
    }

    RGB get(byte pixelNo) {
      return matrix[pixelNo];
    }

    int size() {
      return PIXEL_COUNT;
    }
  protected:
    RGB matrix[PIXEL_COUNT];
};
#endif
