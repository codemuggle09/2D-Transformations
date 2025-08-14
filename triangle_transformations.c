#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

// Just a small struct to hold X and Y coordinates
typedef struct {
    float x, y;
} Point;
// Draws a triangle by connecting the 3 given points
void drawTriangle(SDL_Renderer *renderer, Point a, Point b, Point c) {
    SDL_RenderDrawLine(renderer, (int)a.x, (int)a.y, (int)b.x, (int)b.y);
    SDL_RenderDrawLine(renderer, (int)b.x, (int)b.y, (int)c.x, (int)c.y);
    SDL_RenderDrawLine(renderer, (int)c.x, (int)c.y, (int)a.x, (int)a.y);
}

// Rotates a point around a given center by the given angle
Point rotatePoint(Point p, Point center, float angle) {
    float s = sin(angle), c = cos(angle);

    // Move point to origin (relative to center)
    p.x -= center.x;
    p.y -= center.y;

    // Apply rotation math
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    // Move back to original position
    p.x = xnew + center.x;
    p.y = ynew + center.y;
    return p;
}
// Just shift the point by tx, ty
Point translatePoint(Point p, float tx, float ty) {
    p.x += tx;
    p.y += ty;
    return p;
}
// Grows or shrinks a point relative to some center
Point scalePoint(Point p, Point center, float sx, float sy) {
    p.x = center.x + (p.x - center.x) * sx;
    p.y = center.y + (p.y - center.y) * sy;
    return p;
}
// Tilts the point horizontally or vertically
Point shearPoint(Point p, float shx, float shy) {
    float newX = p.x + shx * p.y;
    float newY = p.y + shy * p.x;
    p.x = newX;
    p.y = newY;
    return p;
}