#pragma once
#include <vector>
#include "GameTypes.h"

class Map;

class Player {
private:
    float x, y, angle;
    float moveSpeed;
    float rotationSpeed;
    std::vector<Ray> rays;
    std::vector<float> distances;
    int numRays;
    float fov;

public:
    Player();
    void init(float x, float y, float angle);
    void update();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void castRays(const Map& map);
    
    // Getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getAngle() const { return angle; }
    std::vector<Ray> getRays() const { return rays; }
    std::vector<float> getDistances() const { return distances; }
    
    // Setters
    void setPosition(float newX, float newY);
    void setAngle(float newAngle);
};
