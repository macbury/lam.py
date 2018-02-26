#include "effect/effect.h"
Effect * currentEffect = NULL;
#include "effect/clear.h"
#include "effect/helper.h"
#include "effect/button.h"
#include "effect/failed.h"
#include "effect/success.h"
#include "effect/running.h"
#include "effect/coffee.h"
#include "effect/food_alert.h"

ClearEffect * clearEffect = new ClearEffect();
void runEffect(Effect * toRunEffect, Effect * fromEffect, int duration) {
  transitToEffect(fromEffect, toRunEffect, 1000);
  while(duration >= 0) {
    toRunEffect->update();

    for(byte i=0; i<strip.numPixels(); i++) {
      RGB currentColor = toRunEffect->get(i);
      strip.setPixelColor(i, strip.Color(currentColor.r, currentColor.g, currentColor.b));
    }

    strip.show();
    duration -= TICK_DELAY;
    yield();
    delay(TICK_DELAY);
  }

  transitToEffect(toRunEffect, fromEffect, 1000);
}

int currentCoffeeNumber = 0;
void coffeeEffect(int nextNoOfCoffee) {
  if (!teamOnline || nextNoOfCoffee == currentCoffeeNumber) {
    return;
  }

  currentCoffeeNumber = nextNoOfCoffee;
  CoffeeEffect * coffeeEffect = new CoffeeEffect();
  runEffect(coffeeEffect, currentEffect, 1000);
  delete coffeeEffect;
}

void foodAlertEffect() {
  if (!teamOnline) {
    return;
  }
  FoodAlertEffect * foodAlertEffect = new FoodAlertEffect();
  runEffect(foodAlertEffect, currentEffect, 3000);
  delete foodAlertEffect;
}
