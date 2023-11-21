#include <stdio.h>
#include "periph/gpio.h"
#include "thread.h"
#include "xtimer.h"

#define RED_PIN GPIO_PIN(2, 4)
#define GREEN_PIN GPIO_PIN(2, 5)
#define BLUE_PIN GPIO_PIN(2, 2)

#define RED_PIN_2 GPIO_PIN(2, 13)
#define GREEN_PIN_2 GPIO_PIN(2, 12)
#define BLUE_PIN_2 GPIO_PIN(2, 14)

char thread_stack[THREAD_STACKSIZE_MAIN];

void set_led_color(int red, int green, int blue)
{
  gpio_write(RED_PIN, red);
  gpio_write(GREEN_PIN, green);
  gpio_write(BLUE_PIN, blue);
}

void set_led_color_main_thread(int red, int green, int blue)
{
  gpio_write(RED_PIN_2, red);
  gpio_write(GREEN_PIN_2, green);
  gpio_write(BLUE_PIN_2, blue);
}

static void *led_thread(void *arg)
{
  (void)arg;

  while (1)
  {
    puts("LED THREAD");
    set_led_color(1, 0, 0);
    xtimer_usleep(2000 * US_PER_MS);
    puts("LED THREAD");
    set_led_color(0, 1, 0);
    xtimer_usleep(2000 * US_PER_MS);
    puts("LED THREAD");
    set_led_color(0, 0, 1);
    xtimer_usleep(2000 * US_PER_MS);
  }

  return NULL;
}

int main(void)
{
  gpio_init(RED_PIN, GPIO_OUT);
  gpio_init(GREEN_PIN, GPIO_OUT);
  gpio_init(BLUE_PIN, GPIO_OUT);

  gpio_init(RED_PIN_2, GPIO_OUT);
  gpio_init(GREEN_PIN_2, GPIO_OUT);
  gpio_init(BLUE_PIN_2, GPIO_OUT);

  thread_create(thread_stack, sizeof(thread_stack),
                THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                led_thread, NULL, "led_thread");

  while (1)
  {
    puts("MAIN THREAD");
    set_led_color_main_thread(0, 0, 1);
    xtimer_usleep(1000 * US_PER_MS);
    puts("MAIN THREAD");
    set_led_color_main_thread(1, 0, 0);
    xtimer_usleep(1000 * US_PER_MS);
    puts("MAIN THREAD");
    set_led_color_main_thread(0, 1, 0);
    xtimer_usleep(1000 * US_PER_MS);
  }
}
