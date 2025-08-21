#include "Renderer.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <cstdint>

Renderer::Renderer() {
    // Constructeur par défaut
}

void Renderer::init(sf::RenderWindow* window) {
    this->window = window;
}

void Renderer::renderWalls(const std::vector<Wall>& walls) {
    // Correction pour SFML 3.x : utiliser sf::Vector2f pour les positions
    for (const auto& wall : walls) {
        sf::Vertex vertices[2];
        
        // Correction E0289 : utiliser la nouvelle syntaxe Vertex avec double accolades
        vertices[0] = sf::Vertex{{wall.x1 * 0.3f, wall.y1 * 0.3f}, sf::Color::Red};
        vertices[1] = sf::Vertex{{wall.x2 * 0.3f, wall.y2 * 0.3f}, sf::Color::Red};
        
        // Correction E0140 : draw prend les bons paramètres
        window->draw(vertices, 2, sf::PrimitiveType::Lines);
    }
}

void Renderer::renderPlayer(const Player& player) {
    // Correction E0415 : utiliser sf::Vector2f pour la position
    sf::CircleShape playerShape(5.0f);
    playerShape.setPosition(sf::Vector2f(player.getX(), player.getY()));
    playerShape.setFillColor(sf::Color::Red);
    
    window->draw(playerShape);
}

void Renderer::renderRays(const std::vector<Ray>& rays) {
    for (const auto& ray : rays) {
        sf::Vertex vertices[2];
        
        // Correction E0289 : nouvelle syntaxe Vertex
        vertices[0] = sf::Vertex{{ray.startX, ray.startY}, sf::Color::Yellow};
        vertices[1] = sf::Vertex{{ray.endX, ray.endY}, sf::Color::Yellow};
        
        // Correction E0140 : paramètres corrects pour draw
        window->draw(vertices, 2, sf::PrimitiveType::Lines);
    }
}

void Renderer::render3DView(const std::vector<float>& distances) {
    float wallHeight = 200.0f;
    float screenWidth = static_cast<float>(window->getSize().x);
    float screenHeight = static_cast<float>(window->getSize().y);
    float stripWidth = screenWidth / distances.size();
    
    for (size_t i = 0; i < distances.size(); ++i) {
        float distance = distances[i];
        if (distance > 0) {
            float height = (wallHeight / distance) * 100.0f;
            float y = (screenHeight - height) / 2.0f;
            
            sf::RectangleShape wall;
            wall.setSize(sf::Vector2f(stripWidth, height));
            wall.setPosition(sf::Vector2f(i * stripWidth, y));
            
            // Calculer la luminosité basée sur la distance
            float brightness = std::max(0.1f, 1.0f - (distance / 1000.0f));
            sf::Color color(static_cast<std::uint8_t>(255 * brightness),
                          static_cast<std::uint8_t>(255 * brightness),
                          static_cast<std::uint8_t>(255 * brightness));
            wall.setFillColor(color);
            
            window->draw(wall);
        }
    }
}

void Renderer::clear() {
    window->clear(sf::Color::Black);
}

void Renderer::display() {
    window->display();
}
