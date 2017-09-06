//
//  main.c
//  Fizzlefade
//
//  Created by Jaco Pretorius on 9/6/17.
//  Copyright © 2017 Jaco Pretorius. All rights reserved.
//

#include <stdio.h>

typedef void (*PIXEL_FUNC_PTR)(uint16_t, uint16_t);

void fizzlefade(PIXEL_FUNC_PTR fizzle_pixel) {
    uint32_t rndval = 1;
    uint16_t x,y;
    do
    {
        y =  rndval & 0x000FF;  /* Y = low 8 bits */
        x = (rndval & 0x1FF00) >> 8;  /* X = High 9 bits */
        unsigned lsb = rndval & 1;   /* Get the output bit. */
        rndval >>= 1;                /* Shift register */
        if (lsb) {                 /* If the output is 0, the xor can be skipped. */
            rndval ^= 0x00012000;
        }
        if (x < 320 && y < 200)
            fizzle_pixel(x , y) ;
    } while (rndval != 1);
}

void print_pixel(uint16_t x, uint16_t y) {
    printf("%d, %d\n", x, y);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Starting fade...\n");
    fizzlefade(&print_pixel);
    printf("All done...\n");
    return 0;
}
