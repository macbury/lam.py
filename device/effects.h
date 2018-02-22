byte defaultBrightness = 0;
void colorWipe(uint32_t c, uint8_t wait) {
  strip.setBrightness(defaultBrightness);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void clearColor() {
  strip.setBrightness(0);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  strip.setBrightness(defaultBrightness);
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
