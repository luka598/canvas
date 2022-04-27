#include <SDL2/SDL.h>

int CANVAS_QUIT = (int)SDL_QUIT;

int POINT_SIZE = 1;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;


void init_canvas(int width, int height, int point_size) {
    SDL_Init(SDL_INIT_VIDEO);
    // SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    POINT_SIZE = point_size;
    window = SDL_CreateWindow("Canvas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width*POINT_SIZE, height*POINT_SIZE, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void clear_canvas(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void draw_canvas(void) {
    SDL_RenderPresent(renderer);
    // TODO: Find a fix for this
    // Well this must be here because otherwise the program redraws pixels to wrong coordinates
    // I found that around delay of 5 ms is enough to make the program redraw pixels to correct coordinates but this my wary
    SDL_Delay(5); 
}

void exit_canvas(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int get_event(void) {
    SDL_PollEvent(&event);
    return (int)event.type;
}

int check_for_event(int event_type) {
    SDL_PumpEvents();
    int event_exists = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, event_type, event_type);
    return event_exists;
}

void wait_for_event(int event_type) {
    while (get_event() != event_type);
}

void draw_pixel(int x, int y, int r, int g, int b, int a) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    if (x > w) printf("[draw_pixel] WARNING: x is out of bounds, x should be inside [0, %d]\n", w / POINT_SIZE);
    if (y > h) printf("[draw_pixel] WARNING: y is out of bounds, y should be inside [0, %d]\n", h / POINT_SIZE);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (int i = 0; i < POINT_SIZE; i++) {
        for (int j = 0; j < POINT_SIZE; j++) {
            SDL_RenderDrawPoint(renderer, x*POINT_SIZE + i, y*POINT_SIZE + j);
        }
    }
    if (check_for_event(CANVAS_QUIT)){
        exit_canvas();
        exit(0);
    };
}

void draw_pixel_size(int x, int y, int r, int g, int b, int a, int size) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    if (x > w) printf("[draw_pixel_size] WARNING: x is out of bounds, x should be inside [0, %d]\n", w);
    if (y > h) printf("[draw_pixel_size] WARNING: y is out of bounds, y should be inside [0, %d]\n", h);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            draw_pixel(x + i, y + j, r, g, b, a);
        }
    }
}

