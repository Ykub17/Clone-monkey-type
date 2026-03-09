#ifndef TYPINGHANDLER_HPP
#define TYPINGHANDLER_HPP
#include <string>
#include <SFML/System.hpp>

class TypingHandler 
{
public:
    TypingHandler(std::string target) : targetText(target), typedText(""), finished(false), started(false) {}

    void handleInput(sf::Uint32 unicode);
    void checkProgress();
    
    // Геттеры для доступа к данным
    const std::string& getTarget() const { return targetText; }
    const std::string& getTyped() const { return typedText; }
    bool isFinished() const { return finished; }
    bool isStarted() const { return started; }
    int getMistakes() const;
    float getTime() const {
    if (!started) return 0.0f;
    if (finished) return finalTime; 
    return clock.getElapsedTime().asSeconds(); 
}

private:
    std::string targetText;
    std::string typedText;
    sf::Clock clock;
    bool finished;
    bool started;
    float finalTime;
};
#endif