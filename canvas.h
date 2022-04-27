#ifndef _CANVAS_H_
#define _CANVAS_H_

extern int CANVAS_QUIT;

void init_canvas(int width, int height, int point_size);
void clear_canvas(void);
void draw_canvas(void);
void exit_canvas(void);
int get_event(void);
void check_for_event(int event_type);
void wait_for_event(int event_type);
void draw_pixel(int x, int y, int r, int g, int b, int a);
void draw_pixel_size(int x, int y, int r, int g, int b, int a, int size);
#endif