#include "Game.h"
#include "EnemyBullet.h"

GameState gameState = GameState::Menu;

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Starship War"), running(true)
{
    resetGame();

    if (!backgroundTextureMenu.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackgroundmenu.jpg")) {
        std::cerr << "Error loading menu background texture from file." << std::endl;
    }
    backgroundSpriteMenu.setTexture(backgroundTextureMenu);
    backgroundSpriteMenu.setScale(
        window.getSize().x / backgroundSpriteMenu.getGlobalBounds().width,
        window.getSize().y / backgroundSpriteMenu.getGlobalBounds().height
        );

    if (!backgroundTexture.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackground.jpg")) {
        std::cerr << "Error loading level 1 background texture from file." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
        );

    if (!backgroundTexture2.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackgroundreverse.jpg")) {
        std::cerr << "Error loading level 2 background texture from file." << std::endl;
    }
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setScale(
        window.getSize().x / backgroundSprite2.getGlobalBounds().width,
        window.getSize().y / backgroundSprite2.getGlobalBounds().height
        );

    // Position the second sprite directly below the first
    backgroundSprite.setPosition(0, 0);
    backgroundSprite2.setPosition(0, backgroundSprite.getGlobalBounds().height);

    if (!backgroundTextureGameOver.loadFromFile("C:\\Users\\jablo\\Desktop\\gameover.jpg")) {
        std::cerr << "Error loading game over background texture from file." << std::endl;
    }
    backgroundSpriteGameOver.setTexture(backgroundTextureGameOver);
    backgroundSpriteGameOver.setScale(
        window.getSize().x / backgroundSpriteGameOver.getGlobalBounds().width,
        window.getSize().y / backgroundSpriteGameOver.getGlobalBounds().height
        );

    if (!font.loadFromFile("C:\\Users\\jablo\\Desktop\\Space Story.otf")) {
        std::cerr << "Error loading font from file." << std::endl;
    }

    // Setup health text properties
    healthText.setFont(font);
    healthText.setCharacterSize(28); // Font size
    healthText.setFillColor(sf::Color::Green); // Text color
    healthText.setPosition(400.f, window.getSize().y - 50.f); // Bottom-left corner

    // Setup the score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(28); // Adjust size as needed
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(400, 10); // Position at the top center
    scoreText.setString("Score: 0");
}


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter && gameState == GameState::GameOver) {
                std::cout << "Game Over -> Menu" << std::endl; // Debug message
                gameState = GameState::Menu;
                resetGame(); // Reset the game state
                playerShipDestroyed = false;
            } else if (event.key.code == sf::Keyboard::Num1 && gameState == GameState::Menu) {
                std::cout << "Starting Level 1" << std::endl; // Debug message
                gameState = GameState::Level1;
                resetGame();
                spawnEnemies(); // Spawn enemies for Level 1
            } else if (event.key.code == sf::Keyboard::Num2 && gameState == GameState::Menu) {
                std::cout << "Starting Level 2" << std::endl; // Debug message
                gameState = GameState::Level2;
                resetGame();
                spawnEnemies2(); // Spawn enemies for Level 2
            }
        }
    }
}

void Game::spawnEnemies() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness

    // Number of ships to spawn for each type
    int numberOfShips1 = 1;


    // Spawn the first type of enemy ships
    for (int i = 0; i < numberOfShips1; ++i) {
        float x = static_cast<float>(std::rand() % 1000); // Spawn anywhere horizontally on the screen
        float y = static_cast<float>(std::rand() % 100);// Spawn in the upper part of the screen
        gameObjects.push_back(std::make_unique<EnemyShip>(sf::Vector2f(x, y), "C:\\Users\\jablo\\Desktop\\enemy.png"));
    }
}

void Game::spawnEnemies2() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness

    // Spawn the first type of enemy ships
    for (int i = 0; i < 1; ++i) {
        float x = static_cast<float>(std::rand() % 1000); // Spawn anywhere horizontally on the screen
        float y = static_cast<float>(std::rand() % 200); // Spawn in the upper part of the screen
        gameObjects.push_back(std::make_unique<EnemyShip2>(sf::Vector2f(x, y), "C:\\Users\\jablo\\Desktop\\enemyship2.png"));
    }
}

void Game::run() {
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);  // Target 60 FPS
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        handleEvents();  // Handle window events like closing

        timeSinceLastUpdate += clock.restart();  // Measure the time since the last frame

        // Update the game logic at the target frame rate
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);  // Update the game state
        }

        render();  // Draw the game
    }
}


void Game::resetGame() {
    score=0;
    gameObjects.clear();
    floatingTexts.clear();

    playerShip = std::make_unique<PlayerShip>(sf::Vector2f(400.f, windowHeight-270.f));
    gameObjects.push_back(std::move(playerShip));
    spawnEnemies(); // Spawn initial enemies
}

void Game::render() {
    window.clear(sf::Color::Black);  // Clear with black background

    // Draw background depending on the state
    switch (gameState) {
    case GameState::Menu:
        window.draw(backgroundSpriteMenu);  // Menu background
        break;
    case GameState::Level1:
    case GameState::Level2:
        window.draw(backgroundSprite);  // Level background
        window.draw(backgroundSprite2);
        window.draw(healthText);
        window.draw(scoreText);
        break;
    case GameState::GameOver:
        window.draw(backgroundSpriteGameOver);  // Game over screen
        break;
    default:
        break;
    }

    window.display();  // Display what was drawn
}

void Game::handleCollisions() {
    for (auto bulletIt = playerShip->handleToContainerOnBullets()->begin(); bulletIt != playerShip->handleToContainerOnBullets()->end(); ) {
        bool collisionDetected = false;

        // Iterate through enemy ships
        for (auto gameObjectsIterator = gameObjects.begin(); gameObjectsIterator != gameObjects.end(); ) {
            // Check if the bullet collides with the enemy ship

            auto maybeEnemy = dynamic_cast<EnemyShip*>(gameObjectsIterator->get());
            auto maybeEnemy2 = dynamic_cast<EnemyShip2*>(gameObjectsIterator->get());

            //EnemyShip being shot by PlayerShip
            if (maybeEnemy && maybeEnemy->collidesWith(*bulletIt)) {
                collisionDetected = true;
                std::cerr << "Colision! " << std::endl;

                // bulletIt = ship->handleToContainerOnBullets()->erase(bulletIt);  // Remove both the bullet and the enemy ship
                score += 100;    // Increase score by 100 points for EnemyShip
                playerShip-> increaseHealth(3.0f); // Increase player's health by 10 points
                gameObjectsIterator = gameObjects.erase(gameObjectsIterator);

                // Create floating Health points  and score gained at a random position after shooting EnemyShip type 2
                try {
                    float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                    float y = static_cast<float>(std::rand() % 300 + (windowHeight - 300));// Y within lower 300 pixels of the window
                    floatingTexts.emplace_back(sf::Vector2f(x, y), "+3%", font, sf::Color::Green, -50);  //Move the text upwards


                    float xScore = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                    float yScore = static_cast<float>(std::rand() % 200); // Y within lower 300 pixels of the window
                    floatingTexts.emplace_back(sf::Vector2f(xScore, yScore), "100", font, sf::Color::Yellow, -50);  //Move the text upwards
                } catch (const std::exception& e) {
                    std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                }

                break; // Exit the inner loop as bullet has been removed
            }
            //EnemyShip2 being shot by PlayerShip
            else if (maybeEnemy2 && maybeEnemy2->collidesWith(*bulletIt)) {
                collisionDetected = true;
                std::cerr << "Collision with EnemyShip2!" << std::endl;

                // Remove the bullet
                bulletIt = playerShip->handleToContainerOnBullets()->erase(bulletIt);

                // Handle damage to the enemy ship
                maybeEnemy2->takeDamage();

                // Check if EnemyShip2 is destroyed, becuase it need to get shot a few times to disappear
                if (maybeEnemy2->isDestroyed()) {
                    score += 500; // Increase score by 500
                    playerShip-> increaseHealth(20.0f); // Increase player's health by 10 points

                    // Create floating Health points  and score gained at a random position after shooting EnemyShip type 2
                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 300 + (windowHeight - 300));// Y within lower 300 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "+20%", font, sf::Color::Green, -50);  //Move the text upwards


                        float xScore = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float yScore = static_cast<float>(std::rand() % 200); // Y within lower 300 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(xScore, yScore), "500", font, sf::Color::Yellow, -50); //Move the text upwards
                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }
                    // Remove the destroyed enemy ship
                    gameObjectsIterator = gameObjects.erase(gameObjectsIterator);
                }

                break; // Exit the inner loop as bullet has been removed
            }
            else {
                ++gameObjectsIterator;
            }
        }

        if (!collisionDetected) {
            ++bulletIt;
        }
    }

    //PlayerShip being shot by EnemyShip
    for (auto& gameObject : gameObjects) {
        auto ship = dynamic_cast<EnemyShip*>(gameObject.get());
        if (ship)
        {
            for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets()->begin();
                 enemyBulletIt != ship->hantleTheContainerOnEnemyBullets()->end(); ) {
                if (playerShip->collidesWithE(*enemyBulletIt)) {
                    std::cerr << "Collision detected!" << std::endl;

                    playerShip->takeDamage(10.0f);  // Handle damage to the player ship
                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 400 + (windowHeight - 400));// Y within lower 400 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "-10%", font, sf::Color::Red, 75);  //Move the text downwards

                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }

                    if (playerShip->isDestroyed()) {
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more source to handle
                    }

                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets()->erase(enemyBulletIt);  // Remove the enemy bullet
                }
                else {
                    ++enemyBulletIt; // Move to the next bullet if no collision detected
                }
            }
        }
    }

    // Handle collisions with bullets from enemyShips2
    for (auto& gameObject : gameObjects) {
        auto ship = dynamic_cast<EnemyShip2*>(gameObject.get());
        if (ship)
        {
            for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2()->begin();
                 enemyBulletIt != ship->hantleTheContainerOnEnemyBullets2()->end();) {

                if (playerShip->collidesWithE2(*enemyBulletIt)) { // Checks if PlayerShip gets shot

                    // Handle damage to the player ship
                    playerShip->takeDamage(30.0f); // Apply 30 health points damage

                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 400 + (windowHeight - 400));// Y within lower 400 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "-30%", font, sf::Color::Red, 75);  //Move the text downwards

                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }

                    // Check if the player ship is destroyed
                    if (playerShip->isDestroyed()) {
                        // Remove the player ship if it's destroyed
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more player ship to handle
                    }

                    // Remove the enemy bullet that caused the collision
                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2()->erase(enemyBulletIt);
                }

                // Only move to the next bullet if no collision was detected
                else {
                    ++enemyBulletIt;
                }
            }
        }
    }

    // Handle collisions with bullets from enemyShips2Reverse
    for (auto& gameObject : gameObjects) {
        auto ship = dynamic_cast<EnemyShip2*>(gameObject.get());
        if(ship)
        {
            for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2Reverse()->begin();
                 enemyBulletIt != ship->hantleTheContainerOnEnemyBullets2Reverse()->end();) {

                if (playerShip->collidesWithE2Reverse(*enemyBulletIt)) { // Checks if PlayerShip gets shot

                    // Handle damage to the player ship
                    playerShip->takeDamage(30.0f); // Apply 30 health points damage

                    // Check if the player ship is destroyed
                    if (playerShip->isDestroyed()) {
                        // Remove the player ship if it's destroyed
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more player ship to handle
                    }

                    // Remove the enemy bullet that caused the collision
                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2Reverse()->erase(enemyBulletIt);
                }

                // Only move to the next bullet if no collision was detected
                else {
                    ++enemyBulletIt;
                }
            }
        }

    }
}


void Game::update(sf::Time dt) {

    // Check if the player's ship is destroyed
    if (playerShipDestroyed) {
        gameState = GameState::GameOver;
    }


    float currentHealth = playerShip->getHealth();  // Get the player's current health
    float maxHealth = playerShip->getMaxHealth();   // Get the player's max health
    float healthPercentage = (currentHealth / maxHealth) * 100;  // Calculate percentage

    switch (gameState) {
    case GameState::Menu:

        for (auto& gameObject : gameObjects) {
            gameObject->update(dt); // Update game objects
        }

        // Update floating texts
        for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
            it->update(dt); // Update each floating text
            if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
            } else {
                ++it;
            }
        }

        break;
    case GameState::Level1:

        // Move both backgrounds downwards one is reversed

        backgroundSprite.move(0, backgroundSpeed * dt.asSeconds());
        backgroundSprite2.move(0, backgroundSpeed * dt.asSeconds());

        // Check if backgroundSprite is completely out of view
        if (backgroundSprite.getPosition().y > window.getSize().y) {
            backgroundSprite.setPosition(0, backgroundSprite2.getPosition().y - backgroundSprite.getGlobalBounds().height);
        }

        // Check if backgroundSprite2 is completely out of view
        if (backgroundSprite2.getPosition().y > window.getSize().y) {
            backgroundSprite2.setPosition(0, backgroundSprite.getPosition().y - backgroundSprite2.getGlobalBounds().height);
        }

        for (auto& gameObject : gameObjects) {
            gameObject->update(dt); // Update game objects
        }

        // Spawn enemies every 3 seconds
        if (spawnClock.getElapsedTime() >= spawnInterval) {
            spawnEnemies();                // Spawn new enemies
            spawnClock.restart();          // Reset the spawn clock
        }

        // Update health percentage text
        healthText.setString("HP: " + std::to_string(static_cast<int>(healthPercentage)) + "%");  // Update text

        // Update score display
        scoreText.setString("Score: " + std::to_string(score));

        // Update floating texts
        for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
            it->update(dt); // Update each floating text
            if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
            } else {
                ++it;
            }
        }

        // Check for collisions
        handleCollisions();

        break;
    case GameState::Level2:

        // Move both backgrounds downwards

        backgroundSprite.move(0, backgroundSpeed * dt.asSeconds());
        backgroundSprite2.move(0, backgroundSpeed * dt.asSeconds());

        // Check if backgroundSprite is completely out of view
        if (backgroundSprite.getPosition().y > window.getSize().y) {
            backgroundSprite.setPosition(0, backgroundSprite2.getPosition().y - backgroundSprite.getGlobalBounds().height);
        }

        // Check if backgroundSprite2 is completely out of view
        if (backgroundSprite2.getPosition().y > window.getSize().y) {
            backgroundSprite2.setPosition(0, backgroundSprite.getPosition().y - backgroundSprite2.getGlobalBounds().height);
        }

        for (auto& gameObject : gameObjects) {
            gameObject->update(dt); // Update game objects
        }

        // Spawn enemies every 3 seconds
        if (spawnClock.getElapsedTime() >= spawnInterval) {
            spawnEnemies();                // Spawn new enemies
            spawnClock.restart();          // Reset the spawn clock
        }

        if (spawnClock2.getElapsedTime() >= spawnInterval2) {
            spawnEnemies2();               // Spawn new enemies
            spawnClock2.restart();         // Reset the spawn clock
        }

        // Update health percentage text
        healthText.setString("HP: " + std::to_string(static_cast<int>(healthPercentage)) + "%");  // Update text

        // Update score display
        scoreText.setString("Score: " + std::to_string(score));

        // Update floating texts
        for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
            it->update(dt); // Update each floating text
            if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
            } else {
                ++it;
            }
        }

        // Check for collisions
        handleCollisions();

        break;
    case GameState::GameOver:

        break;
    default:
        break;
    }
}

