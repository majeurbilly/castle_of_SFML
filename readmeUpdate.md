## Roadmap d'améliorations pour Castle of C++ (SFML)

Ce document propose des incréments concrets pour améliorer le jeu pas à pas. Chaque étape liste des objectifs, tâches clés et critères d'acceptation pour guider l'implémentation.

### Principes
- **Itératif**: livrer des améliorations jouables à chaque étape.
- **Lisible**: garder un code simple, nommage clair, fonctions courtes.
- **Sûr**: éviter les régressions, tester manuellement à chaque incrément.

---

## v0.1 — Contrôles et collisions robustes
**Objectifs**
- Déplacements continus (lecture clavier par frame), diagonales, rotation fluide.
- Collisions fiables contre les murs existants.

**Tâches clés**
- Lire les touches via `sf::Keyboard::isKeyPressed` dans `Game::update()`.
- Ajouter strafe gauche/droite et diagonales via une méthode de mouvement combiné du `Player` (normalisation du vecteur de déplacement).
- Collisions: vérifier séparément X puis Y ("slide" le long des murs) et ajouter un rayon de joueur (ex: 8 px) dans `Map::checkCollision`.

**Critères d'acceptation**
- Le joueur ne peut pas traverser les murs, même en diagonale.
- Les coins ne bloquent pas totalement: le joueur glisse le long des murs.

---

## v0.2 — Raycasting plus précis
**Objectifs**
- Corriger l'effet fish-eye, améliorer la précision et les performances.

**Tâches clés**
- Remplacer l'intersection segment/segment par un DDA sur grille (carte raster 2D).
- Calculer la distance projetée: `distance * cos(angleRayon - angleJoueur)`.
- Paramétrer FOV (ex: 60°/75°/90°) et nombre de rayons selon la largeur écran.

**Critères d'acceptation**
- Mur perpendiculaire au regard a une hauteur stable quelle que soit la colonne.
- Performances stables en plein écran.

---

## v0.3 — Rendu: textures, sol/plafond, sprites
**Objectifs**
- Donner du relief visuel au monde.

**Tâches clés**
- Textures de murs (atlas ou par mur) + mappage horizontal par point d'impact.
- Sol/plafond: simple gradient au début, puis floor casting.
- Z-buffer (tableau de distances par colonne) pour dessiner des sprites (billboards) correctement masqués par les murs.

**Critères d'acceptation**
- Les textures s'alignent sans distorsion sur les murs.
- Les sprites sont masqués correctement par les murs.

---

## v0.4 — Carte & contenu
**Objectifs**
- Faciliter la création de niveaux.

**Tâches clés**
- Passer à une carte en grille (tilemap) + chargeur JSON/texte.
- Éditeur minimal (in-game ou outil externe simple) pour placer murs/portes/sprites.
- Portes/triggers: segments qui s'ouvrent (animation simple, timer, état).

**Critères d'acceptation**
- Charger/sauver une carte fonctionne.
- Au moins une porte fonctionnelle avec interaction.

---

## v0.5 — Audio & UI
**Objectifs**
- Ambiance sonore et informations de jeu à l'écran.

**Tâches clés**
- Sons: pas, ouverture de porte, ambiance (via SFML Audio).
- HUD: vie, munitions, réticule, FPS.
- Minimap 2D (vue de dessus) avec position et cône de vision du joueur.

**Critères d'acceptation**
- Le HUD s'actualise en temps réel sans impacter fortement les FPS.
- Les sons se déclenchent aux bonnes actions.

---

## v0.6 — Gameplay: ennemis & IA
**Objectifs**
- Ajouter des adversaires basiques.

**Tâches clés**
- États simples: Idle → Chase → Attack → Search.
- Détection par champ de vision (raycast contre `Z-buffer`) ou distance.
- Pathfinding grille (A* simplifié) ou poursuite naïve avec évitement basique.

**Critères d'acceptation**
- Un ennemi détecte le joueur, le poursuit et inflige des dégâts à portée.

---

## v0.7 — Performance & qualité
**Objectifs**
- Stabiliser et fiabiliser le moteur.

**Tâches clés**
- Delta time et cap d'images (ex: 120 FPS) pour un mouvement constant.
- Partition spatiale (uniform grid / quadtree) pour le 2D overlay et sprites.
- Nettoyage: séparer `Renderer`, `Physics/Collision`, `Input`, `World`.
- Tests unitaires des calculs géométriques (intersections, DDA, normalisations).
- Liaisons SFML: s'assurer des bons libs Debug/Release; en dynamique, utiliser /MDd (/MD) et ne pas définir `SFML_STATIC`; en statique, définir `SFML_STATIC` et lier toutes les dépendances (ogg/vorbis/freetype/FLAC, etc.).

**Critères d'acceptation**
- Build Debug/Release propres, sans warnings bloquants.
- Framerate stable en résolution cible.

---

## v0.8 — Packaging & DX
**Objectifs**
- Distribuer le jeu facilement.

**Tâches clés**
- Dossier `assets/` (textures, sons, maps), chemins relatifs robustes.
- Fichier de config (JSON): résolution, FOV, sensibilité souris.
- Packaging: copie des DLL SFML en Release, README utilisateur.
- (Option) CI: build automatique, artefacts Release.

**Critères d'acceptation**
- Un zip/joueur final qui lance le jeu sans setup additionnel.

---

## Conseils d'implémentation (extraits utiles)

### Déplacements continus & diagonales
- Déplacer la lecture des touches vers `Game::update()` et additionner les directions avant/strafe.
- Normaliser `(dx, dy)` avant de multiplier par `moveSpeed` pour que la diagonale ne soit pas plus rapide.

### Collisions agréables (slide)
- Tester collision séparément pour X puis Y:
  - si `!collision(newX, y)`, appliquer `x = newX`; sinon garder `x`.
  - si `!collision(x, newY)`, appliquer `y = newY`; sinon garder `y`.
- Ajouter un rayon joueur (ex: 8 px) autour du point pour éviter d'accrocher les coins.

### Raycasting (DDA) — points clés
- Convertir la carte en grille et marcher cellule par cellule jusqu'au mur.
- Mémoriser la distance au mur pour chaque colonne dans un `zbuffer`.
- Corriger fish-eye par `cos(deltaAngle)`.

### Rendu textures
- Calculer la coordonnée texture (u) via la position d'impact sur le mur.
- Échantillonner un "strip" vertical de la texture selon la hauteur projetée.

---

## Backlog d'idées
- Armes, munitions, pickups.
- Système de sauvegarde rapide.
- Mode speedrun (timer).
- Support manette (XInput).
- Localisation (langues UI).

---

## Références utiles
- SFML: `https://www.sfml-dev.org/`
- Raycasting (tutoriels DDA): `https://lodev.org/cgtutor/raycasting.html`


