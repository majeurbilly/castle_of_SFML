#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameTypes.h"

// Forward declaration
class Player;

class Renderer {
private:
    sf::RenderWindow* window = nullptr;

public:
    Renderer();
    void init(sf::RenderWindow* window);
    void renderWalls(const std::vector<Wall>& walls);
    void renderPlayer(const Player& player);
    void renderRays(const std::vector<Ray>& rays);
    void render3DView(const std::vector<float>& distances);
    void clear();
    void display();
};
