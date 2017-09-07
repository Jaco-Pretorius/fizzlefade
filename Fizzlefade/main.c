//
//  main.c
//  Fizzlefade
//
//  Created by Jaco Pretorius on 9/6/17.
//  Copyright © 2017 Jaco Pretorius. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

typedef void (*PIXEL_FUNC_PTR)(uint16_t, uint16_t);

#define FIRST_BIT        (uint32_t)(0x00001)
#define FIRST_EIGHT_BITS (uint32_t)(0x000FF)
#define NEXT_NINE_BITS   (uint32_t)(0x1FF00)
#define LINEAR_FEEDBACK_SHIFT_REGISTER_TAPS (uint32_t)(0x00012000)

void fizzlefade(PIXEL_FUNC_PTR fizzle_pixel) {
  uint32_t random_value = 1;
  uint16_t x,y;
  unsigned least_significant_bit;
  do
  {
    y = (random_value & FIRST_EIGHT_BITS) - 1;
    x = (random_value & NEXT_NINE_BITS) >> 8;
    
    least_significant_bit = random_value & FIRST_BIT;
    random_value >>= 1;
    if (least_significant_bit) {
      random_value ^= LINEAR_FEEDBACK_SHIFT_REGISTER_TAPS;
    }
    
    if (x < 320 && y < 200) {
      fizzle_pixel(x , y);
    }
  } while (random_value != 1);
}

void print_pixel(uint16_t x, uint16_t y) {
  printf("%d, %d\n", x, y);
}

// Test Functions

static bool test_screen[320][200];

void reset_test_screen() {
  int x,y;
  for(x=0;x<320;x++) {
    for(y=0;y<200;y++) {
      test_screen[x][y] = false;
    }
  }
}

void test_every_x_position_is_between_0_and_320(uint16_t x, uint16_t y) {
  if (x < 0 || x >= 320) {
    printf("test_every_x_position_is_between_0_and_320: %d was outside of the expected range\n", x);
  }
}

void test_every_y_position_is_between_0_and_200(uint16_t x, uint16_t y) {
  if (y < 0 || y >= 200) {
    printf("test_every_y_position_is_between_0_and_200: %d was outside of the expected range\n", x);
  }
}

void test_every_position_is_unique(uint16_t x, uint16_t y) {
  if (test_screen[x][y]) {
    printf("test_every_position_is_unique: %d, %d was returned multiple times\n", x, y);
  } else {
    test_screen[x][y] = true;
  }
}

void test_every_possible_position_is_returned(uint16_t x, uint16_t y) {
  test_screen[x][y] = true;
}


void run_all_tests() {
  printf("Running tests.\n");
  
  fizzlefade(&test_every_x_position_is_between_0_and_320);
  fizzlefade(&test_every_y_position_is_between_0_and_200);
  
  reset_test_screen();
  fizzlefade(&test_every_position_is_unique);
  
  reset_test_screen();
  fizzlefade(&test_every_possible_position_is_returned);
  int x,y;
  for(x=0;x<320;x++) {
    for(y=0;y<200;y++) {
      if (!test_screen[x][y]) {
        printf("test_every_possible_position_is_returned: %d, %d was never returned\n", x, y);
      }
    }
  }
  
  printf("All done.\n");
}

// End of Test Functions

int main(int argc, const char * argv[]) {
  run_all_tests();
  return 0;
}
