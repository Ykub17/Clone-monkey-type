#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "TypingHandler.hpp"
#include "Renderer.hpp"

class Game 
{
public:
    Game();         
    ~Game();
    void run();

private:
    void processEvents();
    void render();

    sf::RenderWindow window;
    sf::Font font;
    TypingHandler* handler;
    Renderer* renderer;
    
    // Кнопка и текст
    sf::RectangleShape restartButton;
    sf::Text restartText;
    
    // Плавный курсор
    sf::Vector2f smoothedCursorPos;
};

#endif