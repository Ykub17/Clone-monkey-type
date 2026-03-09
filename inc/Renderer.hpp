#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "TypingHandler.hpp"
#include "Config.hpp"

class Renderer 
{
public:
    Renderer(sf::Font& f);
 
    void drawGame(sf::RenderWindow& window, const TypingHandler& handler, sf::Vector2f smoothedPos);
    void drawResults(sf::RenderWindow& window, int mistakes, float time, int totalChars);
    void drawRestartButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& text);
    sf::Vector2f getCursorTargetPos(const TypingHandler& handler);
private:
    sf::Font& font;
    sf::RectangleShape cursor;
    std::string wrapText(const std::string& str, float maxWidth);
};

#endif