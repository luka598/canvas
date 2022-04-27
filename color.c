#include <math.h>
#include <stdlib.h>

void hsl_to_rgb(float h, float s, float l, int *r, int *g, int *b){
    h = fmod(h, 360);
    float c = (1 - fabs(2 * l - 1)) * s; // chroma
    float h_prime = h / 60;
    float x = c * (1 - fabs(fmod(h_prime, 2) - 1));
    float r_prime, g_prime, b_prime;
    if (h_prime < 1) {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    } else if (h_prime < 2) {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    } else if (h_prime < 3) {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    } else if (h_prime < 4) {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    } else if (h_prime < 5) {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    } else {
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    }
    float m = l - c / 2;
    *r = round(255 * (r_prime + m));
    *g = round(255 * (g_prime + m));
    *b = round(255 * (b_prime + m));
    return;
}

void rgb_to_hsl(int r, int g, int b, float *h, float *s, float *l){
    float r_prime = r / 255.0;
    float g_prime = g / 255.0;
    float b_prime = b / 255.0;
    float c_max = fmax(r_prime, fmax(g_prime, b_prime));
    float c_min = fmin(r_prime, fmin(g_prime, b_prime));
    float delta = c_max - c_min;
    *l = (c_max + c_min) / 2;
    if (delta == 0) {
        *h = 0;
        *s = 0;
    } else {
        if (*l < 0.5) {
            *s = delta / (c_max + c_min);
        } else {
            *s = delta / (2 - c_max - c_min);
        }
        if (r_prime == c_max) {
            *h = (g_prime - b_prime) / delta;
        } else if (g_prime == c_max) {
            *h = 2 + (b_prime - r_prime) / delta;
        } else {
            *h = 4 + (r_prime - g_prime) / delta;
        }
        *h = *h * 60;
        if (*h < 0) {
            *h += 360;
        }
    }
    return;
}