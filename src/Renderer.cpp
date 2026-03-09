#include "Renderer.hpp"
#include "Config.hpp"
#include <sstream>
#include <iomanip>

Renderer::Renderer(sf::Font& f) : font(f) 
{
    // Настройка курсора
    // Курсор - это просто прямоугольник
    cursor.setSize(sf::Vector2f(2.f, 40.f));
    cursor.setOrigin(0.f, 20.f); 
}

// Функция для обрезания текста по ширине
std::string Renderer::wrapText(const std::string& str, float maxWidth) 
{
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(Config::FONT_SIZE);

    std::string result;
    std::string line;
    std::stringstream ss(str);
    std::string word;

    while (ss >> word) 
    {
        std::string testLine = line + word + " ";
        tempText.setString(testLine);

        if (tempText.getGlobalBounds().width > maxWidth) 
        {
            result += line + "\n";
            line = word + " ";
        } else {
            line = testLine;
        }
    }
    return result + line;
}
// Главная функция отрисовки игры
void Renderer::drawGame(sf::RenderWindow& window, const TypingHandler& handler, sf::Vector2f smoothedPos) 
{
    // Подготовка единой обрезанной строки
    std::string wrappedTarget = wrapText(handler.getTarget(), Config::WIDTH - 150.f);

    // Рисуем всю строку целиком базовым цветом
    sf::Text displayLine;
    displayLine.setFont(font);
    displayLine.setCharacterSize(Config::FONT_SIZE);
    displayLine.setString(wrappedTarget);
    
    // Центрируем по горизонтали
    sf::FloatRect bounds = displayLine.getGlobalBounds();
    displayLine.setPosition(std::round((Config::WIDTH - bounds.width) / 2.f), 150.f);

    size_t typedCount = handler.getTyped().size();
    size_t actualCharIdx = 0;

    // Сначала рисуем всю строку целиком базовым цветом
    displayLine.setFillColor(Config::COLOR_BASE);
    window.draw(displayLine);

    // Теперь рисуем только набранные буквы поверх,
    for (size_t i = 0; i < wrappedTarget.size(); i++) 
    {
        if (wrappedTarget[i] == '\n') continue;
        if (actualCharIdx >= typedCount) break;

        sf::Text singleChar = displayLine; // Копируем все настройки, включая шрифт и размер
        singleChar.setString(wrappedTarget[i]);
        
        // Берем позицию символа из исходного объекта displayLine
        sf::Vector2f pos = displayLine.findCharacterPos(i);
        singleChar.setPosition(pos.x, pos.y);

        // Проверяем правильность
        if (handler.getTyped()[actualCharIdx] == handler.getTarget()[actualCharIdx])
            singleChar.setFillColor(Config::COLOR_CORRECT);
        else
            singleChar.setFillColor(Config::COLOR_WRONG);

        window.draw(singleChar);
        actualCharIdx++;
    }

    //  Отрисовка курсора
    cursor.setPosition(smoothedPos.x, smoothedPos.y + 30.f);
    window.draw(cursor);
}

// Функция, чтобы Game мог узнать цель для курсора
sf::Vector2f Renderer::getCursorTargetPos(const TypingHandler& handler) 
{
    // Получаем строку с переносами
    std::string wrapped = wrapText(handler.getTarget(), Config::WIDTH - 150.f);
    
    sf::Text temp;
    temp.setFont(font);
    temp.setCharacterSize(Config::FONT_SIZE);
    temp.setString(wrapped);

    sf::FloatRect bounds = temp.getGlobalBounds();
    float posX = (Config::WIDTH - bounds.width) / 2.f;
    float posY = 150.f; 
    temp.setPosition(posX, posY);

    // Вычисляем правильный индекс для курсора
    size_t typedCount = handler.getTyped().size();
    size_t wrappedIdx = 0;
    size_t actualChars = 0;

    // Идем по обрезанной строке и ищем позицию, 
    // где количество "реальных" букв равно количеству набранных
    while (wrappedIdx < wrapped.size() && actualChars < typedCount) 
    {
        if (wrapped[wrappedIdx] != '\n') 
        {
            actualChars++;
        }
        wrappedIdx++;
    }

    // Возвращаем позицию именно этого индекса
    return temp.findCharacterPos(wrappedIdx);
}
// Функция для отрисовки результатов после окончания игры
void Renderer::drawResults(sf::RenderWindow& window, int mistakes, float time, int totalChars) 
{
    sf::Text res;
    res.setFont(font);
    res.setCharacterSize(40);
    res.setFillColor(sf::Color::White);

    // Вычисляем точность (Accuracy)
    float accuracy = 0.0f;
    if (totalChars > 0) 
    {
        accuracy = (static_cast<float>(totalChars - mistakes) / totalChars) * 100.f;
        if (accuracy < 0) accuracy = 0; 
    }

    std::stringstream ss;
    ss << "Mistakes: " << mistakes << "\n"
       << "Time: " << std::fixed << std::setprecision(2) << time << "s\n"
       << "Accuracy: " << std::fixed << std::setprecision(1) << accuracy << "%";
    
    res.setString(ss.str());

    sf::FloatRect rb = res.getGlobalBounds();
    res.setPosition((Config::WIDTH - rb.width) / 2.f, 150.f);
    window.draw(res);
}
// Функция для отрисовки кнопки перезапуска
void Renderer::drawRestartButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& text) 
{
    window.draw(button);
    window.draw(text);
}