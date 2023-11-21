#include <stdio.h>
#include "periph/gpio.h"
#include "thread.h"
#include "xtimer.h"

#define RED_PIN GPIO_PIN(2, 4)
#define GREEN_PIN GPIO_PIN(2, 5)
#define BLUE_PIN GPIO_PIN(2, 2)

char thread_stack[THREAD_STACKSIZE_MAIN];
char thread_1_stack[THREAD_STACKSIZE_MAIN];
char thread_2_stack[THREAD_STACKSIZE_MAIN];
int MAX_VALUE = 10000000;
volatile int counter = 0;
kernel_pid_t thread_main;

void set_led_color(int red, int green, int blue)
{
  gpio_write(RED_PIN, red);
  gpio_write(GREEN_PIN, green);
  gpio_write(BLUE_PIN, blue);
}

void *increase_counter_thread_1(void *arg)
{
  (void)arg;
  set_led_color(0, 0, 0);
  puts("THREAD 1");
  int i;
  for (i = 0; i < MAX_VALUE; i++)
  {
    counter++;
  }
  return NULL;
}

void *increase_counter_thread_2(void *arg)
{
  (void)arg;
  set_led_color(0, 0, 0);
  puts("THREAD 2");
  int i;
  for (i = 0; i < MAX_VALUE; i++)
  {
    counter++;
  }
  thread_wakeup(thread_main);
  return NULL;
}

void *main_thread(void *arg)
{
  (void)arg;
  puts("MAIN THREAD");
  set_led_color(0, 0, 1);
  thread_sleep();
  puts("MAIN THREAD");
  if (counter == MAX_VALUE * 2)
  {
    set_led_color(0, 1, 0);
    puts("CORRECT");
  }
  else
  {
    set_led_color(1, 0, 0);
    puts("INCORRECT");
  }
  return NULL;
}

int main(void)
{
  gpio_init(RED_PIN, GPIO_OUT);
  gpio_init(GREEN_PIN, GPIO_OUT);
  gpio_init(BLUE_PIN, GPIO_OUT);

  {
    thread_main = thread_create(thread_stack, sizeof(thread_stack),
                                THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                                main_thread, NULL, "Main Thread");
  }

  {
    thread_create(thread_1_stack, sizeof(thread_1_stack),
                  THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                  increase_counter_thread_1, NULL, "Thread 1");
  }

  {
    thread_create(thread_2_stack, sizeof(thread_2_stack),
                  THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                  increase_counter_thread_2, NULL, "Thread 2");
  }
}
