#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "canvas.h"
#include "color.h"

#define WIDTH  500
#define HEIGHT 500
#define SIZE   1

int main(){
    init_canvas(WIDTH, HEIGHT, SIZE);
    clear_canvas();
    draw_canvas();
    int r, g, b;
    for (int i=0; i<9999; i++){
        clear_canvas();
        for (int j=0; j<WIDTH; j++){
            hsl_to_rgb((j+i)*(360/100), 1, 0.5, &r, &g, &b);
            draw_pixel(j, HEIGHT*fabs(sin((i+j)/200.0)), r, g, b, 255);
        }
        draw_canvas();
    }
    wait_for_event(CANVAS_QUIT);
    return 0;
}