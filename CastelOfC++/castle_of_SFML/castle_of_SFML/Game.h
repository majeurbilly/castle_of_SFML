#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Map.h"
#include "Player.h"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    Map map;
    Player player;
    Renderer renderer;

public:
    Game();
    void run();
    void handleEvents();
    void update();
    void render();
};
