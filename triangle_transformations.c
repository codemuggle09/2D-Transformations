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
// Flips point across X or Y axis
Point reflectPoint(Point p, char axis) {
    if (axis == 'x')
        p.y = -p.y + 500; // Adjusted so it stays visible
    if (axis == 'y')
        p.x = -p.x + 500; // Adjusted so it stays visible
    return p;
}
Point getCentroid(Point a, Point b, Point c) {
    Point center;
    center.x = (a.x + b.x + c.x) / 3.0;
    center.y = (a.y + b.y + c.y) / 3.0;
    return center;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Triangle Transformations",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Original triangle points
    Point a = {200, 300}, b = {300, 200}, c = {400, 300};

    // Transformed triangle starts as the same as original
    Point ta = a, tb = b, tc = c;

    int running = 1;
    SDL_Event event;

    while (running) {
        // Check all events like key presses or window close
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    // Move the triangle down and right
                    case SDLK_t:
                        ta = translatePoint(ta, 20, 20);
                        tb = translatePoint(tb, 20, 20);
                        tc = translatePoint(tc, 20, 20);
                        break;
                    // Scale it up slightly
                    case SDLK_s: {
                        Point center = getCentroid(ta, tb, tc);
                        ta = scalePoint(ta, center, 1.1, 1.1);
                        tb = scalePoint(tb, center, 1.1, 1.1);
                        tc = scalePoint(tc, center, 1.1, 1.1);
                        break;
                    }
                    // Rotate by 15 degrees
                    case SDLK_r: {
                        Point center = getCentroid(ta, tb, tc);
                        ta = rotatePoint(ta, center, M_PI / 12);
                        tb = rotatePoint(tb, center, M_PI / 12);
                        tc = rotatePoint(tc, center, M_PI / 12);
                        break;
                    }
                    // Shear it sideways
                    case SDLK_h:
                        ta = shearPoint(ta, 0.2, 0);
                        tb = shearPoint(tb, 0.2, 0);
                        tc = shearPoint(tc, 0.2, 0);
                        break;
                    // Flip over X-axis
                    case SDLK_x:
                        ta = reflectPoint(ta, 'x');
                        tb = reflectPoint(tb, 'x');
                        tc = reflectPoint(tc, 'x');
                        break;
                    // Flip over Y-axis
                    case SDLK_y:
                        ta = reflectPoint(ta, 'y');
                        tb = reflectPoint(tb, 'y');
                        tc = reflectPoint(tc, 'y');
                        break;
                }
            }
        }

        // Black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw original in green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        drawTriangle(renderer, a, b, c);

        // Draw transformed in red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        drawTriangle(renderer, ta, tb, tc);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}