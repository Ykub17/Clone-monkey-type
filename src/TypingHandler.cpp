#include "TypingHandler.hpp"

// Логика обработки ввода
void TypingHandler::handleInput(sf::Uint32 unicode) 
{
    if (finished) return;

    // Запуск таймера при первом вводе
    if (!started && unicode >= 32 && unicode < 128) 
    {
        started = true;
        clock.restart();
    }

    // Обработка символов
    if (unicode >= 32 && unicode < 128) 
    {
        if (typedText.size() < targetText.size()) 
        {
            typedText += static_cast<char>(unicode);
        }
    }
    
    // Фиксация момента финиша при достижении конца текста
    if (typedText.size() == targetText.size()) 
    {
        finished = true;
        finalTime = clock.getElapsedTime().asSeconds(); // Сохраняем момент финиша
    }
}


// Подсчет ошибок
int TypingHandler::getMistakes() const 
{
    int mistakes = 0;
    for (size_t i = 0; i < typedText.size(); i++) 
    {
        if (typedText[i] != targetText[i]) mistakes++;
    }
    return mistakes;
}