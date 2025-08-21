#include "Game.h"
#include "Map.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <optional>

Game::Game() : window(sf::VideoMode(sf::Vector2u(1024, 512)), "Raycasting Castle - SFML"){
	map.init();
	player.init(150.0f, 400.0f, 0.0f);
	renderer.init(&window);
}

void Game::run() {
	while (window.isOpen()) {
		handleEvents();
		update();
		render();
	}
}

void Game::handleEvents() {
	// tant que la file event contient une valeur provenant de la fenetre
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		// Fermeture de la fenêtre
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		// Gestion des touches pour le mouvement du joueur
		if (event->is<sf::Event::KeyPressed>()) {
			const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
			if (keyEvent) {
				switch (keyEvent->code) {
				case sf::Keyboard::Key::W:
					player.moveForward();
					break;
				case sf::Keyboard::Key::S:
					player.moveBackward();
					break;
				case sf::Keyboard::Key::A:
					player.turnLeft();
					break;
				case sf::Keyboard::Key::D:
					player.turnRight();
					break;
				case sf::Keyboard::Key::Escape:
					window.close();
					break;
				}
			}
		}
	}
}

void Game::update() {
	// Mise à jour de la logique du jeu
	player.update();
}

void Game::render() {
	
    renderer.clear();
    
	// calculer l'angle du champs de vision du perso
	player.castRays(map);
    
    // Rendu de la vue 3D
    std::vector<float> distances = player.getDistances();
    renderer.render3DView(distances);

	// Rendu de la vue 2D (vue de dessus) - seulement les murs
	std::vector<Wall> walls = map.getWalls();
	renderer.renderWalls(walls);
    
    renderer.display();
}
