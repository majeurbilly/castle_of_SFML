#include "Map.h"
#include <cmath>

Map::Map() : mapWidth(1800), mapHeight(1600) {
}

void Map::init() {
    // Créer les murs de la map  (x,y  x,y)
    // Murs extérieurs
    walls.push_back(Wall(100, 100, 700, 100));  // Mur nord 
    walls.push_back(Wall(700, 100, 700, 500));  // Mur est
    walls.push_back(Wall(700, 500, 100, 500));  // Mur sud
    walls.push_back(Wall(100, 500, 100, 100));  // Mur ouest
    
    // Murs intérieurs pour créer des pièces
    walls.push_back(Wall(200, 100, 200, 300));  // Mur intérieur vertical
    walls.push_back(Wall(400, 200, 600, 200));  // Mur intérieur horizontal
    walls.push_back(Wall(300, 400, 500, 400));  // Autre mur intérieur
}

std::vector<Wall> Map::getWalls() const {
    return walls;
}

bool Map::checkCollision(float x, float y) const {
    // Vérifier si la position (x, y) entre en collision avec un mur
    for (const auto& wall : walls) {
        // Distance minimale au mur
        float minDistance = 10.0f;
        
        // Calculer la distance au segment de ligne
        float A = x - wall.x1;
        float B = y - wall.y1;
        float C = wall.x2 - wall.x1;
        float D = wall.y2 - wall.y1;
        
        float dot = A * C + B * D;
        float lenSq = C * C + D * D;
        float param = -1;
        
        if (lenSq != 0) {
            param = dot / lenSq;
        }
        
        float xx, yy;
        if (param < 0) {
            xx = wall.x1;
            yy = wall.y1;
        } else if (param > 1) {
            xx = wall.x2;
            yy = wall.y2;
        } else {
            xx = wall.x1 + param * C;
            yy = wall.y1 + param * D;
        }
        
        float dx = x - xx;
        float dy = y - yy;
        float distance = sqrt(dx * dx + dy * dy);
        
        if (distance < minDistance) {
            return true;
        }
    }
    return false;
}

float Map::getDistanceToWall(float startX, float startY, float angle) const {
    float rayX = startX;
    float rayY = startY;
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);
    
    float minDistance = std::numeric_limits<float>::max();
    
    for (const auto& wall : walls) {
        // Algorithme de ray-casting pour trouver l'intersection
        float x1 = wall.x1;
        float y1 = wall.y1;
        float x2 = wall.x2;
        float y2 = wall.y2;
        
        float x3 = startX;
        float y3 = startY;
        float x4 = startX + rayDirX * 1000.0f;
        float y4 = startY + rayDirY * 1000.0f;
        
        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (den == 0) continue;
        
        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        
        if (t >= 0 && t <= 1 && u >= 0) {
            float intersectX = x1 + t * (x2 - x1);
            float intersectY = y1 + t * (y2 - y1);
            
            float dx = intersectX - startX;
            float dy = intersectY - startY;
            float distance = sqrt(dx * dx + dy * dy);
            
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    
    return minDistance == std::numeric_limits<float>::max() ? 1000.0f : minDistance;
}



