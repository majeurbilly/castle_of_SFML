#include "Player.h"
#include "Map.h"
#include <cmath>

Player::Player() : x(0), y(0), angle(0), moveSpeed(5.0f), rotationSpeed(0.1f), 
                   numRays(60), fov(1.0472f) { // FOV = 60 degrés
    rays.resize(numRays);
    distances.resize(numRays);
}

void Player::init(float x, float y, float angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
}

void Player::update() {
    // Mise à jour de la logique du joueur si nécessaire
}

void Player::moveForward() {
    float newX = x + cos(angle) * moveSpeed;
    float newY = y + sin(angle) * moveSpeed;
    setPosition(newX, newY);
}

void Player::moveBackward() {
    float newX = x - cos(angle) * moveSpeed;
    float newY = y - sin(angle) * moveSpeed;
    setPosition(newX, newY);
}

void Player::turnLeft() {
    setAngle(angle - rotationSpeed);
}

void Player::turnRight() {
    setAngle(angle + rotationSpeed);
}

void Player::castRays(const Map& map) {
    float rayAngleStep = fov / numRays;
    float startAngle = angle - fov / 2;
    
    for (int i = 0; i < numRays; i++) {
        float rayAngle = startAngle + i * rayAngleStep;
        float distance = map.getDistanceToWall(x, y, rayAngle);
        
        // Calculer le point final du rayon
        float endX = x + cos(rayAngle) * distance;
        float endY = y + sin(rayAngle) * distance;
        
        rays[i] = Ray(x, y, endX, endY);
        distances[i] = distance;
    }
}

void Player::setPosition(float newX, float newY) {
    // Ici vous pourriez ajouter une vérification de collision avec la carte
    x = newX;
    y = newY;
}

void Player::setAngle(float newAngle) {
    angle = newAngle;
    // Normaliser l'angle entre 0 et 2π
    const float PI = 3.14159265359f;
    while (angle < 0) angle += 2 * PI;
    while (angle >= 2 * PI) angle -= 2 * PI;
}
