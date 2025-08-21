#pragma once
#include <vector>
#include "GameTypes.h"

class Map {
private:
    std::vector<Wall> walls;
    int mapWidth;
    int mapHeight;

public:
    Map();
    void init();
    std::vector<Wall> getWalls() const;
    bool checkCollision(float x, float y) const;
    float getDistanceToWall(float startX, float startY, float angle) const;
};
