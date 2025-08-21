#pragma once

// Structure pour représenter un mur
struct Wall {
    float x1, y1, x2, y2;
    Wall() : x1(0), y1(0), x2(0), y2(0) {}
    Wall(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

// Structure pour représenter un rayon
struct Ray {
    float startX, startY, endX, endY;
    Ray() : startX(0), startY(0), endX(0), endY(0) {}
    Ray(float startX, float startY, float endX, float endY) 
        : startX(startX), startY(startY), endX(endX), endY(endY) {}
};
